/*!
 * @file
 * @brief Low power mode implementation for Kinetis MCUs.
 *
 * This library enables low power modes and configures wakeup.
 *
 * @author Matthias L. Jugel
 * @date   2017-04-01
 *
 * @copyright &copy; 2017 ubirch GmbH (https://ubirch.com)
 *
 * @section LICENSE
 * ```
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 * ```
 */
#include "kinetis_lowpower.h"

#include <fsl_llwu.h>
#include <fsl_port.h>
#include <fsl_smc.h>
#include <fsl_rtc.h>
#include <rtc_api.h>

#define LLWU_WAKEUP_PIN_IDX 7U /* LLWU_P7 */
#define LLWU_WAKEUP_PIN_TYPE kLLWU_ExternalPinFallingEdge

#define BOARD_WAKEUP_PORT PORTC
#define BOARD_WAKEUP_GPIO_PIN 3U

//!< LLWU Wakeup Handler
void __klp_LLWU_IRQHandler(void) {
    // external pin wakeup
    if (LLWU_GetExternalWakeupPinFlag(LLWU, LLWU_WAKEUP_PIN_IDX)) {
        PORT_SetPinInterruptConfig(BOARD_WAKEUP_PORT, BOARD_WAKEUP_GPIO_PIN, kPORT_InterruptOrDMADisabled);
        PORT_ClearPinsInterruptFlags(BOARD_WAKEUP_PORT, (1U << BOARD_WAKEUP_GPIO_PIN));
        LLWU_ClearExternalWakeupPinFlag(LLWU, LLWU_WAKEUP_PIN_IDX);
    }

    // RTC wakeup
    if (RTC_GetStatusFlags(RTC) & kRTC_AlarmFlag) {
        RTC_ClearStatusFlags(RTC, kRTC_AlarmInterruptEnable);
    }
}

void __klp_RTC_IRQHandler(void)
{
    if (RTC_GetStatusFlags(RTC) & kRTC_AlarmFlag) {
        RTC_ClearStatusFlags(RTC, kRTC_AlarmInterruptEnable);
    }
}


void powerDown() {
    // configure power down to lowest possible mode
    smc_power_mode_vlls_config_t vlls_config;
    vlls_config.enablePorDetectInVlls0 = true;
    vlls_config.enableRam2InVlls2 = false;
    vlls_config.enableLpoClock = false;

    // power down
    vlls_config.subMode = kSMC_StopSub0;
    SMC_PreEnterStopModes();
    SMC_SetPowerModeVlls(SMC, &vlls_config);
    SMC_PostExitStopModes();
}

void powerDownWakeupOnPin() {
    // setup the wakeup handler
    NVIC_SetVector(LLWU_IRQn, (uint32_t) &__klp_LLWU_IRQHandler);
    NVIC_EnableIRQ(LLWU_IRQn);
    LLWU_SetExternalWakeupPinMode(LLWU, LLWU_WAKEUP_PIN_IDX, LLWU_WAKEUP_PIN_TYPE);
    powerDown();

}

void powerDownWakeupOnRtc(int seconds) {
    // enable the rtc, at least make sure it works
    rtc_init();
    
    NVIC_SetVector(RTC_IRQn, (uint32_t) &__klp_RTC_IRQHandler);
    NVIC_EnableIRQ(RTC_IRQn);
    RTC_EnableInterrupts(RTC, kRTC_AlarmInterruptEnable);

    // setup the wakeup handler
    NVIC_SetVector(LLWU_IRQn, (uint32_t) &__klp_LLWU_IRQHandler);
    NVIC_EnableIRQ(LLWU_IRQn);
    LLWU_EnableInternalModuleInterruptWakup(LLWU, 5U, true);

    RTC->TAR = RTC->TSR + seconds;
    powerDown();
}


