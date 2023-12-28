/**
 * @file ContinuousControllerTests.cpp
 * @author Christian Neukam
 * @brief Unit Tests for the midi2dmx::midi::ContinuousController
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
#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "midi2dmx.h"

namespace midi2dmx::unittest {
using namespace midi2dmx;

static const uint8_t kMidiMaxValue = 0x7f; /**< maximum allowed MIDI CC value (127) */
static const uint8_t kDmxMaxValue = 0xfe;  /**< maximum possible DMX value (254) */

/**
 * @brief This class provides the fixture for the Test Suite, which checks the MIDI Continuous
 * Controller (CC).
 *
 */
class MidiCcTestSuite : public testing::Test {};

/**
 * @brief This class provides the fixture for the Test Suite, which checks the MIDI Continuous
 * Controller (CC) conversion to DMX values.
 *
 */
class MidiCcInputRangeTestSuite : public testing::TestWithParam<std::tuple<uint8_t, uint8_t>> {};

/**
 * @brief This matcher checks two midi2dmx::DmxValue objects for equality.
 *
 */
MATCHER_P(EQ, other, "") {
  return (arg.channel() == other.channel()) && (arg.value() == other.value());
}

/**
 * @brief This test suite checks the conversion of MIDI signals into DMX control signals.
 *
 * The test design is based on boundary-value analysis with the following equivalence groups:
 *
 * | MIDI \p channel range | description |
 * | --------------------- | ----------- |
 * | (-inf, 0)  | not required -> input range is unsigned |
 * | [0, 1]     | lower boundary, valid input |
 * | [126, 127] | upper boundary, valid input |
 * | [128, inf) | invalid value range, triggers clipping |
 *
 * | MIDI \p value range | description |
 * | ------------------- | ----------- |
 * | (-inf, 0)  | not required -> input range is unsigned |
 * | [0, 1]     | lower boundary, valid input |
 * | [254, 255] | upper boundary, valid input |
 * | [256, inf) | not required -> input range is 8 bit only |
 *
 * @see MidiCcInputRangeTestSuite
 */
INSTANTIATE_TEST_SUITE_P(
    ContinuousController, MidiCcInputRangeTestSuite,
    testing::Combine(testing::Values(0, 1, 254, 255),
                     testing::Values(0, 1, kMidiMaxValue - 1, kMidiMaxValue, kMidiMaxValue + 1)),
    [](const testing::TestParamInfo<MidiCcInputRangeTestSuite::ParamType>& info) {
      std::string name =
          std::to_string(std::get<0>(info.param)) + "_" + std::to_string(std::get<1>(info.param));
      return name;
    });

/**
 * @brief This test case checks whether the default constructor of the
 * midi2dmx::midi::ContinuousController initializes a new object equal to
 * midi2dmx::midi::ContinuousController(0, 0).
 *
 */
TEST_F(MidiCcTestSuite, construct_default) {
  midi::ContinuousController cc;

  EXPECT_EQ(cc, midi::ContinuousController(0, 0));
}

/**
 * @brief This test case checks whether the compare operators of a
 * midi2dmx::midi::ContinuousController return the anticipated result.
 *
 */
TEST_F(MidiCcTestSuite, compare_operators) {
  midi::ContinuousController cc{21, 42};

  EXPECT_TRUE(cc == midi::ContinuousController(cc));
  EXPECT_FALSE(cc != midi::ContinuousController(cc));
  EXPECT_FALSE(cc == midi::ContinuousController());
  EXPECT_TRUE(cc != midi::ContinuousController());
}

/**
 * @brief This test case checks whether the function midi2dmx::midi::ContinuousController::toDmx()
 * converts a MIDI Continuos Controller (CC) signal into a DMX signal, where the MIDI CC command
 * corresponds to the DMX channel and the MIDI CC value corresponds to the DMX value.
 *
 */
TEST_P(MidiCcInputRangeTestSuite, toDmx_scalesDmxValue) {
  const auto [midiChannel, midiValue] = GetParam();
  const uint8_t dmxValue = (midiValue > kMidiMaxValue) ? kDmxMaxValue : midiValue * 2;
  const uint8_t dmxChannel = midiChannel;
  midi::ContinuousController dut{midiChannel, midiValue};

  EXPECT_THAT(dut.toDmx(), EQ(dmx::DmxValue{dmxChannel, dmxValue}));
}
}  // namespace midi2dmx::unittest
