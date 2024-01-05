/**
 * @file DmxRgbChannels.cpp
 * @author Christian Neukam
 * @brief Implementation of the DmxRgbChannels class.
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
#include "DmxRgbChannels.h"

#ifdef ARDUINO
#include <string.h>
#else
#include <string>
#endif

#include "util.h"

namespace midi2dmx::dmx {
#ifndef ARDUINO
using namespace std;
#endif
using namespace midi2dmx::util;

DmxRgbChannels::DmxRgbChannels() : mSize(0) {}

DmxRgbChannels::DmxRgbChannels(const uint8_t s, uint8_t const* const r, uint8_t const* const g,
                               uint8_t const* const b)
    : mSize((r && g && b) ? min(s, kMaxRgbSize) : 0) {
  memcpy(mRed, r, mSize * sizeof(uint8_t));
  memcpy(mGreen, g, mSize * sizeof(uint8_t));
  memcpy(mBlue, b, mSize * sizeof(uint8_t));
}

void DmxRgbChannels::operator=(const DmxRgbChannels& rhs) {
  mSize = rhs.mSize;
  memcpy(mRed, rhs.mRed, mSize * sizeof(uint8_t));
  memcpy(mGreen, rhs.mGreen, mSize * sizeof(uint8_t));
  memcpy(mBlue, rhs.mBlue, mSize * sizeof(uint8_t));
}

uint8_t DmxRgbChannels::size() const { return mSize; }

uint8_t DmxRgbChannels::red(const uint8_t ch) const { return (ch < mSize) ? mRed[ch] : 0; }

uint8_t DmxRgbChannels::green(const uint8_t ch) const { return (ch < mSize) ? mGreen[ch] : 0; }

uint8_t DmxRgbChannels::blue(const uint8_t ch) const { return (ch < mSize) ? mBlue[ch] : 0; }
}  // namespace midi2dmx::dmx
