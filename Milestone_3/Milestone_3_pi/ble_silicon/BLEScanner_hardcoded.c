// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>
// #include <unistd.h>
// #include <stdint.h>
// #include <sys/time.h>
// #include <bluetooth/bluetooth.h>
// #include <bluetooth/hci.h>
// #include <bluetooth/hci_lib.h>
// #include "cbor.h"

// // Configuration constants
// #define SERIAL_PORT_NAME    ""  // Empty string as we use fixed UART
// #define SERIAL_BAUD_RATE   115200
// #define BLE_SCAN_ENDPOINT  10   // Endpoint number for BLE scan data in Wirepas network


// // WPC frame ID tracking
// static uint8_t current_frame_id = 0;

// /**
//  * @brief Get next frame ID for WPC protocol
//  * 
//  * Generates sequential frame IDs, wrapping from 255 to 1
//  * (0 is reserved/invalid)
//  *
//  * @return Next frame ID to use
//  */
// static uint8_t get_next_frame_id(void)
// {
//     current_frame_id++;
//     if (current_frame_id == 0)
//         current_frame_id = 1;
//     return current_frame_id;
// }

// /**
//  * @brief Wait for and validate frame acknowledgment from WPC
//  * 
//  * This function:
//  * 1. Waits for frame delimiter
//  * 2. Reads frame header (primitive_id, frame_id, payload_length)
//  * 3. Validates frame type and ID
//  * 4. Reads and validates confirmation payload
//  *
//  * @param expected_frame_id Frame ID to wait for
//  * @return wpc_error_t Error code indicating success/failure
//  */
// static wpc_error_t wait_for_ack(uint8_t expected_frame_id)
// {
//     uint8_t rx_buf[MAX_FRAME_SIZE];
//     unsigned int total_read = 0;
//     TickType_t start_time = xTaskGetTickCount();
    
//     // Wait for delimiter
//     while (1) {
//         if (Serial_read(rx_buf, WPC_ACK_TIMEOUT_MS) != 1) {
//             return WPC_ERROR_NO_ACK;
//         }
//         if (rx_buf[0] == WPC_FRAME_DELIMITER) {
//             break;
//         }
//         // Check timeout
//         if ((xTaskGetTickCount() - start_time) > pdMS_TO_TICKS(WPC_ACK_TIMEOUT_MS)) {
//             return WPC_ERROR_NO_ACK;
//         }
//     }

//     // Read frame header (3 bytes: primitive_id, frame_id, payload_length)
//     for (int i = 0; i < 3; i++) {
//         if (Serial_read(&rx_buf[total_read], WPC_ACK_TIMEOUT_MS) != 1) {
//             return WPC_ERROR_NO_ACK;
//         }
//         total_read++;
//     }

//     // Check if this is a DSAP_DATA_TX_CONFIRM
//     wpc_frame_t *frame = (wpc_frame_t *)rx_buf;
//     if (frame->primitive_id != DSAP_DATA_TX_CONFIRM ||
//         frame->frame_id != expected_frame_id) {
//         return WPC_ERROR_INVALID_ACK;
//     }

//     // Read confirmation payload
//     if (frame->payload_length > 0) {
//         for (int i = 0; i < frame->payload_length; i++) {
//             if (Serial_read(&rx_buf[total_read + i], WPC_ACK_TIMEOUT_MS) != 1) {
//                 return WPC_ERROR_NO_ACK;
//             }
//         }
//     }

//     // Check result in confirmation
//     if (frame->payload.sap_generic_confirm_payload.result != 0) {
//         return WPC_ERROR_INVALID_ACK;
//     }

//     return WPC_OK;
// }

// /**
//  * @brief Main BLE scanner task
//  * 
//  * This task:
//  * 1. Initializes serial communication for WPC
//  * 2. Configures BLE scanner in passive mode
//  * 3. Starts scanning on 1M PHY
//  * 4. Processes BLE events in a continuous loop
//  *
//  * Scanner Configuration:
//  * - Mode: Passive (non-connecting)
//  * - Interval: 10ms (0x10 * 0.625ms)
//  * - Window: 10ms (continuous scanning)
//  * - PHY: 1M
//  * - Filter: Generic discoverable devices
//  *
//  * @param arg Task parameter (unused)
//  */
// void BLEScannerTask(void *arg)
// {
//     (void)arg; // suppress unused param warning
//     sl_status_t sc;

//     // Initialize serial port
//     if (Serial_open(SERIAL_PORT_NAME, SERIAL_BAUD_RATE) != 0) {
//         printf("Failed to initialize serial port\n");
//         vTaskDelete(NULL);
//         return;
//     }

//     // Configure BLE scanner parameters: passive mode, 10ms interval and window (0x10 * 0.625ms = 10ms)
//     sc = sl_bt_scanner_set_parameters(
//         sl_bt_scanner_scan_mode_passive,
//         0x10,
//         0x10
//     );

//     if (sc != SL_STATUS_OK) {
//         printf("Failed to set scanner parameters: 0x%lx\n", sc);
//         Serial_close();
//         vTaskDelete(NULL);
//         return;
//     }

//     // Start scanning on 1M PHY for generic discoverable devices
//     sc = sl_bt_scanner_start(sl_bt_gap_1m_phy, sl_bt_scanner_discover_generic);

//     if (sc != SL_STATUS_OK) {
//         printf("BLE scanner start failed: 0x%lx\n", sc);
//         Serial_close();
//         vTaskDelete(NULL);
//         return;
//     }

//     while (1) {
//         sl_bt_msg_t evt;
//         // Non-blocking event poll; sl_bt_pop_event returns SL_STATUS_OK if event retrieved
//         sc = sl_bt_pop_event(&evt);
//         if (sc == SL_STATUS_OK) {
//             // Pass event to Bluetooth stack internal handler
//             sl_bt_on_event(&evt);
//         } else {
//             // No event available, can optionally sleep a bit or handle differently
//             // For low power, consider vTaskDelay here or event-driven mechanism
//         }

//         // Delay to prevent tight polling loop, adjust as needed for latency vs CPU usage
//         vTaskDelay(pdMS_TO_TICKS(10));
//     }
// }

// #define CBOR_BUF_SIZE 128

// /**
//  * @brief Encode BLE advertisement data in CBOR format
//  * 
//  * Creates a CBOR map with the following fields:
//  * - "mac": Device MAC address (byte string)
//  * - "rssi": Signal strength (integer)
//  * - "adv": Raw advertisement data (byte string)
//  *
//  * Example CBOR structure:
//  * {
//  *   "mac": h'112233445566',
//  *   "rssi": -70,
//  *   "adv": h'020106050954657374446576'
//  * }
//  *
//  * @param buffer Output buffer for CBOR data
//  * @param buffer_size Size of output buffer
//  * @param mac Bluetooth device address
//  * @param rssi Received signal strength
//  * @param adv_data Raw advertisement data
//  * @param adv_len Length of advertisement data
//  * @param encoded_len Resulting CBOR data length
//  * @return 0 on success, error code on failure
//  */
// int encode_ble_advertisement_to_cbor(uint8_t *buffer, size_t buffer_size,
//                                    const bd_addr *mac,
//                                    int8_t rssi,
//                                    const uint8_t *adv_data,
//                                    size_t adv_len,
//                                    size_t *encoded_len)
// {
//     if (!buffer || !mac || !adv_data || !encoded_len) {
//         return -1; // invalid parameters
//     }

//     CborEncoder encoder, mapEncoder;
//     cbor_encoder_init(&encoder, buffer, buffer_size, 0);

//     // Create a map container with 3 key-value pairs
//     CborError err = cbor_encoder_create_map(&encoder, &mapEncoder, 3);
//     if (err != CborNoError) return err;

//     // Encode MAC address as byte string under key "mac"
//     err |= cbor_encode_text_stringz(&mapEncoder, "mac");
//     err |= cbor_encode_byte_string(&mapEncoder, mac->addr, sizeof(mac->addr));

//     // Encode RSSI as integer under key "rssi"
//     err |= cbor_encode_text_stringz(&mapEncoder, "rssi");
//     err |= cbor_encode_int(&mapEncoder, rssi);

//     // Encode advertisement data as byte string under key "adv_data"
//     err |= cbor_encode_text_stringz(&mapEncoder, "adv_data");
//     err |= cbor_encode_byte_string(&mapEncoder, adv_data, adv_len);

//     // Close the map container
//     err |= cbor_encoder_close_container(&encoder, &mapEncoder);

//     if (err == CborNoError) {
//         *encoded_len = cbor_encoder_get_buffer_size(&encoder, buffer);
//         return 0;
//     }

//     return err;
// }

// /**
//  * @brief Debug function to print advertisement data
//  * 
//  * Prints advertisement data in hexadecimal format with
//  * length information. Used for debugging and verification.
//  *
//  * @param data Advertisement data bytes
//  * @param len Length of data
//  */
// void print_advertising_data(const uint8_t *data, size_t len) {
//     if (!data) return;

//     printf("Adv Data: ");
//     for (size_t i = 0; i < len; ++i) {
//         printf("%02X ", data[i]);
//     }
//     printf("\n");
// }

// /**
//  * @brief Send BLE data using WPC protocol
//  * 
//  * This function:
//  * 1. Creates a WPC frame with the CBOR data
//  * 2. Sends the frame over serial interface
//  * 3. Waits for acknowledgment
//  *
//  * Frame format:
//  * [0xFF][primitive_id][frame_id][length][payload...]
//  *
//  * @param cbor_data Encoded CBOR data to send
//  * @param cbor_len Length of CBOR data
//  * @return wpc_error_t Error code indicating success/failure
//  */
// static wpc_error_t send_ble_data_via_wpc(const uint8_t *cbor_data, size_t cbor_len)
// {
//     if (cbor_data == NULL || cbor_len == 0) {
//         return WPC_ERROR_INVALID_PARAMS;
//     }

//     if (cbor_len > MAX_DATA_PDU_SIZE) {
//         printf("WPC Error: Data too large (%zu bytes, max %d)\n", 
//                cbor_len, MAX_DATA_PDU_SIZE);
//         return WPC_ERROR_PDU_TOO_LARGE;
//     }

//     // Prepare WPC frame
//     wpc_frame_t frame = {0};
//     frame.primitive_id = DSAP_DATA_TX_REQUEST;
//     frame.frame_id = get_next_frame_id();
//     frame.payload_length = sizeof(dsap_data_tx_req_pl_t) - MAX_DATA_PDU_SIZE + cbor_len;

//     // Fill in the data transmission request
//     frame.payload.dsap_data_tx_request_payload.pdu_id = frame.frame_id;  // Use frame_id as PDU ID
//     frame.payload.dsap_data_tx_request_payload.src_endpoint = BLE_SCAN_ENDPOINT;
//     frame.payload.dsap_data_tx_request_payload.dest_add = 0;  // Broadcast address
//     frame.payload.dsap_data_tx_request_payload.dest_endpoint = BLE_SCAN_ENDPOINT;
//     frame.payload.dsap_data_tx_request_payload.qos = 0;  // Normal priority
//     frame.payload.dsap_data_tx_request_payload.tx_options = 0;  // No special options
//     frame.payload.dsap_data_tx_request_payload.apdu_length = cbor_len;
//     memcpy(frame.payload.dsap_data_tx_request_payload.apdu, cbor_data, cbor_len);

//     // Calculate total frame size
//     size_t total_size = FRAME_SIZE(&frame);

//     // Send frame delimiter
//     uint8_t delimiter = WPC_FRAME_DELIMITER;
//     if (Serial_write(&delimiter, 1) != 1) {
//         printf("WPC Error: Failed to write frame delimiter\n");
//         return WPC_ERROR_SERIAL_WRITE;
//     }

//     // Send frame
//     if (Serial_write((uint8_t *)&frame, total_size) != total_size) {
//         printf("WPC Error: Failed to write frame data\n");
//         return WPC_ERROR_SERIAL_WRITE;
//     }

//     // Wait for acknowledgment
//     wpc_error_t ack_result = wait_for_ack(frame.frame_id);
//     if (ack_result != WPC_OK) {
//         printf("WPC Error: Frame acknowledgment failed (error %d)\n", ack_result);
//         return ack_result;
//     }

//     return WPC_OK;
// }

// /**
//  * @brief Handle BLE scanner events
//  * 
//  * Processes BLE scanner events:
//  * - Extracts advertisement data and RSSI
//  * - Encodes data in CBOR format
//  * - Transmits via WPC protocol
//  *
//  * This function is called for each received advertisement
//  * that matches the scanner's filter criteria.
//  *
//  * @param evt Bluetooth stack event
//  */
// void handle_scanner_event(sl_bt_msg_t *evt)
// {
//     if (!evt) return;

//     uint8_t cbor_buf[CBOR_BUF_SIZE];
//     size_t cbor_len = 0;

//     switch (SL_BT_MSG_ID(evt->header)) {
//         case sl_bt_evt_scanner_legacy_advertisement_report_id: {
//             const sl_bt_evt_scanner_legacy_advertisement_report_t *r =
//                 &evt->data.evt_scanner_legacy_advertisement_report;

//             printf("Legacy MAC: %02X:%02X:%02X:%02X:%02X:%02X, RSSI: %d dBm\n",
//                    r->address.addr[5], r->address.addr[4], r->address.addr[3],
//                    r->address.addr[2], r->address.addr[1], r->address.addr[0],
//                    r->rssi);

//             print_advertising_data(r->data.data, r->data.len);

//             if (encode_ble_advertisement_to_cbor(cbor_buf, CBOR_BUF_SIZE, &r->address,
//                                                  r->rssi, r->data.data, r->data.len, &cbor_len) == 0)
//             {
//                 wpc_error_t result = send_ble_data_via_wpc(cbor_buf, cbor_len);
//                 if (result != WPC_OK) {
//                     printf("Failed to send legacy adv data: error %d\n", result);
//                 }
//             }
//             break;
//         }

//         case sl_bt_evt_scanner_extended_advertisement_report_id: {
//             const sl_bt_evt_scanner_extended_advertisement_report_t *r =
//                 &evt->data.evt_scanner_extended_advertisement_report;

//             printf("Extended MAC: %02X:%02X:%02X:%02X:%02X:%02X, RSSI: %d dBm\n",
//                    r->address.addr[5], r->address.addr[4], r->address.addr[3],
//                    r->address.addr[2], r->address.addr[1], r->address.addr[0],
//                    r->rssi);

//             print_advertising_data(r->data.data, r->data.len);

//             if (encode_ble_advertisement_to_cbor(cbor_buf, CBOR_BUF_SIZE, &r->address,
//                                                  r->rssi, r->data.data, r->data.len, &cbor_len) == 0)
//             {
//                 wpc_error_t result = send_ble_data_via_wpc(cbor_buf, cbor_len);
//                 if (result != WPC_OK) {
//                     printf("Failed to send extended adv data: error %d\n", result);
//                 }
//             }
//             break;
//         }

//         default:
//             // Ignore other events
//             break;
//     }
// }


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdint.h>
#include <bluetooth/bluetooth.h>
#include <bluetooth/hci.h>
#include <bluetooth/hci_lib.h>
#include "tinycbor/cbor.h"

// --- Frame struct definitions (keep for inspection) ---
#define MAX_DATA_PDU_SIZE 128
#define BLE_SCAN_ENDPOINT 10

typedef struct {
    uint8_t pdu_id;
    uint8_t src_endpoint;
    uint32_t dest_add;
    uint8_t dest_endpoint;
    uint8_t qos;
    uint8_t tx_options;
    uint16_t apdu_length;
    uint8_t apdu[MAX_DATA_PDU_SIZE];
} dsap_data_tx_req_pl_t;

typedef struct {
    uint8_t primitive_id;
    uint8_t frame_id;
    uint8_t payload_length;
    union {
        dsap_data_tx_req_pl_t dsap_data_tx_request_payload;
    } payload;
} wpc_frame_t;

//typedef struct {
//    uint8_t evt;
//    uint8_t plen;
//} __attribute__((packed)) hci_event_hdr;

// --- CBOR encoding ---
#define CBOR_BUF_SIZE 128

int encode_ble_advertisement_to_cbor(uint8_t *buffer, size_t buffer_size,
                                     const uint8_t *mac,
                                     int8_t rssi,
                                     const uint8_t *adv_data,
                                     size_t adv_len,
                                     size_t *encoded_len)
{
    if (!buffer || !mac || !adv_data || !encoded_len) {
        return -1;
    }
    CborEncoder encoder, mapEncoder;
    cbor_encoder_init(&encoder, buffer, buffer_size, 0);
    CborError err = cbor_encoder_create_map(&encoder, &mapEncoder, 3);
    if (err != CborNoError) return err;
    err |= cbor_encode_text_stringz(&mapEncoder, "mac");
    err |= cbor_encode_byte_string(&mapEncoder, mac, 6);
    err |= cbor_encode_text_stringz(&mapEncoder, "rssi");
    err |= cbor_encode_int(&mapEncoder, rssi);
    err |= cbor_encode_text_stringz(&mapEncoder, "adv_data");
    err |= cbor_encode_byte_string(&mapEncoder, adv_data, adv_len);
    err |= cbor_encoder_close_container(&encoder, &mapEncoder);
    if (err == CborNoError) {
        *encoded_len = cbor_encoder_get_buffer_size(&encoder, buffer);
        return 0;
    }
    return err;
}

// --- Print helpers ---
void print_hex(const uint8_t *buf, size_t len) {
    for (size_t i = 0; i < len; ++i)
        printf("%02X", buf[i]);
    printf("\n");
}

void print_frame_struct(const wpc_frame_t *frame, size_t cbor_len) {
    printf("Frame struct:\n");
    printf("  primitive_id: %u\n", frame->primitive_id);
    printf("  frame_id: %u\n", frame->frame_id);
    printf("  payload_length: %u\n", frame->payload_length);
    printf("  pdu_id: %u\n", frame->payload.dsap_data_tx_request_payload.pdu_id);
    printf("  src_endpoint: %u\n", frame->payload.dsap_data_tx_request_payload.src_endpoint);
    printf("  dest_add: %u\n", frame->payload.dsap_data_tx_request_payload.dest_add);
    printf("  dest_endpoint: %u\n", frame->payload.dsap_data_tx_request_payload.dest_endpoint);
    printf("  qos: %u\n", frame->payload.dsap_data_tx_request_payload.qos);
    printf("  tx_options: %u\n", frame->payload.dsap_data_tx_request_payload.tx_options);
    printf("  apdu_length: %u\n", frame->payload.dsap_data_tx_request_payload.apdu_length);
    printf("  apdu (CBOR): ");
    print_hex(frame->payload.dsap_data_tx_request_payload.apdu, cbor_len);
}

// --- Main BLE scan and frame build ---
int main() {
    int dev_id = hci_get_route(NULL);
    int sock = hci_open_dev(dev_id);
    
    struct hci_filter nf;
    hci_filter_clear(&nf);
    hci_filter_set_ptype(HCI_EVENT_PKT, &nf);
    hci_filter_all_events(&nf);
    setsockopt(sock, SOL_HCI, HCI_FILTER, &nf, sizeof(nf));
    
    if (dev_id < 0 || sock < 0) {
        perror("opening socket");
        return 1;
    }

    // Set BLE scan parameters and enable scan
    if (hci_le_set_scan_parameters(sock, 0x01, htobs(0x10), htobs(0x10), 0, 0, 1000) < 0) {
        perror("set scan parameters");
        close(sock);
        return 1;
    }
    if (hci_le_set_scan_enable(sock, 0x01, 1, 1000) < 0) {
        perror("enable scan");
        close(sock);
        return 1;
    }

    printf("Scanning for BLE advertisements (Ctrl+C to stop)...\n");

    uint8_t frame_id = 1;
    while (1) {
        unsigned char buf[HCI_MAX_EVENT_SIZE];
        int len = read(sock, buf, sizeof(buf));
        //printf("[DEBUG] Raw HCI event: ");
        //print_hex(buf, len);
        if (len < 0) {
            perror("read");
            continue;
        }

        // Log: Data received from socket
        //printf("[LOG] Received %d bytes from HCI socket\n", len);

        if (len < (1 + HCI_EVENT_HDR_SIZE)) {
            //printf("[LOG] Packet too short for HCI event header\n");
            continue;
        }

        //struct hci_event_hdr *hdr = (void *)(buf + 1);
        hci_event_hdr *hdr = (hci_event_hdr *)(buf + 1);
        //printf("[LOG] HCI event type: 0x%02X\n", hdr->evt);

        if (hdr->evt != EVT_LE_META_EVENT) {
            //printf("[LOG] Not a LE Meta Event (evt=0x%02X), skipping\n", hdr->evt);
            continue;
        }

        evt_le_meta_event *meta = (void *)(buf + (1 + HCI_EVENT_HDR_SIZE));
        //printf("[LOG] LE Meta Event subevent: 0x%02X\n", meta->subevent);

        if (meta->subevent != EVT_LE_ADVERTISING_REPORT) {
            //printf("[LOG] Not an Advertising Report (subevent=0x%02X), skipping\n", meta->subevent);
            continue;
        }

        uint8_t reports_count = meta->data[0];
        //printf("[LOG] Number of advertising reports: %u\n", reports_count);
        uint8_t *ptr = meta->data + 1;

        for (int i = 0; i < reports_count; i++) {
            le_advertising_info *info = (le_advertising_info *)ptr;
            
            //uint8_t target_mac[6] = {0xD1, 0x57, 0x89, 0xB3, 0xAF, 0x44};
            //uint8_t target_mac2[6] = {0x44, 0xAF, 0xB3, 0x89, 0x57, 0xD1};
            //if (memcmp(info->bdaddr.b, target_mac, 6) != 0) {
                // Not our beacon, skip
                //continue;
            //}
            //else if (memcmp(info->bdaddr.b, target_mac2, 6) != 0){
                //continue;
            //}
            //else{
                //printf("[DEBUG] Matched target MAC: ");
                //print_hex(info->bdaddr.b, 6);
            //}
            
            //Hardcoded UUID for beacon testing 
            const uint8_t expected_uuid[16] = {
                0x33, 0xD7, 0xFD, 0xBA,
                0x4C, 0x8F,
                0x11, 0xED,
                0xBD, 0xC3,
                0x32, 0xF4, 0x9F, 0x8B, 0x97, 0x84
            };
            
            int matched = 0;
            for (int j = 0; j < info->length - 2; ) {
                uint8_t len = info->data[j];
                uint8_t type = info->data[j + 1];

                // Check for manufacturer specific data (type 0xFF)
                if (type == 0xFF && len >= 25) {
                    // Check Apple Manufacturer ID and iBeacon signature
                    if (info->data[j + 2] == 0x4C && info->data[j + 3] == 0x00 && // Apple ID
                        info->data[j + 4] == 0x02 && info->data[j + 5] == 0x15) { // iBeacon structure
                        // Compare UUID
                        if (memcmp(&info->data[j + 6], expected_uuid, 16) == 0) {
                            matched = 1;
                            break;
                        }
                    }
                }

                j += len + 1;
            }

            if (!matched) {
                //printf("[DEBUG] Skipped non-matching beacon\n");
                continue;
            }


            

            printf("MAC: %02X:%02X:%02X:%02X:%02X:%02X, RSSI: %d dBm\n",
                   info->bdaddr.b[5], info->bdaddr.b[4], info->bdaddr.b[3],
                   info->bdaddr.b[2], info->bdaddr.b[1], info->bdaddr.b[0],
                   (int8_t)info->data[info->length]);

            printf("Adv Data: ");
            for (int j = 0; j < info->length; ++j)
                printf("%02X ", info->data[j]);
            printf("\n");
            

            // --- CBOR encode ---
            uint8_t cbor_buf[CBOR_BUF_SIZE];
            size_t cbor_len = 0;
            if (encode_ble_advertisement_to_cbor(
                    cbor_buf, CBOR_BUF_SIZE,
                    info->bdaddr.b,
                    (int8_t)info->data[info->length],
                    info->data, info->length,
                    &cbor_len) == 0)
            {
                printf("CBOR: ");
                print_hex(cbor_buf, cbor_len);

                // --- Build frame struct (lines 292–299 equivalent) ---
                wpc_frame_t frame = {0};
                frame.primitive_id = 0x01; // Example value
                frame.frame_id = frame_id++;
                frame.payload_length = sizeof(dsap_data_tx_req_pl_t) - MAX_DATA_PDU_SIZE + cbor_len;
                frame.payload.dsap_data_tx_request_payload.pdu_id = frame.frame_id;
                frame.payload.dsap_data_tx_request_payload.src_endpoint = BLE_SCAN_ENDPOINT;
                frame.payload.dsap_data_tx_request_payload.dest_add = 0;
                frame.payload.dsap_data_tx_request_payload.dest_endpoint = BLE_SCAN_ENDPOINT;
                frame.payload.dsap_data_tx_request_payload.qos = 0;
                frame.payload.dsap_data_tx_request_payload.tx_options = 0;
                frame.payload.dsap_data_tx_request_payload.apdu_length = cbor_len;
                memcpy(frame.payload.dsap_data_tx_request_payload.apdu, cbor_buf, cbor_len);

                // --- Print the frame struct for inspection ---
                print_frame_struct(&frame, cbor_len);
            }

            // Advance pointer to next report
            ptr += sizeof(le_advertising_info) + info->length + 2; // +2 for evt_type and data_length fields
        }
    }

    hci_le_set_scan_enable(sock, 0x00, 1, 1000);
    close(sock);
    return 0;
}
