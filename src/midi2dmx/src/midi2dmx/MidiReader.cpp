/**
 * @file MidiReader.cpp
 * @author Christian Neukam
 * @brief Implementation of the midi2dmx::midi::MidiReader class
 * @version 1.0
 * @date 2023-12-31
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
#include "MidiReader.h"

namespace midi2dmx::midi {
MidiReader::MidiReader(const uint8_t channel, ISerialReader& serial)
    : mMidiCcSyncFilter(0xb0 | (0x0f & channel)), mSerial(serial) {}

bool MidiReader::syncCc() {
  bool returnValue;

  while (true) {
    if (!mSerial.available()) {
      returnValue = false;
      break;
    }
    uint8_t value = mSerial.read();

    if (value == mMidiCcSyncFilter) {
      returnValue = true;
      mSerial.delay(2);
      break;
    }
  }

  return returnValue;
}

bool MidiReader::readByte(uint8_t& data) {
  bool returnValue = false;
  const uint8_t byte = mSerial.read();

  if (!(byte & 0x80)) {
    data = byte;
    returnValue = true;
  }

  return returnValue;
}

bool MidiReader::readCc(uint8_t& controller, uint8_t& value) {
  uint8_t nMidiBytes = 0;
  bool returnValue = false;

  if (syncCc() && mSerial.available() >= 2) {
    returnValue = readByte(controller) & readByte(value);
  }

  return returnValue;
}
}  // namespace midi2dmx::midi
