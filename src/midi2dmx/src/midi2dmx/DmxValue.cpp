/**
 * @file DmxValue.cpp
 * @author Christian Neukam
 * @brief Implementation of the midi2dmx::dmx::DmxValue class
 * @version 1.0
 * @date 2023-12-28
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
#include "DmxValue.h"

namespace midi2dmx::dmx {
DmxValue::DmxValue(const uint8_t channel, const uint8_t value) : mChannel(channel), mValue(value) {}

DmxValue& DmxValue::operator=(const DmxValue& rhs) {
  if (this != &rhs) {
    mChannel = rhs.mChannel;
    mValue = rhs.mValue;
  }

  return *this;
}

bool DmxValue::operator==(const DmxValue& rhs) const {
  return mChannel == rhs.mChannel && mValue == rhs.mValue;
}

bool DmxValue::operator!=(const DmxValue& rhs) const { return !(*this == rhs); }

uint8_t DmxValue::channel() const { return mChannel; }

uint8_t DmxValue::value() const { return mValue; }
}  // namespace midi2dmx::dmx
