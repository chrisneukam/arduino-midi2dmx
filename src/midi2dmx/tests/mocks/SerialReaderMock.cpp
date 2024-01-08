/**
 * @file SerialReaderMock.h
 * @author Christian Neukam
 * @brief Mock implementation of the midi2dmx::ISerialReader interface
 * @version 1.0
 * @date 2024-01-04
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
#include "SerialReaderMock.h"

namespace midi2dmx::unittest {

SerialReaderMock::SerialReaderMock(const std::vector<uint8_t>& data) : mSerialData(data) {
  using testing::Return;

  ON_CALL(*this, available).WillByDefault([&]() {
    /// @see https://www.arduino.cc/reference/en/language/functions/communication/serial/available/
    return mSerialData.size();
  });

  ON_CALL(*this, read).WillByDefault([&]() {
    /// @see https://www.arduino.cc/reference/en/language/functions/communication/serial/read/
    int returnValue = -1;  // return -1 if no data is available

    if (mSerialData.size() > 0) {
      returnValue = mSerialData[0];            // get the first byte on the "stack"
      mSerialData.erase(mSerialData.begin());  // remove this byte from the "stack"
    }

    return returnValue;
  });
}

}  // namespace midi2dmx::unittest
