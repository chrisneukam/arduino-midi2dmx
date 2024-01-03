/**
 * @file Midi2DmxTests.cpp
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
#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "SerialReaderMock.h"
#include "midi2dmx.h"

namespace midi2dmx::unittest {
using testing::_;
using testing::NiceMock;

/**
 * @brief This class provides the fixture for the Test Suite, which checks the
 * midi2dmx::midi::MidiReader.
 *
 */
class Midi2DmxTestSuite : public testing::Test {
 public:
  /**
   * @brief Construct a new Midi2DmxTestSuite object.
   *
   */
  Midi2DmxTestSuite()
      : mChannel(1),
        mSyncByte(0xB0 | (0x0f & mChannel)),
        mSerialData({mSyncByte, 0x01, 0x02, mSyncByte, 0x03}),
        mSerial(mSerialData),
        mDut(mChannel,
             std::bind(&Midi2DmxTestSuite::onChangeCallback, this, std::placeholders::_1,
                       std::placeholders::_2),
             mSerial) {}

  /**
   * @brief Mock method for midi2dmx::dmx::DmxOnChangeCallback.
   *
   */
  MOCK_METHOD(void, onChangeCallback, (const uint8_t channel, const uint8_t value), ());

 protected:
  const uint8_t mChannel;                 /**< the MIDI channel to test */
  const uint8_t mSyncByte;                /**< the first MIDI CC byte */
  const std::vector<uint8_t> mSerialData; /**< the serial data to simulate */
  NiceMock<SerialReaderMock> mSerial;     /**< the serial interface mock */
  Midi2Dmx mDut;                          /**< the device under test */
};

/**
 * @brief This test case tests whether the function Midi2Dmx::serialUpdate() triggers a
 * midi2dmx::dmx::DmxOnChangeCallback callback if the serial data stream contains a valid MIDI CC
 * value.
 *
 */
TEST_F(Midi2DmxTestSuite, serialUpdate_shall_trigger_callback_with_valid_serialData) {
  EXPECT_CALL(*this, onChangeCallback(mSerialData[1], mSerialData[2] << 1));

  mDut.serialUpdate();
}

/**
 * @brief This test case tests whether the function Midi2Dmx::serialUpdate() does not trigger a
 * midi2dmx::dmx::DmxOnChangeCallback callback if the serial data stream does not contain a valid
 * MIDI CC value.
 *
 */
TEST_F(Midi2DmxTestSuite, serialUpdate_shall_not_trigger_callback_with_invalid_serialData) {
  EXPECT_CALL(*this, onChangeCallback(_, _)).Times(0);

  mSerial.read();  // Skip the first byte in mSerialData so that the data packet becomes invalid.
  mDut.serialUpdate();
}
}  // namespace midi2dmx::unittest
