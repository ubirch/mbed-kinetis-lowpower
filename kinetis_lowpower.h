/*!
 * @file
 * @brief TODO: ${FILE}
 *
 * ...
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
#ifndef KINETISLOWPOWER_H
#define KINETISLOWPOWER_H

#include <stdint.h>
#include <PinNames.h>
#include <pinmap.h>
#include <fsl_rcm.h>

extern uint32_t kinetisResetSource;

//!< Power down and wait for a pin interrupt
void powerDownWakeupOnPin();

//!< Power down and wake up on RTC interrupt in n seconds
void powerDownWakeupOnRtc(int seconds);

inline bool isPowerOnReset() {
    return (bool) (kinetisResetSource & kRCM_SourcePor);
}

inline bool isResetWatchdog() {
    return (bool) (kinetisResetSource & kRCM_SourceWdog);
}

inline bool isLowPowerWakeup() {
    return (bool) (kinetisResetSource & kRCM_SourceWakeup);
}

#endif //KINETISLOWPOWER_H
