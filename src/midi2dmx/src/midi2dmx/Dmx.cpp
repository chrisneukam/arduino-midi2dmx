/**
 * @file Dmx.cpp
 * @author Christian Neukam
 * @brief Definition of the midi2dmx::Dmx class
 * @version 1.0
 * @date 2023-12-25
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
#include "Dmx.h"

#include "util.h"

namespace midi2dmx::dmx {

Dmx::Dmx() : Dmx(nullptr) {}

Dmx::Dmx(DmxOnChangeCallback callback)
    : mDmxValue(0, 0), mGain(kUnityGainValue), mCallback(callback) {}

uint8_t Dmx::valueScaled() const {
  return (uint32_t)mDmxValue.value() * (uint32_t)mGain >> kAnalogReadBits;
}

void Dmx::update(const uint16_t gain, const bool force) {
  const bool isToSet = (max(gain, mGain) - gain) > kGainDeadZone ? true : false;

  if (isToSet || force) {
    mGain = min(gain, kUnityGainValue);

    if (mCallback) {
      mCallback(mDmxValue.channel(), valueScaled());
    }
  }
}

void Dmx::update(const DmxValue& dmxValue, const bool force) {
  const bool triggerCallback = mDmxValue != dmxValue;

  mDmxValue = dmxValue;

  if (mCallback && (triggerCallback || force)) {
    mCallback(mDmxValue.channel(), valueScaled());
  }
}
}  // namespace midi2dmx::dmx
