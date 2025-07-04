/* Copyright 2017 Wirepas Ltd. All Rights Reserved.
 *
 * See file LICENSE.txt for full license details.
 *
 */

#ifndef FUNCTION_CODES_H__
#define FUNCTION_CODES_H__

typedef enum
{
    /* DSAP-DATA_TX */
    WAPS_FUNC_DSAP_DATA_TX_REQ = 0x01,
    WAPS_FUNC_DSAP_DATA_TX_CNF = 0x81,
    WAPS_FUNC_DSAP_DATA_TX_IND = 0x02,
    WAPS_FUNC_DSAP_DATA_TX_RSP = 0x82,
    /* DSAP-DATA_TX_FRAG */
    WAPS_FUNC_DSAP_DATA_TX_FRAG_REQ = 0x0F,
    WAPS_FUNC_DSAP_DATA_TX_FRAG_CNF = 0x8F,
    WAPS_FUNC_DSAP_DATA_RX_FRAG_IND = 0x10,
    WAPS_FUNC_DSAP_DATA_RX_FRAG_RSP = 0x90,
    /* DSAP-DATA_RX */
    WAPS_FUNC_DSAP_DATA_RX_IND = 0x03,
    WAPS_FUNC_DSAP_DATA_RX_RSP = 0x83,
    /* MSAP-INDICATION_POLL */
    WAPS_FUNC_MSAP_INDICATION_POLL_REQ = 0x04,
    WAPS_FUNC_MSAP_INDICATION_POLL_CNF = 0x84,
    /* MSAP-STACK_START */
    WAPS_FUNC_MSAP_STACK_START_REQ = 0x05,
    WAPS_FUNC_MSAP_STACK_START_CNF = 0x85,
    /* MSAP-STACK_STOP */
    WAPS_FUNC_MSAP_STACK_STOP_REQ = 0x06,
    WAPS_FUNC_MSAP_STACK_STOP_CNF = 0x86,
    /* MSAP-STACK_STATE */
    WAPS_FUNC_MSAP_STACK_STATE_IND = 0x07,
    WAPS_FUNC_MSAP_STACK_STATE_RSP = 0x87,
    /* MSAP-ATTRIBUTE_WRITE */
    WAPS_FUNC_MSAP_ATTR_WRITE_REQ = 0x0B,
    WAPS_FUNC_MSAP_ATTR_WRITE_CNF = 0x8B,
    /* MSAP-ATTRIBUTE_READ */
    WAPS_FUNC_MSAP_ATTR_READ_REQ = 0x0C,
    WAPS_FUNC_MSAP_ATTR_READ_CNF = 0x8C,
    /* CSAP-ATTRIBUTE_WRITE */
    WAPS_FUNC_CSAP_ATTR_WRITE_REQ = 0x0D,
    WAPS_FUNC_CSAP_ATTR_WRITE_CNF = 0x8D,
    /* CSAP-ATTRIBUTE_READ */
    WAPS_FUNC_CSAP_ATTR_READ_REQ = 0x0E,
    WAPS_FUNC_CSAP_ATTR_READ_CNF = 0x8E,
    /* CSAP-FACTORY_RESET */
    WAPS_FUNC_CSAP_FACTORY_RESET_REQ = 0x16,
    WAPS_FUNC_CSAP_FACTORY_RESET_CNF = 0x96,
    /* MSAP-SCRATCHPAD_START */
    WAPS_FUNC_MSAP_SCRATCHPAD_START_REQ = 0x17,
    WAPS_FUNC_MSAP_SCRATCHPAD_START_CNF = 0x97,
    /* MSAP-SCRATCHPAD_BLOCK */
    WAPS_FUNC_MSAP_SCRATCHPAD_BLOCK_REQ = 0x18,
    WAPS_FUNC_MSAP_SCRATCHPAD_BLOCK_CNF = 0x98,
    /* MSAP-SCRATCHPAD_STATUS */
    WAPS_FUNC_MSAP_SCRATCHPAD_STATUS_REQ = 0x19,
    WAPS_FUNC_MSAP_SCRATCHPAD_STATUS_CNF = 0x99,
    /* MSAP-SCRATCHPAD_BOOTABLE */
    WAPS_FUNC_MSAP_SCRATCHPAD_BOOTABLE_REQ = 0x1A,
    WAPS_FUNC_MSAP_SCRATCHPAD_BOOTABLE_CNF = 0x9A,
    /* MSAP-SCRATCHPAD_CLEAR */
    WAPS_FUNC_MSAP_SCRATCHPAD_CLEAR_REQ = 0x1B,
    WAPS_FUNC_MSAP_SCRATCHPAD_CLEAR_CNF = 0x9B,
    /* MSAP-REMOTE_STATUS_REQ */
    WAPS_FUNC_MSAP_REMOTE_STATUS_REQ = 0x1C,
    WAPS_FUNC_MSAP_REMOTE_STATUS_CNF = 0x9C,
    WAPS_FUNC_MSAP_REMOTE_STATUS_IND = 0x1D,
    WAPS_FUNC_MSAP_REMOTE_STATUS_RSP = 0x9D,
    /* MSAP-REMOTE_UPDATE_REQ */
    DEPRECATED_WAPS_FUNC_MSAP_REMOTE_UPDATE_REQ = 0x1E,
    DEPRECATED_WAPS_FUNC_MSAP_REMOTE_UPDATE_CNF = 0x9E,
    /* DSAP-DATA_TX with non-zero initial travel time */
    WAPS_FUNC_DSAP_DATA_TX_TT_REQ = 0x1F,
    WAPS_FUNC_DSAP_DATA_TX_TT_CNF = 0x9F,
    /* MSAP-GET-NBORS */
    WAPS_FUNC_MSAP_GET_NBORS_REQ = 0x20,
    WAPS_FUNC_MSAP_GET_NBORS_CNF = 0xA0,
    /* MSAP-SCAN-NBORS */
    WAPS_FUNC_MSAP_SCAN_NBORS_REQ = 0x21,
    WAPS_FUNC_MSAP_SCAN_NBORS_CNF = 0xA1,
    WAPS_FUNC_MSAP_SCAN_NBORS_IND = 0x22,
    WAPS_FUNC_MSAP_SCAN_NBORS_RSP = 0xA2,
    /* MSAP-INSTALL_QUALITY */
    WAPS_FUNC_MSAP_GET_INSTALL_QUALITY_REQ = 0x23,
    WAPS_FUNC_MSAP_GET_INSTALL_QUALITY_CNF = 0xA3,
    /* MSAP-SCRATCHPAD_TARGET_WRITE */
    WAPS_FUNC_MSAP_SCRATCHPAD_TARGET_WRITE_REQ = 0x26,
    WAPS_FUNC_MSAP_SCRATCHPAD_TARGET_WRITE_CNF = 0xA6,
    /* MSAP-SCRATCHPAD_TARGET_READ */
    WAPS_FUNC_MSAP_SCRATCHPAD_TARGET_READ_REQ = 0x27,
    WAPS_FUNC_MSAP_SCRATCHPAD_TARGET_READ_CNF = 0xA7,
    /* MSAP-SCRATCHPAD_BLOCK_READ */
    WAPS_FUNC_MSAP_SCRATCHPAD_BLOCK_READ_REQ = 0x28,
    WAPS_FUNC_MSAP_SCRATCHPAD_BLOCK_READ_CNF = 0xA8,
    /* MSAP-SINK_COST_WRITE */
    WAPS_FUNC_MSAP_SINK_COST_WRITE_REQ = 0x38,
    WAPS_FUNC_MSAP_SINK_COST_WRITE_CNF = 0xB8,
    /* MSAP-SINK_COST_READ */
    WAPS_FUNC_MSAP_SINK_COST_READ_REQ = 0x39,
    WAPS_FUNC_MSAP_SINK_COST_READ_CNF = 0xB9,
    /* MSAP-APP_CONFIG_DATA_WRITE */
    WAPS_FUNC_MSAP_APP_CONFIG_WRITE_REQ = 0x3A,
    WAPS_FUNC_MSAP_APP_CONFIG_WRITE_CNF = 0xBA,
    /* MSAP-APP_CONFIG_DATA_READ */
    WAPS_FUNC_MSAP_APP_CONFIG_READ_REQ = 0x3B,
    WAPS_FUNC_MSAP_APP_CONFIG_READ_CNF = 0xBB,
    /* MSAP-APP_CONFIG_DATA_RX */
    WAPS_FUNC_MSAP_APP_CONFIG_RX_IND = 0x3F,
    WAPS_FUNC_MSAP_APP_CONFIG_RX_RSP = 0xBF,
    /* MSAP-SLEEP REQ */
    WAPS_FUNC_MSAP_STACK_SLEEP_REQ = 0x40,
    WAPS_FUNC_MSAP_STACK_SLEEP_REQ_CNF = 0xC0,
    /* MSAP-SLEEP STOP REQ  */
    WAPS_FUNC_MSAP_STACK_SLEEP_STOP_REQ = 0x41,
    WAPS_FUNC_MSAP_STACK_SLEEP_STOP_CNF = 0xC1,
    /* MSAP-SLEEP STATE GET REQ  */
    WAPS_FUNC_MSAP_STACK_SLEEP_STATE_GET_REQ = 0x42,
    WAPS_FUNC_MSAP_STACK_SLEEP_STATE_GET_RSP = 0xC2,

    /* MSAP-SLEEP GOTOSLEEPINFO REQ */
    WAPS_FUNC_MSAP_STACK_SLEEP_GOTOSLEEPINFO_REQ = 0x4C,
    WAPS_FUNC_MSAP_STACK_SLEEP_GOTOSLEEPINFO_RSP = 0xCC,

    /* MSAP-MAX_QUEUE_TIME_WRITE REQ */
    DEPRECATED_WAPS_FUNC_MSAP_MAX_MSG_QUEUEING_TIME_WRITE_REQ = 0x4F,
    DEPRECATED_WAPS_FUNC_MSAP_MAX_MSG_QUEUEING_TIME_WRITE_CNF = 0xCF,
    /* MSAP-MAX_QUEUE_TIME_READ REQ */
    DEPRECATED_WAPS_FUNC_MSAP_MAX_MSG_QUEUEING_TIME_READ_REQ = 0x50,
    DEPRECATED_WAPS_FUNC_MSAP_MAX_MSG_QUEUEING_TIME_READ_CNF = 0xD0,

    /* Reserved request ids (only present in Remote API). */
    WAPS_FUNC_RESERVED_REMOTE_API_1_REQ = 0x60,
    WAPS_FUNC_RESERVED_REMOTE_API_1_CNF = 0xE0,
    WAPS_FUNC_RESERVED_REMOTE_API_2_REQ = 0x61,
    WAPS_FUNC_RESERVED_REMOTE_API_2_CNF = 0xE1,
    WAPS_FUNC_RESERVED_REMOTE_API_3_REQ = 0x62,
    WAPS_FUNC_RESERVED_REMOTE_API_3_CNF = 0xE2,
    WAPS_FUNC_RESERVED_REMOTE_API_4_REQ = 0x63,
    WAPS_FUNC_RESERVED_REMOTE_API_4_CNF = 0xE3,

} waps_func_e;

/* When you add/remove functions, make sure you update the tables below */

#define DSAP_REQUESTS                   \
{                                       \
    WAPS_FUNC_DSAP_DATA_TX_REQ,         \
    WAPS_FUNC_DSAP_DATA_TX_TT_REQ,      \
    WAPS_FUNC_DSAP_DATA_TX_FRAG_REQ,    \
}

#define MSAP_REQUESTS                               \
{                                                   \
    WAPS_FUNC_MSAP_INDICATION_POLL_REQ,             \
    WAPS_FUNC_MSAP_STACK_START_REQ,                 \
    WAPS_FUNC_MSAP_STACK_STOP_REQ,                  \
    WAPS_FUNC_MSAP_ATTR_WRITE_REQ,                  \
    WAPS_FUNC_MSAP_ATTR_READ_REQ,                   \
    WAPS_FUNC_MSAP_SCRATCHPAD_START_REQ,            \
    WAPS_FUNC_MSAP_SCRATCHPAD_BLOCK_REQ,            \
    WAPS_FUNC_MSAP_SCRATCHPAD_STATUS_REQ,           \
    WAPS_FUNC_MSAP_SCRATCHPAD_BOOTABLE_REQ,         \
    WAPS_FUNC_MSAP_SCRATCHPAD_CLEAR_REQ,            \
    WAPS_FUNC_MSAP_REMOTE_STATUS_REQ,               \
    WAPS_FUNC_MSAP_GET_NBORS_REQ,                   \
    WAPS_FUNC_MSAP_SCAN_NBORS_REQ,                  \
    WAPS_FUNC_MSAP_GET_INSTALL_QUALITY_REQ,         \
    WAPS_FUNC_MSAP_SINK_COST_WRITE_REQ,             \
    WAPS_FUNC_MSAP_SINK_COST_READ_REQ,              \
    WAPS_FUNC_MSAP_APP_CONFIG_WRITE_REQ,            \
    WAPS_FUNC_MSAP_APP_CONFIG_READ_REQ,             \
    WAPS_FUNC_MSAP_STACK_SLEEP_REQ,                 \
    WAPS_FUNC_MSAP_STACK_SLEEP_STOP_REQ,            \
    WAPS_FUNC_MSAP_STACK_SLEEP_STATE_GET_REQ,       \
    WAPS_FUNC_MSAP_STACK_SLEEP_GOTOSLEEPINFO_REQ,   \
    WAPS_FUNC_MSAP_SCRATCHPAD_TARGET_READ_REQ,      \
    WAPS_FUNC_MSAP_SCRATCHPAD_TARGET_WRITE_REQ,     \
    WAPS_FUNC_MSAP_SCRATCHPAD_BLOCK_READ_REQ        \
}

#define CSAP_REQUESTS                   \
{                                       \
    WAPS_FUNC_CSAP_ATTR_WRITE_REQ,      \
    WAPS_FUNC_CSAP_ATTR_READ_REQ,       \
    WAPS_FUNC_CSAP_FACTORY_RESET_REQ,   \
}

#define WAPS_CONFIRMATIONS                          \
{                                                   \
    WAPS_FUNC_DSAP_DATA_TX_CNF,                     \
    WAPS_FUNC_DSAP_DATA_TX_FRAG_CNF,                \
    WAPS_FUNC_MSAP_INDICATION_POLL_CNF,             \
    WAPS_FUNC_MSAP_STACK_START_CNF,                 \
    WAPS_FUNC_MSAP_STACK_STOP_CNF,                  \
    WAPS_FUNC_MSAP_APP_CONFIG_WRITE_CNF,            \
    WAPS_FUNC_MSAP_APP_CONFIG_READ_CNF,             \
    WAPS_FUNC_MSAP_ATTR_WRITE_CNF,                  \
    WAPS_FUNC_MSAP_ATTR_READ_CNF,                   \
    WAPS_FUNC_MSAP_GET_NBORS_CNF,                   \
    WAPS_FUNC_MSAP_SCAN_NBORS_CNF,                  \
    WAPS_FUNC_MSAP_GET_INSTALL_QUALITY_CNF,         \
    WAPS_FUNC_MSAP_SINK_COST_WRITE_CNF,             \
    WAPS_FUNC_MSAP_SINK_COST_READ_CNF,              \
    WAPS_FUNC_CSAP_ATTR_WRITE_CNF,                  \
    WAPS_FUNC_CSAP_ATTR_READ_CNF,                   \
    WAPS_FUNC_CSAP_FACTORY_RESET_CNF,               \
    WAPS_FUNC_MSAP_SCRATCHPAD_START_CNF,            \
    WAPS_FUNC_MSAP_SCRATCHPAD_BLOCK_CNF,            \
    WAPS_FUNC_MSAP_SCRATCHPAD_STATUS_CNF,           \
    WAPS_FUNC_MSAP_SCRATCHPAD_BOOTABLE_CNF,         \
    WAPS_FUNC_MSAP_SCRATCHPAD_CLEAR_CNF,            \
    WAPS_FUNC_MSAP_REMOTE_STATUS_CNF,               \
    WAPS_FUNC_DSAP_DATA_TX_TT_CNF,                  \
    WAPS_FUNC_MSAP_APP_CONFIG_WRITE_CNF,            \
    WAPS_FUNC_MSAP_APP_CONFIG_READ_CNF,             \
    WAPS_FUNC_MSAP_STACK_SLEEP_REQ_CNF,             \
    WAPS_FUNC_MSAP_STACK_SLEEP_STOP_CNF,            \
    WAPS_FUNC_MSAP_SCRATCHPAD_TARGET_READ_CNF,      \
    WAPS_FUNC_MSAP_SCRATCHPAD_TARGET_WRITE_CNF,     \
    WAPS_FUNC_MSAP_SCRATCHPAD_BLOCK_READ_CNF,       \
}

#define WAPS_INDICATIONS                            \
{                                                   \
    WAPS_FUNC_DSAP_DATA_TX_IND,                     \
    WAPS_FUNC_DSAP_DATA_RX_FRAG_IND,                \
    WAPS_FUNC_DSAP_DATA_RX_IND,                     \
    WAPS_FUNC_MSAP_STACK_STATE_IND,                 \
    WAPS_FUNC_MSAP_APP_CONFIG_RX_IND,               \
    WAPS_FUNC_MSAP_REMOTE_STATUS_IND,               \
    WAPS_FUNC_MSAP_SCAN_NBORS_IND,                  \
}

#define WAPS_RESPONSES                              \
{                                                   \
    WAPS_FUNC_DSAP_DATA_TX_RSP,                     \
    WAPS_FUNC_DSAP_DATA_RX_FRAG_RSP,                \
    WAPS_FUNC_DSAP_DATA_RX_RSP,                     \
    WAPS_FUNC_MSAP_STACK_STATE_RSP,                 \
    WAPS_FUNC_MSAP_APP_CONFIG_RX_RSP,               \
    WAPS_FUNC_MSAP_REMOTE_STATUS_RSP,               \
    WAPS_FUNC_MSAP_SCAN_NBORS_RSP,                  \
    WAPS_FUNC_MSAP_STACK_SLEEP_STATE_GET_RSP,       \
    WAPS_FUNC_MSAP_STACK_SLEEP_GOTOSLEEPINFO_RSP,   \
}

/** \brief  Check if given func code is a request
 *  \param  func
 *          Function code to check
 */
bool WapsFunc_isRequest(uint8_t func);

/** \brief  Check if given func code is a DSAP request
 *  \param  func
 *          Function code to check
 */
bool WapsFunc_isDsapRequest(uint8_t func);

/** \brief  Check if given func code is a MSAP request
 *  \param  func
 *          Function code to check
 */
bool WapsFunc_isMsapRequest(uint8_t func);

/** \brief  Check if given func code is a CSAP request
 *  \param  func
 *          Function code to check
 */
bool WapsFunc_isCsapRequest(uint8_t func);

/** \brief  Check if given func code is a confirmation
 *  \param  func
 *          Function code to check
 */
bool WapsFunc_isConfirmation(uint8_t func);

/** \brief  Check if given func code is an indication
 *  \param  func
 *          Function code to check
 */
bool WapsFunc_isIndication(uint8_t func);

/** \brief  Check if given func code is a response
 *  \param  func
 *          Function code to check
 */
bool WapsFunc_isResponse(uint8_t func);

#endif
