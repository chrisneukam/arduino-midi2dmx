/**
 * @file DmxOverride.h
 * @author Christian Neukam
 * @brief Implementation of the DMX override mode handling class.
 * @version 1.0
 * @date 2024-01-05
 *
 * @copyright Copyright 2024 Christian Neukam. All rights reserved.
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
#include "DmxOverride.h"

#include "Dmx.h"
#include "ISleep.h"
#include "util.h"

namespace midi2dmx::dmx {
using namespace midi2dmx::util;

DmxOverride::DmxOverride(ISleep& sleep) : mSleep(sleep) {}

void DmxOverride::setRgbOverride(const DmxRgbChannels& channels, const DmxRgb& rgb) {
  mChannels = channels;
  mRgb = rgb;
}

void DmxOverride::sendStaticScene(Dmx& dmx) {
  for (uint8_t ch = 0; ch < mChannels.size(); ch++) {
    dmx.update(DmxValue{mChannels.red(ch), mRgb.red}, true);
    dmx.update(DmxValue{mChannels.green(ch), mRgb.green}, true);
    dmx.update(DmxValue{mChannels.blue(ch), mRgb.blue}, true);
  }

  mSleep.sleep(1000);
}
}  // namespace midi2dmx::dmx
