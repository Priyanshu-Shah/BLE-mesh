/*
 * Copyright (c) 2017 - 2023, Nordic Semiconductor ASA
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice, this
 *    list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * 3. Neither the name of the copyright holder nor the names of its
 *    contributors may be used to endorse or promote products derived from this
 *    software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef NRFX_CONFIG_NRF52832_H__
#define NRFX_CONFIG_NRF52832_H__

#ifndef NRFX_CONFIG_H__
#error "This file should not be included directly. Include nrfx_config.h instead."
#endif


/**
 * @brief NRFX_DEFAULT_IRQ_PRIORITY
 *
 * Integer value. Minimum: 0 Maximum: 7
 */
#ifndef NRFX_DEFAULT_IRQ_PRIORITY
#define NRFX_DEFAULT_IRQ_PRIORITY 7
#endif

/**
 * @brief NRFX_CLOCK_ENABLED
 *
 * Boolean. Accepted values 0 and 1.
 */
#ifndef NRFX_CLOCK_ENABLED
#define NRFX_CLOCK_ENABLED 0
#endif

/**
 * @brief NRFX_CLOCK_CONFIG_LF_SRC
 *
 * Integer value.
 * Supported values:
 * - RC                  = 0
 * - XTAL                = 1
 * - Synth               = 2
 * - External Low Swing  = 131073
 * - External Full Swing = 196609
 */
#ifndef NRFX_CLOCK_CONFIG_LF_SRC
#define NRFX_CLOCK_CONFIG_LF_SRC 1
#endif

/**
 * @brief NRFX_CLOCK_CONFIG_LF_CAL_ENABLED
 *
 * Boolean. Accepted values 0 and 1.
 */
#ifndef NRFX_CLOCK_CONFIG_LF_CAL_ENABLED
#define NRFX_CLOCK_CONFIG_LF_CAL_ENABLED 0
#endif

/**
 * @brief NRFX_CLOCK_CONFIG_CT_ENABLED
 *
 * Boolean. Accepted values 0 and 1.
 */
#ifndef NRFX_CLOCK_CONFIG_CT_ENABLED
#define NRFX_CLOCK_CONFIG_CT_ENABLED 1
#endif

/**
 * @brief NRFX_CLOCK_CONFIG_LFXO_TWO_STAGE_ENABLED
 *
 * Boolean. Accepted values 0 and 1.
 */
#ifndef NRFX_CLOCK_CONFIG_LFXO_TWO_STAGE_ENABLED
#define NRFX_CLOCK_CONFIG_LFXO_TWO_STAGE_ENABLED 0
#endif

/**
 * @brief NRFX_CLOCK_DEFAULT_CONFIG_IRQ_PRIORITY
 *
 * Integer value. Minimum: 0 Maximum: 7
 */
#ifndef NRFX_CLOCK_DEFAULT_CONFIG_IRQ_PRIORITY
#define NRFX_CLOCK_DEFAULT_CONFIG_IRQ_PRIORITY NRFX_DEFAULT_IRQ_PRIORITY
#endif

/**
 * @brief NRFX_CLOCK_CONFIG_LOG_ENABLED
 *
 * Boolean. Accepted values 0 and 1.
 */
#ifndef NRFX_CLOCK_CONFIG_LOG_ENABLED
#define NRFX_CLOCK_CONFIG_LOG_ENABLED 0
#endif

/**
 * @brief NRFX_CLOCK_CONFIG_LOG_LEVEL
 *
 * Integer value.
 * Supported values:
 * - Off     = 0
 * - Error   = 1
 * - Warning = 2
 * - Info    = 3
 * - Debug   = 4
 */
#ifndef NRFX_CLOCK_CONFIG_LOG_LEVEL
#define NRFX_CLOCK_CONFIG_LOG_LEVEL 3
#endif

/**
 * @brief NRFX_COMP_ENABLED
 *
 * Boolean. Accepted values 0 and 1.
 */
#ifndef NRFX_COMP_ENABLED
#define NRFX_COMP_ENABLED 0
#endif

/**
 * @brief NRFX_COMP_DEFAULT_CONFIG_IRQ_PRIORITY
 *
 * Integer value. Minimum: 0 Maximum: 7
 */
#ifndef NRFX_COMP_DEFAULT_CONFIG_IRQ_PRIORITY
#define NRFX_COMP_DEFAULT_CONFIG_IRQ_PRIORITY NRFX_DEFAULT_IRQ_PRIORITY
#endif

/**
 * @brief NRFX_COMP_CONFIG_LOG_ENABLED
 *
 * Boolean. Accepted values 0 and 1.
 */
#ifndef NRFX_COMP_CONFIG_LOG_ENABLED
#define NRFX_COMP_CONFIG_LOG_ENABLED 0
#endif

/**
 * @brief NRFX_COMP_CONFIG_LOG_LEVEL
 *
 * Integer value.
 * Supported values:
 * - Off     = 0
 * - Error   = 1
 * - Warning = 2
 * - Info    = 3
 * - Debug   = 4
 */
#ifndef NRFX_COMP_CONFIG_LOG_LEVEL
#define NRFX_COMP_CONFIG_LOG_LEVEL 3
#endif

/**
 * @brief NRFX_EGU_ENABLED
 *
 * Boolean. Accepted values 0 and 1.
 */
#ifndef NRFX_EGU_ENABLED
#define NRFX_EGU_ENABLED 0
#endif

/**
 * @brief NRFX_EGU_DEFAULT_CONFIG_IRQ_PRIORITY
 *
 * Integer value. Minimum: 0 Maximum: 7
 */
#ifndef NRFX_EGU_DEFAULT_CONFIG_IRQ_PRIORITY
#define NRFX_EGU_DEFAULT_CONFIG_IRQ_PRIORITY NRFX_DEFAULT_IRQ_PRIORITY
#endif

/**
 * @brief NRFX_EGU0_ENABLED
 *
 * Boolean. Accepted values 0 and 1.
 */
#ifndef NRFX_EGU0_ENABLED
#define NRFX_EGU0_ENABLED 0
#endif

/**
 * @brief NRFX_EGU1_ENABLED
 *
 * Boolean. Accepted values 0 and 1.
 */
#ifndef NRFX_EGU1_ENABLED
#define NRFX_EGU1_ENABLED 0
#endif

/**
 * @brief NRFX_EGU2_ENABLED
 *
 * Boolean. Accepted values 0 and 1.
 */
#ifndef NRFX_EGU2_ENABLED
#define NRFX_EGU2_ENABLED 0
#endif

/**
 * @brief NRFX_EGU3_ENABLED
 *
 * Boolean. Accepted values 0 and 1.
 */
#ifndef NRFX_EGU3_ENABLED
#define NRFX_EGU3_ENABLED 0
#endif

/**
 * @brief NRFX_EGU4_ENABLED
 *
 * Boolean. Accepted values 0 and 1.
 */
#ifndef NRFX_EGU4_ENABLED
#define NRFX_EGU4_ENABLED 0
#endif

/**
 * @brief NRFX_EGU5_ENABLED
 *
 * Boolean. Accepted values 0 and 1.
 */
#ifndef NRFX_EGU5_ENABLED
#define NRFX_EGU5_ENABLED 0
#endif

/**
 * @brief NRFX_GPIOTE_ENABLED
 *
 * Boolean. Accepted values 0 and 1.
 */
#ifndef NRFX_GPIOTE_ENABLED
#define NRFX_GPIOTE_ENABLED 0
#endif

/**
 * @brief NRFX_GPIOTE_DEFAULT_CONFIG_IRQ_PRIORITY
 *
 * Integer value. Minimum: 0 Maximum: 7
 */
#ifndef NRFX_GPIOTE_DEFAULT_CONFIG_IRQ_PRIORITY
#define NRFX_GPIOTE_DEFAULT_CONFIG_IRQ_PRIORITY NRFX_DEFAULT_IRQ_PRIORITY
#endif

/**
 * @brief NRFX_GPIOTE_CONFIG_NUM_OF_EVT_HANDLERS
 *
 * Integer value. Minimum: 0 Maximum: 15
 */
#ifndef NRFX_GPIOTE_CONFIG_NUM_OF_EVT_HANDLERS
#define NRFX_GPIOTE_CONFIG_NUM_OF_EVT_HANDLERS 2
#endif

/**
 * @brief NRFX_GPIOTE_CONFIG_LOG_ENABLED
 *
 * Boolean. Accepted values 0 and 1.
 */
#ifndef NRFX_GPIOTE_CONFIG_LOG_ENABLED
#define NRFX_GPIOTE_CONFIG_LOG_ENABLED 0
#endif

/**
 * @brief NRFX_GPIOTE_CONFIG_LOG_LEVEL
 *
 * Integer value.
 * Supported values:
 * - Off     = 0
 * - Error   = 1
 * - Warning = 2
 * - Info    = 3
 * - Debug   = 4
 */
#ifndef NRFX_GPIOTE_CONFIG_LOG_LEVEL
#define NRFX_GPIOTE_CONFIG_LOG_LEVEL 3
#endif

/**
 * @brief NRFX_I2S_ENABLED
 *
 * Boolean. Accepted values 0 and 1.
 */
#ifndef NRFX_I2S_ENABLED
#define NRFX_I2S_ENABLED 0
#endif

/**
 * @brief NRFX_I2S_DEFAULT_CONFIG_IRQ_PRIORITY
 *
 * Integer value. Minimum: 0 Maximum: 7
 */
#ifndef NRFX_I2S_DEFAULT_CONFIG_IRQ_PRIORITY
#define NRFX_I2S_DEFAULT_CONFIG_IRQ_PRIORITY NRFX_DEFAULT_IRQ_PRIORITY
#endif

/**
 * @brief NRFX_I2S_CONFIG_LOG_ENABLED
 *
 * Boolean. Accepted values 0 and 1.
 */
#ifndef NRFX_I2S_CONFIG_LOG_ENABLED
#define NRFX_I2S_CONFIG_LOG_ENABLED 0
#endif

/**
 * @brief NRFX_I2S_CONFIG_LOG_LEVEL
 *
 * Integer value.
 * Supported values:
 * - Off     = 0
 * - Error   = 1
 * - Warning = 2
 * - Info    = 3
 * - Debug   = 4
 */
#ifndef NRFX_I2S_CONFIG_LOG_LEVEL
#define NRFX_I2S_CONFIG_LOG_LEVEL 3
#endif

/**
 * @brief NRFX_LPCOMP_ENABLED
 *
 * Boolean. Accepted values 0 and 1.
 */
#ifndef NRFX_LPCOMP_ENABLED
#define NRFX_LPCOMP_ENABLED 0
#endif

/**
 * @brief NRFX_LPCOMP_DEFAULT_CONFIG_IRQ_PRIORITY
 *
 * Integer value. Minimum: 0 Maximum: 7
 */
#ifndef NRFX_LPCOMP_DEFAULT_CONFIG_IRQ_PRIORITY
#define NRFX_LPCOMP_DEFAULT_CONFIG_IRQ_PRIORITY NRFX_DEFAULT_IRQ_PRIORITY
#endif

/**
 * @brief NRFX_LPCOMP_CONFIG_LOG_ENABLED
 *
 * Boolean. Accepted values 0 and 1.
 */
#ifndef NRFX_LPCOMP_CONFIG_LOG_ENABLED
#define NRFX_LPCOMP_CONFIG_LOG_ENABLED 0
#endif

/**
 * @brief NRFX_LPCOMP_CONFIG_LOG_LEVEL
 *
 * Integer value.
 * Supported values:
 * - Off     = 0
 * - Error   = 1
 * - Warning = 2
 * - Info    = 3
 * - Debug   = 4
 */
#ifndef NRFX_LPCOMP_CONFIG_LOG_LEVEL
#define NRFX_LPCOMP_CONFIG_LOG_LEVEL 3
#endif

/**
 * @brief NRFX_NFCT_ENABLED
 *
 * Boolean. Accepted values 0 and 1.
 */
#ifndef NRFX_NFCT_ENABLED
#define NRFX_NFCT_ENABLED 0
#endif

/**
 * @brief NRFX_NFCT_DEFAULT_CONFIG_IRQ_PRIORITY
 *
 * Integer value. Minimum: 0 Maximum: 7
 */
#ifndef NRFX_NFCT_DEFAULT_CONFIG_IRQ_PRIORITY
#define NRFX_NFCT_DEFAULT_CONFIG_IRQ_PRIORITY NRFX_DEFAULT_IRQ_PRIORITY
#endif

/**
 * @brief NRFX_NFCT_CONFIG_TIMER_INSTANCE_ID - Timer instance used for workarounds in the driver.
 *
 * Integer value. Minimum: 0 Maximum: 5
 */
#ifndef NRFX_NFCT_CONFIG_TIMER_INSTANCE_ID
#define NRFX_NFCT_CONFIG_TIMER_INSTANCE_ID 4
#endif

/**
 * @brief NRFX_NFCT_CONFIG_LOG_ENABLED
 *
 * Boolean. Accepted values 0 and 1.
 */
#ifndef NRFX_NFCT_CONFIG_LOG_ENABLED
#define NRFX_NFCT_CONFIG_LOG_ENABLED 0
#endif

/**
 * @brief NRFX_NFCT_CONFIG_LOG_LEVEL
 *
 * Integer value.
 * Supported values:
 * - Off     = 0
 * - Error   = 1
 * - Warning = 2
 * - Info    = 3
 * - Debug   = 4
 */
#ifndef NRFX_NFCT_CONFIG_LOG_LEVEL
#define NRFX_NFCT_CONFIG_LOG_LEVEL 3
#endif

/**
 * @brief NRFX_NVMC_ENABLED
 *
 * Boolean. Accepted values 0 and 1.
 */
#ifndef NRFX_NVMC_ENABLED
#define NRFX_NVMC_ENABLED 0
#endif

/**
 * @brief NRFX_PDM_ENABLED
 *
 * Boolean. Accepted values 0 and 1.
 */
#ifndef NRFX_PDM_ENABLED
#define NRFX_PDM_ENABLED 0
#endif

/**
 * @brief NRFX_PDM_DEFAULT_CONFIG_IRQ_PRIORITY
 *
 * Integer value. Minimum: 0 Maximum: 7
 */
#ifndef NRFX_PDM_DEFAULT_CONFIG_IRQ_PRIORITY
#define NRFX_PDM_DEFAULT_CONFIG_IRQ_PRIORITY NRFX_DEFAULT_IRQ_PRIORITY
#endif

/**
 * @brief NRFX_PDM_CONFIG_LOG_ENABLED
 *
 * Boolean. Accepted values 0 and 1.
 */
#ifndef NRFX_PDM_CONFIG_LOG_ENABLED
#define NRFX_PDM_CONFIG_LOG_ENABLED 0
#endif

/**
 * @brief NRFX_PDM_CONFIG_LOG_LEVEL
 *
 * Integer value.
 * Supported values:
 * - Off     = 0
 * - Error   = 1
 * - Warning = 2
 * - Info    = 3
 * - Debug   = 4
 */
#ifndef NRFX_PDM_CONFIG_LOG_LEVEL
#define NRFX_PDM_CONFIG_LOG_LEVEL 3
#endif

/**
 * @brief NRFX_POWER_ENABLED
 *
 * Boolean. Accepted values 0 and 1.
 */
#ifndef NRFX_POWER_ENABLED
#define NRFX_POWER_ENABLED 0
#endif

/**
 * @brief NRFX_POWER_DEFAULT_CONFIG_IRQ_PRIORITY
 *
 * Integer value. Minimum: 0 Maximum: 7
 */
#ifndef NRFX_POWER_DEFAULT_CONFIG_IRQ_PRIORITY
#define NRFX_POWER_DEFAULT_CONFIG_IRQ_PRIORITY NRFX_DEFAULT_IRQ_PRIORITY
#endif

/**
 * @brief NRFX_PPI_ENABLED
 *
 * Boolean. Accepted values 0 and 1.
 */
#ifndef NRFX_PPI_ENABLED
#define NRFX_PPI_ENABLED 0
#endif

/**
 * @brief NRFX_PPI_CONFIG_LOG_ENABLED
 *
 * Boolean. Accepted values 0 and 1.
 */
#ifndef NRFX_PPI_CONFIG_LOG_ENABLED
#define NRFX_PPI_CONFIG_LOG_ENABLED 0
#endif

/**
 * @brief NRFX_PPI_CONFIG_LOG_LEVEL
 *
 * Integer value.
 * Supported values:
 * - Off     = 0
 * - Error   = 1
 * - Warning = 2
 * - Info    = 3
 * - Debug   = 4
 */
#ifndef NRFX_PPI_CONFIG_LOG_LEVEL
#define NRFX_PPI_CONFIG_LOG_LEVEL 3
#endif

/**
 * @brief NRFX_PRS_ENABLED
 *
 * Boolean. Accepted values 0 and 1.
 */
#ifndef NRFX_PRS_ENABLED
#define NRFX_PRS_ENABLED 0
#endif

/**
 * @brief NRFX_PRS_CONFIG_LOG_ENABLED
 *
 * Boolean. Accepted values 0 and 1.
 */
#ifndef NRFX_PRS_CONFIG_LOG_ENABLED
#define NRFX_PRS_CONFIG_LOG_ENABLED 0
#endif

/**
 * @brief NRFX_PRS_CONFIG_LOG_LEVEL
 *
 * Integer value.
 * Supported values:
 * - Off     = 0
 * - Error   = 1
 * - Warning = 2
 * - Info    = 3
 * - Debug   = 4
 */
#ifndef NRFX_PRS_CONFIG_LOG_LEVEL
#define NRFX_PRS_CONFIG_LOG_LEVEL 3
#endif

/**
 * @brief NRFX_PRS_BOX_0_ENABLED
 *
 * Boolean. Accepted values 0 and 1.
 */
#ifndef NRFX_PRS_BOX_0_ENABLED
#define NRFX_PRS_BOX_0_ENABLED 0
#endif

/**
 * @brief NRFX_PRS_BOX_1_ENABLED
 *
 * Boolean. Accepted values 0 and 1.
 */
#ifndef NRFX_PRS_BOX_1_ENABLED
#define NRFX_PRS_BOX_1_ENABLED 0
#endif

/**
 * @brief NRFX_PRS_BOX_2_ENABLED
 *
 * Boolean. Accepted values 0 and 1.
 */
#ifndef NRFX_PRS_BOX_2_ENABLED
#define NRFX_PRS_BOX_2_ENABLED 0
#endif

/**
 * @brief NRFX_PRS_BOX_3_ENABLED
 *
 * Boolean. Accepted values 0 and 1.
 */
#ifndef NRFX_PRS_BOX_3_ENABLED
#define NRFX_PRS_BOX_3_ENABLED 0
#endif

/**
 * @brief NRFX_PRS_BOX_4_ENABLED
 *
 * Boolean. Accepted values 0 and 1.
 */
#ifndef NRFX_PRS_BOX_4_ENABLED
#define NRFX_PRS_BOX_4_ENABLED 0
#endif

/**
 * @brief NRFX_PWM_ENABLED
 *
 * Boolean. Accepted values 0 and 1.
 */
#ifndef NRFX_PWM_ENABLED
#define NRFX_PWM_ENABLED 0
#endif

/**
 * @brief NRFX_PWM_DEFAULT_CONFIG_IRQ_PRIORITY
 *
 * Integer value. Minimum: 0 Maximum: 7
 */
#ifndef NRFX_PWM_DEFAULT_CONFIG_IRQ_PRIORITY
#define NRFX_PWM_DEFAULT_CONFIG_IRQ_PRIORITY NRFX_DEFAULT_IRQ_PRIORITY
#endif

/**
 * @brief NRFX_PWM_CONFIG_LOG_ENABLED
 *
 * Boolean. Accepted values 0 and 1.
 */
#ifndef NRFX_PWM_CONFIG_LOG_ENABLED
#define NRFX_PWM_CONFIG_LOG_ENABLED 0
#endif

/**
 * @brief NRFX_PWM_NRF52_ANOMALY_109_WORKAROUND_ENABLED - Enables nRF52 Anomaly 109 workaround for PWM.
 *
 * Boolean. Accepted values 0 and 1.
 */
#ifndef NRFX_PWM_NRF52_ANOMALY_109_WORKAROUND_ENABLED
#define NRFX_PWM_NRF52_ANOMALY_109_WORKAROUND_ENABLED 0
#endif

/**
 * @brief NRFX_PWM_NRF52_ANOMALY_109_EGU_INSTANCE - EGU instance used by the nRF52 Anomaly 109 workaround for PWM.
 *
 * Integer value.
 * Supported values:
 * - EGU0 = 0
 * - EGU1 = 1
 * - EGU2 = 2
 * - EGU3 = 3
 * - EGU4 = 4
 * - EGU5 = 5
 */
#ifndef NRFX_PWM_NRF52_ANOMALY_109_EGU_INSTANCE
#define NRFX_PWM_NRF52_ANOMALY_109_EGU_INSTANCE 5
#endif

/**
 * @brief NRFX_PWM_CONFIG_LOG_LEVEL
 *
 * Integer value.
 * Supported values:
 * - Off     = 0
 * - Error   = 1
 * - Warning = 2
 * - Info    = 3
 * - Debug   = 4
 */
#ifndef NRFX_PWM_CONFIG_LOG_LEVEL
#define NRFX_PWM_CONFIG_LOG_LEVEL 3
#endif

/**
 * @brief NRFX_PWM0_ENABLED
 *
 * Boolean. Accepted values 0 and 1.
 */
#ifndef NRFX_PWM0_ENABLED
#define NRFX_PWM0_ENABLED 0
#endif

/**
 * @brief NRFX_PWM1_ENABLED
 *
 * Boolean. Accepted values 0 and 1.
 */
#ifndef NRFX_PWM1_ENABLED
#define NRFX_PWM1_ENABLED 0
#endif

/**
 * @brief NRFX_PWM2_ENABLED
 *
 * Boolean. Accepted values 0 and 1.
 */
#ifndef NRFX_PWM2_ENABLED
#define NRFX_PWM2_ENABLED 0
#endif

/**
 * @brief NRFX_QDEC_ENABLED
 *
 * Boolean. Accepted values 0 and 1.
 */
#ifndef NRFX_QDEC_ENABLED
#define NRFX_QDEC_ENABLED 0
#endif

/**
 * @brief NRFX_QDEC_DEFAULT_CONFIG_IRQ_PRIORITY
 *
 * Integer value. Minimum: 0 Maximum: 7
 */
#ifndef NRFX_QDEC_DEFAULT_CONFIG_IRQ_PRIORITY
#define NRFX_QDEC_DEFAULT_CONFIG_IRQ_PRIORITY NRFX_DEFAULT_IRQ_PRIORITY
#endif

/**
 * @brief NRFX_QDEC_CONFIG_LOG_ENABLED
 *
 * Boolean. Accepted values 0 and 1.
 */
#ifndef NRFX_QDEC_CONFIG_LOG_ENABLED
#define NRFX_QDEC_CONFIG_LOG_ENABLED 0
#endif

/**
 * @brief NRFX_QDEC_CONFIG_LOG_LEVEL
 *
 * Integer value.
 * Supported values:
 * - Off     = 0
 * - Error   = 1
 * - Warning = 2
 * - Info    = 3
 * - Debug   = 4
 */
#ifndef NRFX_QDEC_CONFIG_LOG_LEVEL
#define NRFX_QDEC_CONFIG_LOG_LEVEL 3
#endif

/**
 * @brief NRFX_RNG_ENABLED
 *
 * Boolean. Accepted values 0 and 1.
 */
#ifndef NRFX_RNG_ENABLED
#define NRFX_RNG_ENABLED 0
#endif

/**
 * @brief NRFX_RNG_DEFAULT_CONFIG_IRQ_PRIORITY
 *
 * Integer value. Minimum: 0 Maximum: 7
 */
#ifndef NRFX_RNG_DEFAULT_CONFIG_IRQ_PRIORITY
#define NRFX_RNG_DEFAULT_CONFIG_IRQ_PRIORITY NRFX_DEFAULT_IRQ_PRIORITY
#endif

/**
 * @brief NRFX_RNG_CONFIG_LOG_ENABLED
 *
 * Boolean. Accepted values 0 and 1.
 */
#ifndef NRFX_RNG_CONFIG_LOG_ENABLED
#define NRFX_RNG_CONFIG_LOG_ENABLED 0
#endif

/**
 * @brief NRFX_RNG_CONFIG_LOG_LEVEL
 *
 * Integer value.
 * Supported values:
 * - Off     = 0
 * - Error   = 1
 * - Warning = 2
 * - Info    = 3
 * - Debug   = 4
 */
#ifndef NRFX_RNG_CONFIG_LOG_LEVEL
#define NRFX_RNG_CONFIG_LOG_LEVEL 3
#endif

/**
 * @brief NRFX_RTC_ENABLED
 *
 * Boolean. Accepted values 0 and 1.
 */
#ifndef NRFX_RTC_ENABLED
#define NRFX_RTC_ENABLED 0
#endif

/**
 * @brief NRFX_RTC_DEFAULT_CONFIG_IRQ_PRIORITY
 *
 * Integer value. Minimum: 0 Maximum: 7
 */
#ifndef NRFX_RTC_DEFAULT_CONFIG_IRQ_PRIORITY
#define NRFX_RTC_DEFAULT_CONFIG_IRQ_PRIORITY NRFX_DEFAULT_IRQ_PRIORITY
#endif

/**
 * @brief NRFX_RTC_CONFIG_LOG_ENABLED
 *
 * Boolean. Accepted values 0 and 1.
 */
#ifndef NRFX_RTC_CONFIG_LOG_ENABLED
#define NRFX_RTC_CONFIG_LOG_ENABLED 0
#endif

/**
 * @brief NRFX_RTC_CONFIG_LOG_LEVEL
 *
 * Integer value.
 * Supported values:
 * - Off     = 0
 * - Error   = 1
 * - Warning = 2
 * - Info    = 3
 * - Debug   = 4
 */
#ifndef NRFX_RTC_CONFIG_LOG_LEVEL
#define NRFX_RTC_CONFIG_LOG_LEVEL 3
#endif

/**
 * @brief NRFX_RTC0_ENABLED
 *
 * Boolean. Accepted values 0 and 1.
 */
#ifndef NRFX_RTC0_ENABLED
#define NRFX_RTC0_ENABLED 0
#endif

/**
 * @brief NRFX_RTC1_ENABLED
 *
 * Boolean. Accepted values 0 and 1.
 */
#ifndef NRFX_RTC1_ENABLED
#define NRFX_RTC1_ENABLED 0
#endif

/**
 * @brief NRFX_RTC2_ENABLED
 *
 * Boolean. Accepted values 0 and 1.
 */
#ifndef NRFX_RTC2_ENABLED
#define NRFX_RTC2_ENABLED 0
#endif

/**
 * @brief NRFX_SAADC_ENABLED
 *
 * Boolean. Accepted values 0 and 1.
 */
#ifndef NRFX_SAADC_ENABLED
#define NRFX_SAADC_ENABLED 0
#endif

/**
 * @brief NRFX_SAADC_DEFAULT_CONFIG_IRQ_PRIORITY
 *
 * Integer value. Minimum: 0 Maximum: 7
 */
#ifndef NRFX_SAADC_DEFAULT_CONFIG_IRQ_PRIORITY
#define NRFX_SAADC_DEFAULT_CONFIG_IRQ_PRIORITY NRFX_DEFAULT_IRQ_PRIORITY
#endif

/**
 * @brief NRFX_SAADC_CONFIG_LOG_ENABLED
 *
 * Boolean. Accepted values 0 and 1.
 */
#ifndef NRFX_SAADC_CONFIG_LOG_ENABLED
#define NRFX_SAADC_CONFIG_LOG_ENABLED 0
#endif

/**
 * @brief NRFX_SAADC_CONFIG_LOG_LEVEL
 *
 * Integer value.
 * Supported values:
 * - Off     = 0
 * - Error   = 1
 * - Warning = 2
 * - Info    = 3
 * - Debug   = 4
 */
#ifndef NRFX_SAADC_CONFIG_LOG_LEVEL
#define NRFX_SAADC_CONFIG_LOG_LEVEL 3
#endif

/**
 * @brief NRFX_SPI_ENABLED
 *
 * Boolean. Accepted values 0 and 1.
 */
#ifndef NRFX_SPI_ENABLED
#define NRFX_SPI_ENABLED 0
#endif

/**
 * @brief NRFX_SPI_DEFAULT_CONFIG_IRQ_PRIORITY
 *
 * Integer value. Minimum: 0 Maximum: 7
 */
#ifndef NRFX_SPI_DEFAULT_CONFIG_IRQ_PRIORITY
#define NRFX_SPI_DEFAULT_CONFIG_IRQ_PRIORITY NRFX_DEFAULT_IRQ_PRIORITY
#endif

/**
 * @brief NRFX_SPI_CONFIG_LOG_ENABLED
 *
 * Boolean. Accepted values 0 and 1.
 */
#ifndef NRFX_SPI_CONFIG_LOG_ENABLED
#define NRFX_SPI_CONFIG_LOG_ENABLED 0
#endif

/**
 * @brief NRFX_SPI_CONFIG_LOG_LEVEL
 *
 * Integer value.
 * Supported values:
 * - Off     = 0
 * - Error   = 1
 * - Warning = 2
 * - Info    = 3
 * - Debug   = 4
 */
#ifndef NRFX_SPI_CONFIG_LOG_LEVEL
#define NRFX_SPI_CONFIG_LOG_LEVEL 3
#endif

/**
 * @brief NRFX_SPI0_ENABLED
 *
 * Boolean. Accepted values 0 and 1.
 */
#ifndef NRFX_SPI0_ENABLED
#define NRFX_SPI0_ENABLED 0
#endif

/**
 * @brief NRFX_SPI1_ENABLED
 *
 * Boolean. Accepted values 0 and 1.
 */
#ifndef NRFX_SPI1_ENABLED
#define NRFX_SPI1_ENABLED 0
#endif

/**
 * @brief NRFX_SPI2_ENABLED
 *
 * Boolean. Accepted values 0 and 1.
 */
#ifndef NRFX_SPI2_ENABLED
#define NRFX_SPI2_ENABLED 0
#endif

/**
 * @brief NRFX_SPIM_ENABLED
 *
 * Boolean. Accepted values 0 and 1.
 */
#ifndef NRFX_SPIM_ENABLED
#define NRFX_SPIM_ENABLED 0
#endif

/**
 * @brief NRFX_SPIM_DEFAULT_CONFIG_IRQ_PRIORITY
 *
 * Integer value. Minimum: 0 Maximum: 7
 */
#ifndef NRFX_SPIM_DEFAULT_CONFIG_IRQ_PRIORITY
#define NRFX_SPIM_DEFAULT_CONFIG_IRQ_PRIORITY NRFX_DEFAULT_IRQ_PRIORITY
#endif

/**
 * @brief NRFX_SPIM_CONFIG_LOG_ENABLED
 *
 * Boolean. Accepted values 0 and 1.
 */
#ifndef NRFX_SPIM_CONFIG_LOG_ENABLED
#define NRFX_SPIM_CONFIG_LOG_ENABLED 0
#endif

/**
 * @brief NRFX_SPIM_NRF52_ANOMALY_109_WORKAROUND_ENABLED - Enables nRF52 Anomaly 109 workaround for SPIM.
 *
 * Boolean. Accepted values 0 and 1.
 */
#ifndef NRFX_SPIM_NRF52_ANOMALY_109_WORKAROUND_ENABLED
#define NRFX_SPIM_NRF52_ANOMALY_109_WORKAROUND_ENABLED 0
#endif

/**
 * @brief NRFX_SPIM_CONFIG_LOG_LEVEL
 *
 * Integer value.
 * Supported values:
 * - Off     = 0
 * - Error   = 1
 * - Warning = 2
 * - Info    = 3
 * - Debug   = 4
 */
#ifndef NRFX_SPIM_CONFIG_LOG_LEVEL
#define NRFX_SPIM_CONFIG_LOG_LEVEL 3
#endif

/**
 * @brief NRFX_SPIM0_ENABLED
 *
 * Boolean. Accepted values 0 and 1.
 */
#ifndef NRFX_SPIM0_ENABLED
#define NRFX_SPIM0_ENABLED 0
#endif

/**
 * @brief NRFX_SPIM1_ENABLED
 *
 * Boolean. Accepted values 0 and 1.
 */
#ifndef NRFX_SPIM1_ENABLED
#define NRFX_SPIM1_ENABLED 0
#endif

/**
 * @brief NRFX_SPIM2_ENABLED
 *
 * Boolean. Accepted values 0 and 1.
 */
#ifndef NRFX_SPIM2_ENABLED
#define NRFX_SPIM2_ENABLED 0
#endif

/**
 * @brief NRFX_SPIS_ENABLED
 *
 * Boolean. Accepted values 0 and 1.
 */
#ifndef NRFX_SPIS_ENABLED
#define NRFX_SPIS_ENABLED 0
#endif

/**
 * @brief NRFX_SPIS_DEFAULT_CONFIG_IRQ_PRIORITY
 *
 * Integer value. Minimum: 0 Maximum: 7
 */
#ifndef NRFX_SPIS_DEFAULT_CONFIG_IRQ_PRIORITY
#define NRFX_SPIS_DEFAULT_CONFIG_IRQ_PRIORITY NRFX_DEFAULT_IRQ_PRIORITY
#endif

/**
 * @brief NRFX_SPIS_CONFIG_LOG_ENABLED
 *
 * Boolean. Accepted values 0 and 1.
 */
#ifndef NRFX_SPIS_CONFIG_LOG_ENABLED
#define NRFX_SPIS_CONFIG_LOG_ENABLED 0
#endif

/**
 * @brief NRFX_SPIS_NRF52_ANOMALY_109_WORKAROUND_ENABLED - Enables nRF52 Anomaly 109 workaround for SPIS.
 *
 * Boolean. Accepted values 0 and 1.
 */
#ifndef NRFX_SPIS_NRF52_ANOMALY_109_WORKAROUND_ENABLED
#define NRFX_SPIS_NRF52_ANOMALY_109_WORKAROUND_ENABLED 0
#endif

/**
 * @brief NRFX_SPIS_CONFIG_LOG_LEVEL
 *
 * Integer value.
 * Supported values:
 * - Off     = 0
 * - Error   = 1
 * - Warning = 2
 * - Info    = 3
 * - Debug   = 4
 */
#ifndef NRFX_SPIS_CONFIG_LOG_LEVEL
#define NRFX_SPIS_CONFIG_LOG_LEVEL 3
#endif

/**
 * @brief NRFX_SPIS0_ENABLED
 *
 * Boolean. Accepted values 0 and 1.
 */
#ifndef NRFX_SPIS0_ENABLED
#define NRFX_SPIS0_ENABLED 0
#endif

/**
 * @brief NRFX_SPIS1_ENABLED
 *
 * Boolean. Accepted values 0 and 1.
 */
#ifndef NRFX_SPIS1_ENABLED
#define NRFX_SPIS1_ENABLED 0
#endif

/**
 * @brief NRFX_SPIS2_ENABLED
 *
 * Boolean. Accepted values 0 and 1.
 */
#ifndef NRFX_SPIS2_ENABLED
#define NRFX_SPIS2_ENABLED 0
#endif

/**
 * @brief NRFX_SYSTICK_ENABLED
 *
 * Boolean. Accepted values 0 and 1.
 */
#ifndef NRFX_SYSTICK_ENABLED
#define NRFX_SYSTICK_ENABLED 0
#endif

/**
 * @brief NRFX_TEMP_ENABLED
 *
 * Boolean. Accepted values 0 and 1.
 */
#ifndef NRFX_TEMP_ENABLED
#define NRFX_TEMP_ENABLED 0
#endif

/**
 * @brief NRFX_TEMP_DEFAULT_CONFIG_IRQ_PRIORITY
 *
 * Integer value. Minimum: 0 Maximum: 7
 */
#ifndef NRFX_TEMP_DEFAULT_CONFIG_IRQ_PRIORITY
#define NRFX_TEMP_DEFAULT_CONFIG_IRQ_PRIORITY NRFX_DEFAULT_IRQ_PRIORITY
#endif

/**
 * @brief NRFX_TEMP_CONFIG_LOG_ENABLED
 *
 * Boolean. Accepted values 0 and 1.
 */
#ifndef NRFX_TEMP_CONFIG_LOG_ENABLED
#define NRFX_TEMP_CONFIG_LOG_ENABLED 0
#endif

/**
 * @brief NRFX_TEMP_CONFIG_LOG_LEVEL
 *
 * Integer value.
 * Supported values:
 * - Off     = 0
 * - Error   = 1
 * - Warning = 2
 * - Info    = 3
 * - Debug   = 4
 */
#ifndef NRFX_TEMP_CONFIG_LOG_LEVEL
#define NRFX_TEMP_CONFIG_LOG_LEVEL 3
#endif

/**
 * @brief NRFX_TIMER_ENABLED
 *
 * Boolean. Accepted values 0 and 1.
 */
#ifndef NRFX_TIMER_ENABLED
#define NRFX_TIMER_ENABLED 0
#endif

/**
 * @brief NRFX_TIMER_DEFAULT_CONFIG_IRQ_PRIORITY
 *
 * Integer value. Minimum: 0 Maximum: 7
 */
#ifndef NRFX_TIMER_DEFAULT_CONFIG_IRQ_PRIORITY
#define NRFX_TIMER_DEFAULT_CONFIG_IRQ_PRIORITY NRFX_DEFAULT_IRQ_PRIORITY
#endif

/**
 * @brief NRFX_TIMER_CONFIG_LOG_ENABLED
 *
 * Boolean. Accepted values 0 and 1.
 */
#ifndef NRFX_TIMER_CONFIG_LOG_ENABLED
#define NRFX_TIMER_CONFIG_LOG_ENABLED 0
#endif

/**
 * @brief NRFX_TIMER_CONFIG_LOG_LEVEL
 *
 * Integer value.
 * Supported values:
 * - Off     = 0
 * - Error   = 1
 * - Warning = 2
 * - Info    = 3
 * - Debug   = 4
 */
#ifndef NRFX_TIMER_CONFIG_LOG_LEVEL
#define NRFX_TIMER_CONFIG_LOG_LEVEL 3
#endif

/**
 * @brief NRFX_TIMER0_ENABLED
 *
 * Boolean. Accepted values 0 and 1.
 */
#ifndef NRFX_TIMER0_ENABLED
#define NRFX_TIMER0_ENABLED 0
#endif

/**
 * @brief NRFX_TIMER1_ENABLED
 *
 * Boolean. Accepted values 0 and 1.
 */
#ifndef NRFX_TIMER1_ENABLED
#define NRFX_TIMER1_ENABLED 0
#endif

/**
 * @brief NRFX_TIMER2_ENABLED
 *
 * Boolean. Accepted values 0 and 1.
 */
#ifndef NRFX_TIMER2_ENABLED
#define NRFX_TIMER2_ENABLED 0
#endif

/**
 * @brief NRFX_TIMER3_ENABLED
 *
 * Boolean. Accepted values 0 and 1.
 */
#ifndef NRFX_TIMER3_ENABLED
#define NRFX_TIMER3_ENABLED 0
#endif

/**
 * @brief NRFX_TIMER4_ENABLED
 *
 * Boolean. Accepted values 0 and 1.
 */
#ifndef NRFX_TIMER4_ENABLED
#define NRFX_TIMER4_ENABLED 0
#endif

/**
 * @brief NRFX_TWI_ENABLED
 *
 * Boolean. Accepted values 0 and 1.
 */
#ifndef NRFX_TWI_ENABLED
#define NRFX_TWI_ENABLED 0
#endif

/**
 * @brief NRFX_TWI_DEFAULT_CONFIG_IRQ_PRIORITY
 *
 * Integer value. Minimum: 0 Maximum: 7
 */
#ifndef NRFX_TWI_DEFAULT_CONFIG_IRQ_PRIORITY
#define NRFX_TWI_DEFAULT_CONFIG_IRQ_PRIORITY NRFX_DEFAULT_IRQ_PRIORITY
#endif

/**
 * @brief NRFX_TWI_CONFIG_LOG_ENABLED
 *
 * Boolean. Accepted values 0 and 1.
 */
#ifndef NRFX_TWI_CONFIG_LOG_ENABLED
#define NRFX_TWI_CONFIG_LOG_ENABLED 0
#endif

/**
 * @brief NRFX_TWI_CONFIG_LOG_LEVEL
 *
 * Integer value.
 * Supported values:
 * - Off     = 0
 * - Error   = 1
 * - Warning = 2
 * - Info    = 3
 * - Debug   = 4
 */
#ifndef NRFX_TWI_CONFIG_LOG_LEVEL
#define NRFX_TWI_CONFIG_LOG_LEVEL 3
#endif

/**
 * @brief NRFX_TWI0_ENABLED
 *
 * Boolean. Accepted values 0 and 1.
 */
#ifndef NRFX_TWI0_ENABLED
#define NRFX_TWI0_ENABLED 0
#endif

/**
 * @brief NRFX_TWI1_ENABLED
 *
 * Boolean. Accepted values 0 and 1.
 */
#ifndef NRFX_TWI1_ENABLED
#define NRFX_TWI1_ENABLED 0
#endif

/**
 * @brief NRFX_TWIM_ENABLED
 *
 * Boolean. Accepted values 0 and 1.
 */
#ifndef NRFX_TWIM_ENABLED
#define NRFX_TWIM_ENABLED 0
#endif

/**
 * @brief NRFX_TWIM_DEFAULT_CONFIG_IRQ_PRIORITY
 *
 * Integer value. Minimum: 0 Maximum: 7
 */
#ifndef NRFX_TWIM_DEFAULT_CONFIG_IRQ_PRIORITY
#define NRFX_TWIM_DEFAULT_CONFIG_IRQ_PRIORITY NRFX_DEFAULT_IRQ_PRIORITY
#endif

/**
 * @brief NRFX_TWIM_CONFIG_LOG_ENABLED
 *
 * Boolean. Accepted values 0 and 1.
 */
#ifndef NRFX_TWIM_CONFIG_LOG_ENABLED
#define NRFX_TWIM_CONFIG_LOG_ENABLED 0
#endif

/**
 * @brief NRFX_TWIM_NRF52_ANOMALY_109_WORKAROUND_ENABLED - Enables nRF52 Anomaly 109 workaround for TWIM.
 *
 * Boolean. Accepted values 0 and 1.
 */
#ifndef NRFX_TWIM_NRF52_ANOMALY_109_WORKAROUND_ENABLED
#define NRFX_TWIM_NRF52_ANOMALY_109_WORKAROUND_ENABLED 0
#endif

/**
 * @brief NRFX_TWIM_CONFIG_LOG_LEVEL
 *
 * Integer value.
 * Supported values:
 * - Off     = 0
 * - Error   = 1
 * - Warning = 2
 * - Info    = 3
 * - Debug   = 4
 */
#ifndef NRFX_TWIM_CONFIG_LOG_LEVEL
#define NRFX_TWIM_CONFIG_LOG_LEVEL 3
#endif

/**
 * @brief NRFX_TWIM0_ENABLED
 *
 * Boolean. Accepted values 0 and 1.
 */
#ifndef NRFX_TWIM0_ENABLED
#define NRFX_TWIM0_ENABLED 0
#endif

/**
 * @brief NRFX_TWIM1_ENABLED
 *
 * Boolean. Accepted values 0 and 1.
 */
#ifndef NRFX_TWIM1_ENABLED
#define NRFX_TWIM1_ENABLED 0
#endif

/**
 * @brief NRFX_TWIS_ENABLED
 *
 * Boolean. Accepted values 0 and 1.
 */
#ifndef NRFX_TWIS_ENABLED
#define NRFX_TWIS_ENABLED 0
#endif

/**
 * @brief NRFX_TWIS_DEFAULT_CONFIG_IRQ_PRIORITY
 *
 * Integer value. Minimum: 0 Maximum: 7
 */
#ifndef NRFX_TWIS_DEFAULT_CONFIG_IRQ_PRIORITY
#define NRFX_TWIS_DEFAULT_CONFIG_IRQ_PRIORITY NRFX_DEFAULT_IRQ_PRIORITY
#endif

/**
 * @brief NRFX_TWIS_CONFIG_LOG_ENABLED
 *
 * Boolean. Accepted values 0 and 1.
 */
#ifndef NRFX_TWIS_CONFIG_LOG_ENABLED
#define NRFX_TWIS_CONFIG_LOG_ENABLED 0
#endif

/**
 * @brief NRFX_TWIS_ASSUME_INIT_AFTER_RESET_ONLY - Assume that any instance would be initialized only once.
 *
 * Boolean. Accepted values 0 and 1.
 */
#ifndef NRFX_TWIS_ASSUME_INIT_AFTER_RESET_ONLY
#define NRFX_TWIS_ASSUME_INIT_AFTER_RESET_ONLY 0
#endif

/**
 * @brief NRFX_TWIS_NO_SYNC_MODE - Remove support for synchronous mode.
 *
 * Boolean. Accepted values 0 and 1.
 */
#ifndef NRFX_TWIS_NO_SYNC_MODE
#define NRFX_TWIS_NO_SYNC_MODE 0
#endif

/**
 * @brief NRFX_TWIS_CONFIG_LOG_LEVEL
 *
 * Integer value.
 * Supported values:
 * - Off     = 0
 * - Error   = 1
 * - Warning = 2
 * - Info    = 3
 * - Debug   = 4
 */
#ifndef NRFX_TWIS_CONFIG_LOG_LEVEL
#define NRFX_TWIS_CONFIG_LOG_LEVEL 3
#endif

/**
 * @brief NRFX_TWIS0_ENABLED
 *
 * Boolean. Accepted values 0 and 1.
 */
#ifndef NRFX_TWIS0_ENABLED
#define NRFX_TWIS0_ENABLED 0
#endif

/**
 * @brief NRFX_TWIS1_ENABLED
 *
 * Boolean. Accepted values 0 and 1.
 */
#ifndef NRFX_TWIS1_ENABLED
#define NRFX_TWIS1_ENABLED 0
#endif

/**
 * @brief NRFX_UART_ENABLED
 *
 * Boolean. Accepted values 0 and 1.
 */
#ifndef NRFX_UART_ENABLED
#define NRFX_UART_ENABLED 0
#endif

/**
 * @brief NRFX_UART_DEFAULT_CONFIG_IRQ_PRIORITY
 *
 * Integer value. Minimum: 0 Maximum: 7
 */
#ifndef NRFX_UART_DEFAULT_CONFIG_IRQ_PRIORITY
#define NRFX_UART_DEFAULT_CONFIG_IRQ_PRIORITY NRFX_DEFAULT_IRQ_PRIORITY
#endif

/**
 * @brief NRFX_UART_CONFIG_LOG_ENABLED
 *
 * Boolean. Accepted values 0 and 1.
 */
#ifndef NRFX_UART_CONFIG_LOG_ENABLED
#define NRFX_UART_CONFIG_LOG_ENABLED 0
#endif

/**
 * @brief NRFX_UART_CONFIG_LOG_LEVEL
 *
 * Integer value.
 * Supported values:
 * - Off     = 0
 * - Error   = 1
 * - Warning = 2
 * - Info    = 3
 * - Debug   = 4
 */
#ifndef NRFX_UART_CONFIG_LOG_LEVEL
#define NRFX_UART_CONFIG_LOG_LEVEL 3
#endif

/**
 * @brief NRFX_UART0_ENABLED
 *
 * Boolean. Accepted values 0 and 1.
 */
#ifndef NRFX_UART0_ENABLED
#define NRFX_UART0_ENABLED 0
#endif

/**
 * @brief NRFX_UARTE_ENABLED
 *
 * Boolean. Accepted values 0 and 1.
 */
#ifndef NRFX_UARTE_ENABLED
#define NRFX_UARTE_ENABLED 0
#endif

/**
 * @brief NRFX_UARTE_DEFAULT_CONFIG_IRQ_PRIORITY
 *
 * Integer value. Minimum: 0 Maximum: 7
 */
#ifndef NRFX_UARTE_DEFAULT_CONFIG_IRQ_PRIORITY
#define NRFX_UARTE_DEFAULT_CONFIG_IRQ_PRIORITY NRFX_DEFAULT_IRQ_PRIORITY
#endif

/**
 * @brief NRFX_UARTE_CONFIG_LOG_ENABLED
 *
 * Boolean. Accepted values 0 and 1.
 */
#ifndef NRFX_UARTE_CONFIG_LOG_ENABLED
#define NRFX_UARTE_CONFIG_LOG_ENABLED 0
#endif

/**
 * @brief NRFX_UARTE_CONFIG_LOG_LEVEL
 *
 * Integer value.
 * Supported values:
 * - Off     = 0
 * - Error   = 1
 * - Warning = 2
 * - Info    = 3
 * - Debug   = 4
 */
#ifndef NRFX_UARTE_CONFIG_LOG_LEVEL
#define NRFX_UARTE_CONFIG_LOG_LEVEL 3
#endif

/**
 * @brief NRFX_UARTE0_ENABLED
 *
 * Boolean. Accepted values 0 and 1.
 */
#ifndef NRFX_UARTE0_ENABLED
#define NRFX_UARTE0_ENABLED 0
#endif

/**
 * @brief NRFX_WDT_ENABLED
 *
 * Boolean. Accepted values 0 and 1.
 */
#ifndef NRFX_WDT_ENABLED
#define NRFX_WDT_ENABLED 0
#endif

/**
 * @brief NRFX_WDT_DEFAULT_CONFIG_IRQ_PRIORITY
 *
 * Integer value. Minimum: 0 Maximum: 7
 */
#ifndef NRFX_WDT_DEFAULT_CONFIG_IRQ_PRIORITY
#define NRFX_WDT_DEFAULT_CONFIG_IRQ_PRIORITY NRFX_DEFAULT_IRQ_PRIORITY
#endif

/**
 * @brief NRFX_WDT_CONFIG_NO_IRQ - Remove WDT IRQ handling from WDT driver
 *
 * Boolean. Accepted values 0 and 1.
 */
#ifndef NRFX_WDT_CONFIG_NO_IRQ
#define NRFX_WDT_CONFIG_NO_IRQ 0
#endif

/**
 * @brief NRFX_WDT_CONFIG_LOG_ENABLED
 *
 * Boolean. Accepted values 0 and 1.
 */
#ifndef NRFX_WDT_CONFIG_LOG_ENABLED
#define NRFX_WDT_CONFIG_LOG_ENABLED 0
#endif

/**
 * @brief NRFX_WDT_CONFIG_LOG_LEVEL
 *
 * Integer value.
 * Supported values:
 * - Off     = 0
 * - Error   = 1
 * - Warning = 2
 * - Info    = 3
 * - Debug   = 4
 */
#ifndef NRFX_WDT_CONFIG_LOG_LEVEL
#define NRFX_WDT_CONFIG_LOG_LEVEL 3
#endif

#endif // NRFX_CONFIG_NRF52832_H__
