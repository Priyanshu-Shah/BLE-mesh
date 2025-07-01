# BLE Mesh Forwarder Using EFR32MG26 and nRF9151 (Wirepas Dual-MCU)

## Overview

This project implements a dual-MCU system for capturing BLE advertisements and forwarding them into a Wirepas Mesh network. It uses:

- **EFR32MG26 (Silicon Labs)** for BLE scanning and CBOR encoding.
- **nRF9151 (Nordic)** for receiving this data over UART, framing it using WAPS (Wirepas Application Protocol for Serial), and injecting it into the mesh.

This solution is ideal for BLE beacon harvesting, low-power wide-area sensing, and distributed mesh communication scenarios.

---

## System Architecture

  - A[BLE Advertisement] --> B[EFR32MG26 BLE Scanner]
  - B --> C[CBOR Encoding]
  - C --> D[UART WPC Transmission]
  - D --> E[nRF9151 Dual-MCU App]
  - E --> F[WAPS Frame Creation]
  - F --> G[Mesh Network via Wirepas Stack]

---

## Component Roles

### 🧠 EFR32MG26: BLE Scanner + CBOR Encoder

* **Scans** BLE advertisements (legacy + extended).
* **Extracts** MAC address, RSSI, and payload.
* **Encodes** the data using CBOR for compact serialization.
* **Transmits** it via UART using a custom WPC protocol format.

> See `BLEScanner.c`, `handle_scanner_event`, `encode_ble_advertisement_to_cbor`, and `send_ble_data_via_wpc`.

### 📡 nRF9151: Mesh Transmitter via Wirepas WAPS

* **Receives** encoded CBOR data via UART.
* **Parses** it using WAPS (DSAP, MSAP, HSAP handlers).
* **Injects** it into the Wirepas Mesh using the correct endpoints.

> See `dual_mcu_app`, `waps_uart.c`, and `dsap_data_tx_req_t` usage.

---

## Data Flow

1. **EFR32MG26** passively scans BLE advertisements using Silicon Labs’ Bluetooth stack.
2. On receiving an ad:

   * It parses the MAC, RSSI, and data.
   * Encodes the result in CBOR.
   * Sends the payload using a WPC-compatible UART frame.
3. **nRF9151** receives this data via UART.

   * SLIP decoding and CRC verification occur.
   * It wraps the payload in a `waps_frame_t` structure (DSAP).
   * The data is injected into the mesh via the Wirepas stack.

---

## BLEScanner (EFR32MG26) Software Design

* **BLEScannerTask**: Initializes serial port and starts BLE scanning.
* **sl\_bt\_on\_event**: Dispatches events from the Bluetooth stack.
* **handle\_scanner\_event**: Extracts, logs, encodes, and transmits BLE data.
* **encode\_ble\_advertisement\_to\_cbor**: Compresses advertisement info.
* **send\_ble\_data\_via\_wpc**: Formats the payload and sends it over UART.

### BLE Event Handling

* `sl_bt_evt_scanner_legacy_advertisement_report_id`
* `sl_bt_evt_scanner_extended_advertisement_report_id`

---

## Wirepas Integration on nRF9151

* **Dual-MCU setup** with `Dualmcu_lib_init()` to manage UART reception.
* Uses `waps_frame_t` with:

  * `DSAP_DATA_TX_REQUEST_CODE`
  * Matching source/destination endpoints
* **No dynamic provisioning**: All credentials (network address, channel, keys) are **hardcoded** in `config.mk`.

### Example `config.mk`

```makefile
default_network_address ?= 5000
default_network_channel ?= 1
default_network_authen_key ?= 0x12,...,0x12
default_network_cipher_key ?= 0x12,...,0x12
```

> Provisioning must be completed at build time.

---

## Serial Frame Format (UART)

* **Encoding**: SLIP with CRC
* **Structure**:

  * `sfunc`, `sfid`, `splen`, payload (CBOR)
* Data is placed in `dsap_data_tx_req_t`:

```c
req->apdu_id = frame.sfid;
req->src_endpoint = BLE_SCAN_ENDPOINT;
req->dst_endpoint = BLE_SCAN_ENDPOINT;
req->apdu_len = cbor_len;
memcpy(req->apdu, cbor_buf, cbor_len);
```

---

## Dependencies

### EFR32MG26 Side

* **Silicon Labs Bluetooth SDK**
* **Wirepas Protocol Controller SDK**
* **CBOR library**
* **FreeRTOS**
* **UART driver**

### nRF9151 Side

* **Wirepas SDK** (dual MCU stack)
* **WAPS** (waps\_uart.c, waps.c)
* **HAL for UART and GPIO**
* **SLIP/CRC utilities**

---

## File/Directory Structure

```
project_root/
├── efr32_ble_scanner/
│   ├── BLEScanner.c
│   ├── app.c
│   └── cbor_utils.c
├── nrf91_wirepas_node/
│   ├── source/
│   │   └── reference_apps/dualmcu_app/
│   ├── libraries/dualmcu/waps/
│   ├── config.mk
├── README.md
```

---

## Debugging & Tools

* Use `printf()` or UART/RTT output for logs.
* **EFR32**: Logs BLE packet reception, CBOR encoding steps.
* **nRF9151**: Can log frame reception and parsing.
* Wireshark (with a Wirepas sniffer node) can be used for **mesh analysis**.

---

## Customization

* **UART Settings**: Match baudrate and flow control on both MCUs.
* **Endpoints**: Define custom `BLE_SCAN_ENDPOINT` for application routing.
* **CBOR Fields**: Modify `encode_ble_advertisement_to_cbor` to include additional sensor or tag fields.

---

## References

* [Silicon Labs Bluetooth SDK](https://docs.silabs.com/bluetooth/latest/)
* [Wirepas SDK and Docs](https://github.com/wirepas/wm-sdk)
* [CBOR Format](https://cbor.io/)
