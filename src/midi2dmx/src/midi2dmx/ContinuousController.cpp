/**
 * @file ContinuousController.cpp
 * @author Christian Neukam
 * @brief Implementation of the midi2dmx::midi::ContinuousController class
 * @version 1.0
 * @date 2023-12-12
 *
 * @copyright Copyright 2023 Christian Neukam. All rights reserved.
 *
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
 */
#include "ContinuousController.h"

namespace midi2dmx::midi {
const unsigned int kMidiToDmxFactor = 2; /**< scaling factor converting midi to dmx */
const unsigned int kMaxDmxValue = 255;   /**< maximum possible DMX value */
const unsigned int kAnalogReadBits = 10; /**< bit resolution of analog read */
const unsigned int kUnityGainValue = (1 << kAnalogReadBits); /**< factor representing unity gain */

/**
 * @brief constexpr definition of the min operation.
 *
 * @param[in] x the first value
 * @param[in] y the second value
 * @return unsigned int; the minumum value of x and y
 */
constexpr unsigned int min(unsigned int x, unsigned int y) { return (x > y) ? y : x; }

ContinuousController::ContinuousController(const unsigned int controller, const unsigned int value)
    : mController(controller), mValue(value), mGain(kUnityGainValue) {}

Dmx ContinuousController::toDmx() const {
  unsigned dmxValue = mValue * kMidiToDmxFactor;

  if (dmxValue > kMaxDmxValue) {
    dmxValue = kMaxDmxValue;
  }

  return {mController, applyGain(dmxValue)};
}

void ContinuousController::setGain(const unsigned int gain) { mGain = min(gain, kUnityGainValue); }

unsigned ContinuousController::applyGain(const unsigned int value) const {
  return (value * mGain) >> kAnalogReadBits;
}

/*
 * MIDI Protocol:
 * Statusbyte - Datenbyte 1 - Datenbyte 2
 * [80, FF]   - [00, 7F]    - [00, 7F]
 *
 * Statusbyte:
 * 0000   0000
 * Befehl Kanal
 *
 * relevantes Statusbyte:
 * Bn -> Control Change
 *
 * DMX Protocol:
 * up to 512 data channels
 * 8 bit per channel
 */
}  // namespace midi2dmx::midi
