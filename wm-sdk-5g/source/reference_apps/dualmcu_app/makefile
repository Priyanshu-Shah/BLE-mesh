# Dual MCU app needs UART
HAL_UART=yes
ifeq ($(uart_use_usb),yes)
UART_USE_DMA=no
UART_USE_USB=yes
CFLAGS += -DUART_USE_USB
else ifeq ($(uart_use_dma),no)
UART_USE_DMA=no
UART_USE_USB=no
else
# dma uart is used by default if not explicitly set to no
UART_USE_DMA=yes
UART_USE_USB=no
endif

# Define default baudrate and hardware flow control settings
uart_br ?= 125000
uart_fc ?= false

CFLAGS += -DUART_BAUDRATE=$(uart_br)
CFLAGS += -DUART_FLOWCONTROL=$(uart_fc)

DUALMCU_LIB=yes


# Enable to allow reading scratchpad via dual-MCU API
allow_scratchpad_read ?= no
ifeq ($(allow_scratchpad_read),yes)
    CFLAGS += -DALLOW_SCRATCHPAD_READ
endif
