/**
 * @file midi2dmx.h
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

/**
 * @brief This namespace bundles all components that are required for the execution of unit tests of
 * the \p midi2dmx library.
 *
 */
namespace midi2dmx::unittest {
using namespace midi2dmx;

constexpr unsigned int kMidiMaxValue = 0x7f; /**< maximum allowed MIDI CC value */
constexpr unsigned int kDmxMaxValue = 255;   /**< maximum allowed DMX value */
constexpr unsigned int kGainMaxValue = 1024; /**< maximum allowed gain value */

/**
 * @brief This class provides the fixture for the Test Suite, which checks the MIDI Continuous
 * Controller (CC) conversion to DMX with unity gain.
 *
 */
class MidiCcInputRangeTestSuite : public testing::TestWithParam<unsigned int> {};

/**
 * @brief This class provides the fixture for the Test Suite, which checks the MIDI Continuous
 * Controller (CC) conversion to DMX with variable gain.
 *
 */
class GainInputRangeTestSuite
    : public testing::TestWithParam<std::tuple<unsigned int, unsigned int>> {};

/**
 * @brief This matcher checks two midi2dmx::Dmx objects for equality.
 *
 */
MATCHER_P(EQ, other, "") { return (arg.channel == other.channel) && (arg.value == other.value); }

/**
 * @brief This test suite checks the conversion of MIDI signals into DMX control signals.
 *
 * The test design is based on boundary-value analysis with the following equivalence groups:
 *
 * | value range | description |
 * | ----------- | ----------- |
 * | (-inf, 0)   | not required -> input range is unsigned |
 * | [0, 1]      | lower boundary, valid input |
 * | [126, 127]  | upper boundary, valid input |
 * | [128, inf)  | invalid value range, triggers clipping |
 *
 * @see MidiCcInputRangeTestSuite
 */
INSTANTIATE_TEST_SUITE_P(
    ContinuousController, MidiCcInputRangeTestSuite,
    testing::Values(0, 1, kMidiMaxValue - 1, kMidiMaxValue, kMidiMaxValue + 1),
    [](const testing::TestParamInfo<MidiCcInputRangeTestSuite::ParamType>& info) {
      return std::to_string(info.param);
    });

/**
 * @brief This test suite checks the attenuation of converted DMX control signals.
 *
 * @note A gain value of 1024 means unity gain, values lower than this mean a reduction. Values
 * greater than 1024 are not permitted and are clipped to 1024.
 *
 * The test design is based on boundary-value analysis with the following equivalence groups:
 *
 * | value range  | description |
 * | ------------ | ----------- |
 * | (-inf, 0)    | not required -> input range is unsigned |
 * | [0, 1]       | lower boundary, valid input |
 * | [1023, 1024] | upper boundary, valid input |
 * | [1025, inf)  | invalid value range, triggers clipping |
 *
 * @see GainInputRangeTestSuite
 */
INSTANTIATE_TEST_SUITE_P(
    ContinuousController, GainInputRangeTestSuite,
    testing::Combine(testing::Values(0, 1, kGainMaxValue - 1, kGainMaxValue, kGainMaxValue + 1),
                     testing::Values(0, 1, kMidiMaxValue - 1, kMidiMaxValue, kMidiMaxValue + 1)),
    [](const testing::TestParamInfo<GainInputRangeTestSuite::ParamType>& info) {
      std::string name =
          std::to_string(std::get<0>(info.param)) + "_" + std::to_string(std::get<1>(info.param));
      return name;
    });

/**
 * @brief This test case checks whether the function midi2dmx::midi::ContinuousController::toDmx()
 * converts a MIDI Continuos Controller (CC) signal into a DMX signal, where the MIDI CC command
 * corresponds to the DMX channel and the MIDI CC value corresponds to the DMX value.
 *
 */
TEST_P(MidiCcInputRangeTestSuite, toDmx_without_gain) {
  const auto midiValue = GetParam();
  const unsigned int dmxValue = std::min(midiValue * 2, kDmxMaxValue);
  midi::ContinuousController dut{0, midiValue};

  EXPECT_THAT(dut.toDmx(), EQ(Dmx{0, dmxValue}));
}

/**
 * @brief This test case checks whether the function midi2dmx::midi::ContinuousController::toDmx()
 * applies a gain value to the resulting DMX signal, where 1024 means unity gain.
 *
 */
TEST_P(GainInputRangeTestSuite, toDmx_with_gain) {
  const auto [gain, midiValue] = GetParam();
  const unsigned int dmxValue = (gain * std::min(midiValue * 2, kDmxMaxValue)) / 1024;
  midi::ContinuousController dut{0, midiValue};
  dut.setGain(gain);

  EXPECT_THAT(dut.toDmx(), EQ(Dmx{0, dmxValue}));
}
}  // namespace midi2dmx::unittest
