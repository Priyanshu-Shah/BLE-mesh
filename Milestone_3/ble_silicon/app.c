/***************************************************************************//**
 * @file
 * @brief Core application logic.
 *******************************************************************************
 * # License
 * <b>Copyright 2024 Silicon Laboratories Inc. www.silabs.com</b>
 *******************************************************************************
 *
 * SPDX-License-Identifier: Zlib
 *
 * The licensor of this software is Silicon Laboratories Inc.
 *
 * This software is provided 'as-is', without any express or implied
 * warranty. In no event will the authors be held liable for any damages
 * arising from the use of this software.
 *
 * Permission is granted to anyone to use this software for any purpose,
 * including commercial applications, and to alter it and redistribute it
 * freely, subject to the following restrictions:
 *
 * 1. The origin of this software must not be misrepresented; you must not
 *    claim that you wrote the original software. If you use this software
 *    in a product, an acknowledgment in the product documentation would be
 *    appreciated but is not required.
 * 2. Altered source versions must be plainly marked as such, and must not be
 *    misrepresented as being the original software.
 * 3. This notice may not be removed or altered from any source distribution.
 *
 ******************************************************************************/
#include "sl_common.h"
#include "sl_bt_api.h"
#include "app_assert.h"
#include "app.h"
#include "FreeRTOS.h"
#include "task.h"

// Declare scanner event handler (implemented elsewhere)
void handle_scanner_event(sl_bt_msg_t *evt);
extern void BLEScannerTask(void *arg);

// The advertising set handle allocated from Bluetooth stack.
// static uint8_t advertising_set_handle = 0xff;

// Application Init.
SL_WEAK void app_init(void)
{
  xTaskCreate(BLEScannerTask, "BLEScan", 512, NULL, 2, NULL);
}

// Application Process Action.
SL_WEAK void app_process_action(void)
{
  if (app_is_process_required()) {
    /////////////////////////////////////////////////////////////////////////////
    // Put your additional application code here!                              //
    // This is will run each time app_proceed() is called.                     //
    // Do not call blocking functions from here!                               //
    /////////////////////////////////////////////////////////////////////////////
  }
}

/**************************************************************************//**
 * Bluetooth stack event handler.
 * This overrides the dummy weak implementation.
 *
 * @param[in] evt Event coming from the Bluetooth stack.
 *****************************************************************************/
void sl_bt_on_event(sl_bt_msg_t *evt)
{
  sl_status_t sc;

  switch (SL_BT_MSG_ID(evt->header)) {
    // -------------------------------
    // This event indicates the device has started and the radio is ready.
    // Do not call any stack command before receiving this boot event!
    case sl_bt_evt_system_boot_id:
      // // Create an advertising set.
      // sc = sl_bt_advertiser_create_set(&advertising_set_handle);
      // app_assert_status(sc);

      // // Generate data for advertising
      // sc = sl_bt_legacy_advertiser_generate_data(advertising_set_handle,
      //                                           sl_bt_advertiser_general_discoverable);
      // app_assert_status(sc);

      // // Set advertising interval to 100ms.
      // sc = sl_bt_advertiser_set_timing(
      //  advertising_set_handle,
      //  160, // min. adv. interval (milliseconds * 1.6)
      //  160, // max. adv. interval (milliseconds * 1.6)
      //  0,   // adv. duration
      //  0);  // max. num. adv. events
      // app_assert_status(sc);
      // // Start advertising and enable connections.
      // sc = sl_bt_legacy_advertiser_start(advertising_set_handle,
      //                                   sl_bt_legacy_advertiser_connectable);
      // app_assert_status(sc);
      break;

    // -------------------------------
    // This event indicates that a new connection was opened.
    case sl_bt_evt_connection_opened_id:
      break;

    // -------------------------------
    // This event indicates that a connection was closed.
    case sl_bt_evt_connection_closed_id:
      // // Generate data for advertising
      // sc = sl_bt_legacy_advertiser_generate_data(advertising_set_handle,
      //                                            sl_bt_advertiser_general_discoverable);
      // app_assert_status(sc);

      // Restart advertising after client has disconnected.
      // sc = sl_bt_legacy_advertiser_start(advertising_set_handle,
      //                                    sl_bt_legacy_advertiser_connectable);
      // app_assert_status(sc);
      break;

      // Forward scanner advertisement events to scanner handler
      case sl_bt_evt_scanner_legacy_advertisement_report_id:
      case sl_bt_evt_scanner_extended_advertisement_report_id:
        handle_scanner_event(evt);
        break;

    // -------------------------------
    // Default event handler.
    default:
      break;
  }
}
