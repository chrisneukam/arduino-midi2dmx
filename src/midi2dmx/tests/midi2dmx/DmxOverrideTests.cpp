/**
 * @file DmxOverrideTests.cpp
 * @author Christian Neukam
 * @brief Unit Tests for the midi2dmx::dmx::DmxOverride class
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
#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <vector>

#include "Dmx.h"
#include "DmxOverride.h"
#include "SleepMock.h"

namespace midi2dmx::unittest {
using namespace midi2dmx::dmx;

using testing::_;
using testing::NiceMock;

/**
 * @brief Derived class from midi2dmx::dmxDmxOverride.
 *
 * The derivation enables access to the protected member function
 * midi2dmx::dmxDmxOverride::sendStaticScene() in the Test Cases.
 *
 */
class DmxOverrideDut : public DmxOverride {
 public:
  /**
   * @brief Construct a new DmxOverrideDut object
   *
   */
  DmxOverrideDut() : DmxOverride(mSleepMock){};

  /**
   * @brief Forward the call to the protected parent class.
   *
   * @param[in] dmx the DMX handler object to send the scene to
   */
  void forwardSendStaticScene(Dmx& dmx) { sendStaticScene(dmx); }

 protected:
  NiceMock<SleepMock> mSleepMock; /**< the sleep mock object */
};

/**
 * @brief This class provides the fixture for the Test Suite, which checks
 * the midi2dmx::dmx::DmxOverride.
 *
 */
class DmxOverrideTestSuite : public testing::Test {
 public:
  /**
   * @brief Construct a new DmxOverrideTestSuite object.
   *
   */
  DmxOverrideTestSuite()
      : mDmx(std::bind(&DmxOverrideTestSuite::onChangeCallback, this, std::placeholders::_1,
                       std::placeholders::_2)) {}

  /**
   * @brief Mock method for midi2dmx::dmx::DmxOnChangeCallback.
   *
   */
  MOCK_METHOD(void, onChangeCallback, (const uint8_t channel, const uint8_t value), ());

 protected:
  Dmx mDmx; /**< the DMX handler object */
};

/**
 * @brief This class provides the fixture for the Test Suite, which checks the DMX class with
 * variable gain value parameters.
 *
 */
class DmxOverrideValueTestSuite : public ::testing::TestWithParam<uint8_t> {
 public:
  /**
   * @brief Construct a new DmxOverrideValueTestSuite object.
   *
   */
  DmxOverrideValueTestSuite()
      : mDmx(std::bind(&DmxOverrideValueTestSuite::onChangeCallback, this, std::placeholders::_1,
                       std::placeholders::_2)) {}

  /**
   * @brief Mock method for midi2dmx::dmx::DmxOnChangeCallback.
   *
   */
  MOCK_METHOD(void, onChangeCallback, (const uint8_t channel, const uint8_t value), ());

 protected:
  Dmx mDmx; /**< the DMX handler object */
};

/**
 * @brief This test suite checks the channel assignment and the RGB value assignment of the DMX
 * override mode.
 *
 * The test design is based on boundary-value analysis with the following equivalence
 * groups:
 *
 * | value range  | description |
 * | ------------ | ----------- |
 * | (-inf, 0)    | not required -> input range is unsigned |
 * | [0, 1, 2]    | lower boundary, valid input |
 * | [254, 255]   | upper boundary, valid input |
 *
 * @see DmxOverrideValueTestSuite
 */
INSTANTIATE_TEST_SUITE_P(
    DmxOverride, DmxOverrideValueTestSuite, testing::Values(0, 1, 2, 254, 255),
    [](const testing::TestParamInfo<DmxOverrideValueTestSuite::ParamType>& info) {
      return std::to_string(info.param);
    });

/**
 * @brief This test case tests whether a non-initialized DMX override mode does not trigger the DMX
 * on change callback.
 *
 */
TEST_F(DmxOverrideTestSuite, sendStaticScene_noInit_doesNotTriggerCallback) {
  DmxOverrideDut dut;

  EXPECT_CALL(*this, onChangeCallback(_, _)).Times(0);
  dut.forwardSendStaticScene(mDmx);
}

/**
 * @brief This test case tests whether an initialized DMX override mode triggers the DMX on change
 * callback.
 *
 */
TEST_F(DmxOverrideTestSuite, sendStaticScene_triggerCallback) {
  const std::vector<uint8_t> dmxChannels{1, 2, 3};
  const DmxRgb rgb = {2, 4, 6};
  const DmxRgbChannels channels(1, &dmxChannels[0], &dmxChannels[1], &dmxChannels[2]);
  DmxOverrideDut dut;

  dut.setRgbOverride(channels, rgb);

  EXPECT_CALL(*this, onChangeCallback(dmxChannels[0], rgb.red));
  EXPECT_CALL(*this, onChangeCallback(dmxChannels[1], rgb.green));
  EXPECT_CALL(*this, onChangeCallback(dmxChannels[2], rgb.blue));
  dut.forwardSendStaticScene(mDmx);
}

/**
 * @brief This test case tests whether an initialized DMX override mode triggers the DMX on change
 * callback across the valid input range of the channel input.
 *
 */
TEST_P(DmxOverrideValueTestSuite, sendStaticScene_channels_triggerCallback) {
  const uint8_t value = GetParam();
  const std::vector<uint8_t> dmxChannels{value, value, value};
  const DmxRgb rgb = {2, 4, 6};
  const DmxRgbChannels channels(1, &dmxChannels[0], &dmxChannels[1], &dmxChannels[2]);
  DmxOverrideDut dut;

  dut.setRgbOverride(channels, rgb);

  EXPECT_CALL(*this, onChangeCallback(dmxChannels[0], rgb.red));
  EXPECT_CALL(*this, onChangeCallback(dmxChannels[1], rgb.green));
  EXPECT_CALL(*this, onChangeCallback(dmxChannels[2], rgb.blue));
  dut.forwardSendStaticScene(mDmx);
}

/**
 * @brief This test case tests whether an initialized DMX override mode triggers the DMX on change
 * callback across the valid input range of the RGB input takin into account the bit depth
 * conversion.
 *
 */
TEST_P(DmxOverrideValueTestSuite, sendStaticScene_rgb_triggerCallback) {
  const uint8_t value = GetParam();
  const std::vector<uint8_t> dmxChannels{1, 2, 3};
  const DmxRgb rgb = {value, value, value};
  const DmxRgbChannels channels(1, &dmxChannels[0], &dmxChannels[1], &dmxChannels[2]);
  DmxOverrideDut dut;

  dut.setRgbOverride(channels, rgb);

  EXPECT_CALL(*this, onChangeCallback(dmxChannels[0], rgb.red));
  EXPECT_CALL(*this, onChangeCallback(dmxChannels[1], rgb.green));
  EXPECT_CALL(*this, onChangeCallback(dmxChannels[2], rgb.blue));
  dut.forwardSendStaticScene(mDmx);
}
}  // namespace midi2dmx::unittest
