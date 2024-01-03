/**
 * @file SerialReaderMock.h
 * @author Christian Neukam
 * @brief Unit Tests for the midi2dmx::dmx::DmxValue
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
#pragma once
#include <gmock/gmock.h>

#include <vector>

#include "ISerialReader.h"

namespace midi2dmx::unittest {
/**
 * @brief This class provides the mock implementation of the midi2dmx::ISerialReader interface.
 *
 */
class SerialReaderMock : public midi2dmx::ISerialReader {
 public:
  /**
   * @brief Construct a new SerialReaderMock object.
   *
   * @param[in] data the serial data buffer to simulate
   */
  SerialReaderMock(const std::vector<uint8_t>& data);

  /**
   * @brief Mock methods from midi2dmx::ISerialReader.
   *
   */
  ///@{
  MOCK_METHOD(int, available, (), (override));
  MOCK_METHOD(int, read, (), (override));
  MOCK_METHOD(void, delay, (uint8_t sleep_ms), (override));
  ///@}

 private:
  std::vector<uint8_t> mSerialData; /**< the serial data to simulate */
};
}  // namespace midi2dmx::unittest
