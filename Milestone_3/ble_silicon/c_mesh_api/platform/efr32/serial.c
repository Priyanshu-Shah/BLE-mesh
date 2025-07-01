/*
 * serial.c
 *
 * Serial implementation for EFR32xG26 Explorer Board (BRD2709A Rev A03)
 * This module implements the low-level UART communication interface using USART0
 * with hardware flow control (CTS/RTS).
 *
 * Hardware Configuration:
 * - USART0 with the following pins:
 *   - TX:  PB02 (USART0_TX)
 *   - RX:  PB03 (USART0_RX)
 *   - CTS: PA06 (USART0_CTS) - Input, controlled by receiver
 *   - RTS: PA00 (USART0_RTS) - Output, controlled by this device
 *
 * Flow Control:
 * - Hardware flow control (CTS/RTS) is used for reliable communication
 * - CTS (Clear To Send): Input signal controlled by the receiver
 *   - When LOW, this device can transmit
 *   - When HIGH, this device must stop transmitting
 * - RTS (Ready To Send): Output signal controlled by this device
 *   - Set LOW when ready to receive data
 *   - Set HIGH when cannot accept more data
 *
 */

/* Wirepas Oy licensed under Apache License, Version 2.0
 *
 * See file LICENSE for full license details.
 */

#include "../serial.h"
#include "em_device.h"
#include "em_cmu.h"
#include "em_gpio.h"
#include "em_usart.h"
#include "sl_sleeptimer.h"

// Pin definitions for USART0
#define SERIAL_TX_PORT  gpioPortB
#define SERIAL_TX_PIN   2

#define SERIAL_RX_PORT  gpioPortB
#define SERIAL_RX_PIN   3

#define SERIAL_CTS_PORT gpioPortA
#define SERIAL_CTS_PIN  6

#define SERIAL_RTS_PORT gpioPortA
#define SERIAL_RTS_PIN  0

// Default USART instance
#define SERIAL_USART    USART0

// Track initialization state
static bool is_initialized = false;

/**
 * @brief Initialize and open the serial interface
 * 
 * This function:
 * 1. Enables clocks for GPIO and USART0
 * 2. Configures GPIO pins for UART and flow control
 * 3. Initializes USART0 with hardware flow control
 * 4. Sets up pin routing for all signals
 *
 * @param port_name Ignored as we use fixed USART0
 * @param bitrate Communication speed in bits per second
 * @return 0 on success, -1 on error
 */
int Serial_open(const char * port_name, unsigned long bitrate)
{
    (void)port_name; // Port name is ignored as we use fixed USART0

    if (is_initialized)
    {
        return -1;
    }

    // Enable clock for GPIO and USART0
    CMU_ClockEnable(cmuClock_GPIO, true);
    CMU_ClockEnable(cmuClock_USART0, true);

    // Configure GPIO pins
    GPIO_PinModeSet(SERIAL_TX_PORT, SERIAL_TX_PIN, gpioModePushPull, 1);
    GPIO_PinModeSet(SERIAL_RX_PORT, SERIAL_RX_PIN, gpioModeInputPull, 1);
    
    // Configure flow control pins
    GPIO_PinModeSet(SERIAL_CTS_PORT, SERIAL_CTS_PIN, gpioModeInputPull, 1);  // CTS is input
    GPIO_PinModeSet(SERIAL_RTS_PORT, SERIAL_RTS_PIN, gpioModePushPull, 0);   // RTS is output, initially low (ready to receive)

    // Default USART configuration
    USART_InitAsync_TypeDef init = USART_INITASYNC_DEFAULT;
    init.baudrate = bitrate;
    init.enable = usartEnable;
    init.hwFlowControl = usartHwFlowControlCtsAndRts;  // Enable hardware flow control

    // Initialize USART
    USART_InitAsync(SERIAL_USART, &init);

    // Route USART signals to GPIO pins
    GPIO->USARTROUTE[0].ROUTEEN = GPIO_USART_ROUTEEN_TXPEN | 
                                  GPIO_USART_ROUTEEN_RXPEN |
                                  GPIO_USART_ROUTEEN_RTSPEN |
                                  GPIO_USART_ROUTEEN_CSPEN;   // Changed to CSPEN for CTS

    // Configure TX/RX routing
    GPIO->USARTROUTE[0].TXROUTE = (SERIAL_TX_PORT << _GPIO_USART_TXROUTE_PORT_SHIFT) |
                                  (SERIAL_TX_PIN << _GPIO_USART_TXROUTE_PIN_SHIFT);
    
    GPIO->USARTROUTE[0].RXROUTE = (SERIAL_RX_PORT << _GPIO_USART_RXROUTE_PORT_SHIFT) |
                                  (SERIAL_RX_PIN << _GPIO_USART_RXROUTE_PIN_SHIFT);

    // Configure flow control routing
    GPIO->USARTROUTE[0].CSROUTE = (SERIAL_CTS_PORT << _GPIO_USART_CSROUTE_PORT_SHIFT) |
                                  (SERIAL_CTS_PIN << _GPIO_USART_CSROUTE_PIN_SHIFT);

    GPIO->USARTROUTE[0].RTSROUTE = (SERIAL_RTS_PORT << _GPIO_USART_RTSROUTE_PORT_SHIFT) |
                                   (SERIAL_RTS_PIN << _GPIO_USART_RTSROUTE_PIN_SHIFT);

    is_initialized = true;
    return 0;
}

/**
 * @brief Close the serial interface and cleanup resources
 * 
 * This function:
 * 1. Disables the USART peripheral
 * 2. Disables peripheral clocks
 * 3. Resets all GPIO pins to disabled state
 *
 * @return 0 on success, -1 if not initialized
 */
int Serial_close(void)
{
    if (!is_initialized)
    {
        return -1;
    }

    // Disable USART
    USART_Enable(SERIAL_USART, usartDisable);

    // Disable clocks
    CMU_ClockEnable(cmuClock_USART0, false);

    // Reset GPIO pins
    GPIO_PinModeSet(SERIAL_TX_PORT, SERIAL_TX_PIN, gpioModeDisabled, 0);
    GPIO_PinModeSet(SERIAL_RX_PORT, SERIAL_RX_PIN, gpioModeDisabled, 0);
    GPIO_PinModeSet(SERIAL_CTS_PORT, SERIAL_CTS_PIN, gpioModeDisabled, 0);
    GPIO_PinModeSet(SERIAL_RTS_PORT, SERIAL_RTS_PIN, gpioModeDisabled, 0);

    is_initialized = false;
    return 0;
}

/**
 * @brief Read a single byte from the serial interface
 * 
 * This function waits for data with timeout. Hardware flow control (RTS)
 * is automatically handled by the USART peripheral based on buffer status.
 *
 * @param c Pointer to store the received byte
 * @param timeout_ms Maximum time to wait for data in milliseconds
 * @return 1 if byte received, 0 on timeout, -1 on error
 */
int Serial_read(unsigned char * c, unsigned int timeout_ms)
{
    if (!is_initialized || c == NULL)
    {
        return -1;
    }

    uint32_t start_time = sl_sleeptimer_get_tick_count();
    uint32_t timeout_ticks = sl_sleeptimer_ms_to_tick(timeout_ms);

    // Wait for data or timeout
    while ((SERIAL_USART->STATUS & USART_STATUS_RXDATAV) == 0)
    {
        if ((sl_sleeptimer_get_tick_count() - start_time) >= timeout_ticks)
        {
            return 0; // Timeout
        }
    }

    // Read the data
    *c = USART_Rx(SERIAL_USART);
    return 1;
}

/**
 * @brief Write data to the serial interface
 * 
 * This function transmits data with hardware flow control:
 * - Waits for TX buffer to be empty before each byte
 * - Hardware flow control (CTS) is automatically handled by USART
 * - Ensures all data is transmitted before returning
 *
 * @param buffer Data to transmit
 * @param buffer_size Number of bytes to transmit
 * @return Number of bytes written, or -1 on error
 */
int Serial_write(const unsigned char * buffer, unsigned int buffer_size)
{
    if (!is_initialized || buffer == NULL)
    {
        return -1;
    }

    unsigned int bytes_written;
    for (bytes_written = 0; bytes_written < buffer_size; bytes_written++)
    {
        // Wait for TX buffer to be empty
        // Hardware flow control (CTS) is handled automatically by the USART peripheral
        while (!(SERIAL_USART->STATUS & USART_STATUS_TXBL));
        
        // Send the byte
        USART_Tx(SERIAL_USART, buffer[bytes_written]);
    }

    // Wait for all data to be transmitted
    while (!(SERIAL_USART->STATUS & USART_STATUS_TXC));

    return bytes_written;
}




