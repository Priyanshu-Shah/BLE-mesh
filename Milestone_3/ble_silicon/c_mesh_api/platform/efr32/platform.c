/*
 * platform.c
 *
 * Platform-specific implementation for EFR32xG26 Explorer Board (BRD2709A Rev A03)
 * This module provides hardware abstraction and platform services including:
 * - Hardware initialization
 * - Sleep/timing functions
 * - Critical section handling
 * - Poll request management
 *
 * The implementation is designed for the Wirepas Dual MCU API protocol,
 * providing necessary platform services for reliable communication between
 * the host MCU and the Wirepas network stack.
 *
 */

/* Wirepas Oy licensed under Apache License, Version 2.0
 *
 * See file LICENSE for full license details.
 */

#include "../platform.h"
#include "em_device.h"
#include "em_chip.h"
#include "em_cmu.h"
#include "em_gpio.h"
#include "em_usart.h"
#include "em_core.h"
#include "sl_sleeptimer.h"

// Platform state tracking
static bool is_initialized = false;          // Platform initialization state
static bool poll_disabled = false;           // Poll request state
static unsigned long max_poll_fail_duration_s = 0;  // Maximum allowed poll failure duration
static unsigned long long last_valid_message_timestamp = 0;  // Timestamp of last valid message

/**
 * @brief Initialize the platform hardware and services
 * 
 * This function:
 * 1. Performs chip initialization (clock, peripherals)
 * 2. Initializes the sleep timer for timing services
 *
 * @return true if initialization successful, false otherwise
 */
bool Platform_init()
{
    if (is_initialized)
    {
        return true;
    }

    // Initialize chip (clocks, peripherals)
    CHIP_Init();

    // Initialize sleep timer for timing services
    sl_sleeptimer_init();

    is_initialized = true;
    return true;
}

/**
 * @brief Sleep for specified microseconds
 * 
 * Uses the sleep timer to implement microsecond delays.
 * Note: Actual resolution is milliseconds, microseconds are
 * converted to nearest millisecond value.
 *
 * @param time_us Time to sleep in microseconds
 */
void Platform_usleep(unsigned int time_us)
{
    sl_sleeptimer_delay_millisecond(time_us / 1000);
}

/**
 * @brief Get current timestamp in milliseconds
 * 
 * Provides a monotonic timestamp using the sleep timer.
 * Used for timing and timeout management in the protocol.
 *
 * @return Current timestamp in milliseconds
 */
unsigned long long Platform_get_timestamp_ms_epoch()
{
    uint32_t ticks = sl_sleeptimer_get_tick_count();
    return (unsigned long long)sl_sleeptimer_tick_to_ms(ticks);
}

/**
 * @brief Enter a critical section
 * 
 * Disables interrupts to protect shared resources.
 * Must be paired with Platform_unlock_request().
 *
 * @return true if critical section entered successfully
 */
bool Platform_lock_request()
{
    CORE_DECLARE_IRQ_STATE;
    CORE_ENTER_CRITICAL();
    return true;
}

/**
 * @brief Exit a critical section
 * 
 * Re-enables interrupts after critical section.
 * Must be paired with Platform_lock_request().
 */
void Platform_unlock_request()
{
    CORE_DECLARE_IRQ_STATE;
    CORE_EXIT_CRITICAL();
}

/**
 * @brief Set maximum duration for poll request failures
 * 
 * Configures how long poll requests are allowed to fail before
 * taking action (e.g., resetting communication).
 *
 * @param duration_s Maximum duration in seconds
 * @return true if setting was applied successfully
 */
bool Platform_set_max_poll_fail_duration(unsigned long duration_s)
{
    max_poll_fail_duration_s = duration_s;
    return true;
}

/**
 * @brief Enable/disable poll requests
 * 
 * Used to temporarily suspend polling during operations
 * that might interfere with normal communication (e.g., reboot).
 *
 * @param disabled true to disable polling, false to enable
 * @return true if state was changed successfully
 */
bool Platform_disable_poll_request(bool disabled)
{
    poll_disabled = disabled;
    return true;
}

/**
 * @brief Record timestamp of valid message reception
 * 
 * Updates the timestamp of the last valid message received.
 * Used for monitoring communication health and timeout handling.
 */
void Platform_valid_message_from_node()
{
    last_valid_message_timestamp = Platform_get_timestamp_ms_epoch();
}

/**
 * @brief Clean up platform resources
 * 
 * Resets platform state and clears all tracking variables.
 * Called during shutdown or before re-initialization.
 */
void Platform_close()
{
    is_initialized = false;
    poll_disabled = false;
    max_poll_fail_duration_s = 0;
    last_valid_message_timestamp = 0;
}




