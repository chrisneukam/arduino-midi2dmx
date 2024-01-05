/**
 * @file DmxTests.cpp
 * @author Christian Neukam
 * @brief Unit Tests for the midi2dmx::dmx::Dmx class
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
#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <functional>

#include "Dmx.h"

namespace midi2dmx::unittest {
using namespace midi2dmx::dmx;

static const uint16_t kGainMaxValue = 1024; /**< maximum allowed gain value */

/**
 * @brief This class provides the fixture for the Test Suite, which checks the DMX class without
 * parameters.
 *
 */
class DmxTestSuite : public ::testing::Test {
 public:
  /**
   * @brief Construct a new DmxTestSuite object.
   *
   */
  DmxTestSuite()
      : mDut(std::bind(&DmxTestSuite::onChangeCallback, this, std::placeholders::_1,
                       std::placeholders::_2)) {}

  /**
   * @brief Mock method for midi2dmx::dmx::DmxOnChangeCallback.
   *
   */
  MOCK_METHOD(void, onChangeCallback, (const uint8_t channel, const uint8_t value), ());

 protected:
  Dmx mDut; /**< the device under test */
};

/**
 * @brief This class provides the fixture for the Test Suite, which checks the DMX class with
 * variable gain value parameters.
 *
 */
class DmxGainTestSuite : public ::testing::TestWithParam<uint16_t> {
 public:
  /**
   * @brief Construct a new DmxGainTestSuite object.
   *
   */
  DmxGainTestSuite()
      : mDut(std::bind(&DmxGainTestSuite::onChangeCallback, this, std::placeholders::_1,
                       std::placeholders::_2)) {}

  /**
   * @brief Construct a new mock method object.
   *
   */
  MOCK_METHOD(void, onChangeCallback, (const uint8_t channel, const uint8_t value), ());

 protected:
  Dmx mDut; /**< the device under test */
};

class DmxGainOutsideDeadZoneTestSuite : public DmxGainTestSuite {};
class DmxGainInsideDeadZoneTestSuite : public DmxGainTestSuite {};

/**
 * @brief This test suite checks the attenuation of DMX control signals.
 *
 * @note A gain value of 1024 means unity gain, values lower than this mean a reduction.
 * Values greater than 1024 are not permitted and are clipped to 1024.
 *
 * The test design is based on boundary-value analysis with the following equivalence
 * groups:
 *
 * | value range  | description |
 * | ------------ | ----------- |
 * | (-inf, 0)    | not required -> input range is unsigned |
 * | [0, 1]       | lower boundary, valid input |
 * | [1023, 1024] | upper boundary, valid input |
 * | [1025, inf)  | invalid value range, triggers clipping |
 *
 * @see DmxGainTestSuite
 */
INSTANTIATE_TEST_SUITE_P(DMX, DmxGainTestSuite,
                         testing::Values(0, 1, kGainMaxValue - 1, kGainMaxValue, kGainMaxValue + 1),
                         [](const testing::TestParamInfo<DmxGainTestSuite::ParamType>& info) {
                           return std::to_string(info.param);
                         });

/**
 * @brief This test suite checks the attenuation of DMX control signals in case the gain is outside
 * the dead zone.
 *
 * @note The dead zone of the gain values is defined in the range of [-1, 1] around the current gain
 * value.
 *
 * The test design is based on boundary-value analysis with the following equivalence
 * groups:
 *
 * | gain range   | description |
 * | ------------ | ----------- |
 * | [0, 1]       | lower boundary, will trigger a DMX gain update |
 * | [1023, 1024] | upper boundary, will trigger a DMX gain update |
 *
 * @see DmxGainOutsideDeadZoneTestSuite
 */
INSTANTIATE_TEST_SUITE_P(
    DMX, DmxGainOutsideDeadZoneTestSuite,
    testing::Values(0, 1, 509, 510, 511, 512, 513, 514, 515, 1023, 1024),
    [](const testing::TestParamInfo<DmxGainOutsideDeadZoneTestSuite::ParamType>& info) {
      return std::to_string(info.param);
    });

/**
 * @brief This test suite checks the attenuation of DMX control signals in case the gain is outside
 * the dead zone.
 *
 * @note The dead zone of the gain values is defined in the range of [-1, 1] around the current gain
 * value.
 *
 * @note The values 510 and 514 are not explicitly checked as they result in the same values as the
 * boundary gain values due to rounding effects.
 *
 * The test design is based on boundary-value analysis with the following equivalence
 * groups:
 *
 * | gain range   | description |
 * | ------------ | ----------- |
 * | [0, 510]     | outside dead zone, will trigger a callback |
 * | [511, 513]   | gain inside the dead zone assuming a pre gain of 512 |
 * | [514, 1024]  | outside dead zone, will trigger a callback |
 *
 * @see DmxGainInsideDeadZoneTestSuite
 */
INSTANTIATE_TEST_SUITE_P(
    DMX, DmxGainInsideDeadZoneTestSuite, testing::Values(500, 511, 512, 513, 600),
    [](const testing::TestParamInfo<DmxGainInsideDeadZoneTestSuite::ParamType>& info) {
      return std::to_string(info.param);
    });

/**
 * @brief This test case checks whether the function midi2dmx::dmx::Dmx::update()
 * applies a gain value to the resulting DMX signal, where 1024 means unity gain.
 *
 */
TEST_P(DmxGainTestSuite, update_gain_forcedTrue_triggers_callback) {
  const auto gain = GetParam();
  const uint8_t dmxValue = 255u;
  const uint8_t dmxValueGain = (dmxValue * gain) / kGainMaxValue;

  if (gain >= kGainMaxValue) {
    // When the gain goes into saturation, the DMX input and output values are identical.
    EXPECT_CALL(*this, onChangeCallback(0, dmxValue)).Times(2);
  } else {
    EXPECT_CALL(*this, onChangeCallback(0, dmxValue));
    EXPECT_CALL(*this, onChangeCallback(0, dmxValueGain));
  }

  mDut.update({0, dmxValue});
  mDut.update(gain, true);
}

/**
 * @brief This test case checks whether the midi2dmx::dmx::Dmx::update() function applies a gain
 * value to the resulting DMX signal if the gain is outside the dead zone.
 *
 */
TEST_P(DmxGainOutsideDeadZoneTestSuite, update_gain_outside_deadZone_triggers_callback) {
  const auto gain = GetParam();
  const uint16_t gainInit = (gain + kGainMaxValue * 3 / 4) % kGainMaxValue;
  const uint8_t dmxValue = 254;
  const uint8_t dmxValueGainInit = (dmxValue * gainInit) / kGainMaxValue;
  const uint8_t dmxValueGain = (dmxValue * gain) / kGainMaxValue;

  if (gain < 1024) {
    // If unity gain is selected, this expectation is covered in the else path.
    EXPECT_CALL(*this, onChangeCallback(0, dmxValue));
    EXPECT_CALL(*this, onChangeCallback(0, dmxValueGain)).Times(1);
  } else {
    // If unity gain is selected, the values dmxValueGain and dmxValue are equal.
    EXPECT_CALL(*this, onChangeCallback(0, dmxValueGain)).Times(2);
  }
  EXPECT_CALL(*this, onChangeCallback(0, dmxValueGainInit));

  mDut.update({0, dmxValue});
  mDut.update(gainInit);
  mDut.update(gain);
}

/**
 * @brief This test case checks whether the midi2dmx::dmx::Dmx::update() function applies a gain
 * value to the resulting DMX signal if the gain is outside the dead zone.
 *
 */
TEST_P(DmxGainInsideDeadZoneTestSuite, update_gain_inside_deadZone_dont_triggers_callback) {
  const auto gain = GetParam();
  const uint16_t gainInit = 512;
  const uint8_t dmxValue = 254;
  const uint8_t dmxValueGainInit = (dmxValue * gainInit) / kGainMaxValue;
  const uint8_t dmxValueGain = (dmxValue * gain) / kGainMaxValue;

  EXPECT_CALL(*this, onChangeCallback(0, dmxValue));
  EXPECT_CALL(*this, onChangeCallback(0, dmxValueGainInit));

  if ((std::max(gain, gainInit) - std::min(gain, gainInit)) > 1) {
    // The third callback is only triggered if the last gain is outside the dead zone.
    // The dead zone is on the range [-1, 1] around the current gain.
    EXPECT_CALL(*this, onChangeCallback(0, dmxValueGain));
  }

  mDut.update({0, dmxValue});
  mDut.update(gainInit);
  mDut.update(gain);
}
}  // namespace midi2dmx::unittest
