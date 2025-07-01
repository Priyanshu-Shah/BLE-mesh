# Boards compatible with this app 
TARGET_BOARDS := pca10153 pca10165 pca20049 pca20064 pca20065 

# Define a specific application area_id
app_specific_area_id=0x846B74

# App version
app_major=$(sdk_major)
app_minor=$(sdk_minor)
app_maintenance=$(sdk_maintenance)
app_development=$(sdk_development)

# Uncomment to allow reading scratchpad via dual-MCU API
#allow_scratchpad_read=yes
default_network_address ?= 5000
default_network_channel ?= 1
default_network_authen_key ?= 0x12,0x34,0x56,0x78,0x90,0x12,0x34,0x56,0x78,0x90,0x12,0x34,0x56,0x78,0x90,0x12
default_network_cipher_key ?= 0x12,0x34,0x56,0x78,0x90,0x12,0x34,0x56,0x78,0x90,0x12,0x34,0x56,0x78,0x90,0x12