/**
 * @file MidiReaderTest.cpp
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

#include "MidiReader.h"
#include "SerialReaderMock.h"

namespace midi2dmx::unittest {
using midi2dmx::midi::MidiReader;
using testing::NiceMock;

/**
 * @brief This class provides the fixture for the Test Suite, which checks the
 * midi2dmx::midi::MidiReader.
 *
 */
class MidiReaderTestSuite : public testing::Test {
 protected:
  const uint8_t mChannel = 1;                         /**< the MIDI channel to test */
  const uint8_t mSyncByte = 0xB0 | (0x0f & mChannel); /**< the first MIDI CC byte */
};

/**
 * @brief This class provides the fixture for the Test Suite, which checks the
 * midi2dmx::midi::MidiReader with different MIDI channels.
 *
 */
class MidiReaderCcChannelTestSuite : public testing::TestWithParam<uint8_t> {};

/**
 * @brief This class provides the fixture for the Test Suite, which checks the
 * midi2dmx::midi::MidiReader with different MIDI CC data bytes.
 *
 */
class MidiReaderCcDataByteTestSuite : public testing::TestWithParam<uint8_t> {
 protected:
  const uint8_t mChannel = 1;                         /**< the MIDI channel to test */
  const uint8_t mSyncByte = 0xB0 | (0x0f & mChannel); /**< the first MIDI CC byte */
};

/**
 * @brief This test suite checks the MIDI channel response of MIDI CC signals.
 *
 * The test design is based on boundary-value analysis with the following equivalence
 * groups:
 *
 * | value range  | description |
 * | ------------ | ----------- |
 * | (-inf, 0)    | not required -> input range is unsigned |
 * | [0, 1]       | lower boundary, valid input |
 * | [14, 15]     | upper boundary, valid input |
 * | [16, inf)    | not required -> channel has only 4 bit resolution |
 *
 * @see MidiReaderCcChannelTestSuite
 */
INSTANTIATE_TEST_SUITE_P(
    MIDI, MidiReaderCcChannelTestSuite, testing::Values(0x00, 0x01, 0x0e, 0x0f),
    [](const testing::TestParamInfo<MidiReaderCcChannelTestSuite::ParamType>& info) {
      return std::to_string(info.param);
    });

/**
 * @brief This test suite checks the MIDI CC data byte response of MIDI CC signals.
 *
 * The test design is based on boundary-value analysis with the following equivalence
 * groups:
 *
 * | value range  | description |
 * | ------------ | ----------- |
 * | (-inf, 0)    | not required -> input range is unsigned |
 * | [0, 1]       | lower boundary, valid input |
 * | [126, 127]   | upper boundary, valid input |
 * | [128, 129]   | lower boundary, invalid input |
 * | [254, 255]   | upper boundary, invalid input |
 *
 * @see MidiReaderCcChannelTestSuite
 */
INSTANTIATE_TEST_SUITE_P(
    MIDI, MidiReaderCcDataByteTestSuite,
    testing::Values(0x00, 0x01, 0x7e, 0x7f, 0x80, 0x81, 0xfe, 0xff),
    [](const testing::TestParamInfo<MidiReaderCcDataByteTestSuite::ParamType>& info) {
      return std::to_string(info.param);
    });

/**
 * @brief This test case tests whether the function midi2dmx::midi::MidiReader::readCc() can read a
 * MIDI CC date on all valid MIDI channels.
 *
 */
TEST_P(MidiReaderCcChannelTestSuite, readCc_channelsInRange_shall_pass) {
  uint8_t controller;
  uint8_t value;
  const uint8_t channel = GetParam();
  const uint8_t syncByte = 0xB0 | (0x0f & channel);
  const std::vector<uint8_t> serialData = {syncByte, 0x01, 0x02};

  NiceMock<SerialReaderMock> serial(serialData);
  MidiReader dut{channel, serial};

  EXPECT_TRUE(dut.readCc(controller, value));
}

/**
 * @brief This test case tests whether the function midi2dmx::midi::MidiReader::readCc() can read a
 * MIDI CC date on the set MIDI channel and returns the corresponding status.
 *
 */
TEST_F(MidiReaderTestSuite, readCc_channel_filter_shall_pass) {
  uint8_t controller;
  uint8_t value;
  const std::vector<uint8_t> serialData = {mSyncByte, 0x01, 0x02};

  NiceMock<SerialReaderMock> serial(serialData);
  MidiReader dut{mChannel, serial};

  EXPECT_TRUE(dut.readCc(controller, value));
}

/**
 * @brief This test case tests whether the function midi2dmx::midi::MidiReader::readCc() ignores a
 * MIDI CC date received on a MIDI channel other than the one set and returns the corresponding
 * status.
 *
 */
TEST_F(MidiReaderTestSuite, readCc_channel_filter_shall_fail) {
  uint8_t controller;
  uint8_t value;
  const std::vector<uint8_t> serialData = {mSyncByte, 0x01, 0x02};

  NiceMock<SerialReaderMock> serial(serialData);
  MidiReader dut{mChannel + 1u, serial};

  EXPECT_FALSE(dut.readCc(controller, value));
}

/**
 * @brief This test case tests whether the function midi2dmx::midi::MidiReader::readCc() ignores a
 * MIDI CC datum with the correct sync byte but missing data bytes and returns the corresponding
 * status.
 *
 */
TEST_F(MidiReaderTestSuite, readCc_validSyncByte_noData_shall_fail) {
  uint8_t controller;
  uint8_t value;
  const std::vector<uint8_t> serialData = {mSyncByte};

  NiceMock<SerialReaderMock> serial(serialData);
  MidiReader dut{mChannel, serial};

  EXPECT_FALSE(dut.readCc(controller, value));
}

/**
 * @brief This test case tests whether the function midi2dmx::midi::MidiReader::readCc() ignores a
 * MIDI CC datum with correct sync byte but missing 2nd data byte and returns the corresponding
 * status.
 *
 */
TEST_F(MidiReaderTestSuite, readCc_validSyncByte_noValueByte_shall_fail) {
  uint8_t controller;
  uint8_t value;
  const std::vector<uint8_t> serialData = {mSyncByte, 0x01};

  NiceMock<SerialReaderMock> serial(serialData);
  MidiReader dut{mChannel, serial};

  EXPECT_FALSE(dut.readCc(controller, value));
}

/**
 * @brief This test case tests whether the function midi2dmx::midi::MidiReader::readCc() ignores a
 * MIDI CC datum with incorrect sync bytes and returns the corresponding status.
 *
 */
TEST_F(MidiReaderTestSuite, readCc_invalidSyncByte_validData_shall_fail) {
  uint8_t controller;
  uint8_t value;
  const std::vector<uint8_t> serialData = {0x71, 0x01, 0x02};

  NiceMock<SerialReaderMock> serial(serialData);
  MidiReader dut{mChannel, serial};

  EXPECT_FALSE(dut.readCc(controller, value));
}

/**
 * @brief This test case tests whether the function midi2dmx::midi::MidiReader::readCc() transfers a
 * MIDI CC datum with the correct sync byte received on the set channel to the \p controller
 * parameter.
 *
 */
TEST_P(MidiReaderCcDataByteTestSuite, readCc_controllerByte_shall_getUpdated_if_valid) {
  uint8_t controller;
  uint8_t value;
  const std::vector<uint8_t> serialData = {mSyncByte, GetParam(), 0x02};

  NiceMock<SerialReaderMock> serial(serialData);
  MidiReader dut{mChannel, serial};

  if (GetParam() & 0x80) {
    // MIDI CC data bytes must not have set the MSB to 1.
    ASSERT_FALSE(dut.readCc(controller, value));
  } else {
    ASSERT_TRUE(dut.readCc(controller, value));
    EXPECT_EQ(controller, serialData[1]);
  }
}

/**
 * @brief This test case tests whether the function midi2dmx::midi::MidiReader::readCc() transfers a
 * MIDI CC datum with the correct sync byte received on the set channel to the \p value parameter.
 *
 */
TEST_P(MidiReaderCcDataByteTestSuite, readCc_valueByte_shall_getUpdated_if_valid) {
  uint8_t controller;
  uint8_t value;
  const std::vector<uint8_t> serialData = {mSyncByte, 0x01, GetParam()};

  NiceMock<SerialReaderMock> serial(serialData);
  MidiReader dut{mChannel, serial};

  if (GetParam() & 0x80) {
    // MIDI CC data bytes must not have set the MSB to 1.
    ASSERT_FALSE(dut.readCc(controller, value));
  } else {
    ASSERT_TRUE(dut.readCc(controller, value));
    EXPECT_EQ(value, serialData[2]);
  }
}
}  // namespace midi2dmx::unittest
