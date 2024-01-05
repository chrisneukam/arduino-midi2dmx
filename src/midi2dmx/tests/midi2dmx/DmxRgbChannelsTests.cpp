/**
 * @file MidiReaderTest.cpp
 * @author Christian Neukam
 * @brief Unit Tests for the midi2dmx::dmx::DmxRgbChannels class
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

#include "DmxRgbChannels.h"

namespace midi2dmx::unittest {
using midi2dmx::dmx::DmxRgbChannels;

/**
 * @brief This class provides the fixture for the Test Suite, which checks the
 * midi2dmx::dmx::DmxRgbChannels.
 *
 */
class DmxRgbChannelsTestSuite : public testing::Test {};

/**
 * @brief This test case tests whether the default constructor creates an empty
 * midi2dmx::dmx::DmxRgbChannels object with a size of 0.
 *
 */
TEST_F(DmxRgbChannelsTestSuite, construct_default_returns_size_0) {
  const uint8_t value = 1;
  DmxRgbChannels dut;

  EXPECT_EQ(dut.size(), 0);
  EXPECT_EQ(dut.red(0), 0);
  EXPECT_EQ(dut.green(0), 0);
  EXPECT_EQ(dut.blue(0), 0);
}

/**
 * @brief This test case tests whether the constructor creates an empty
 * midi2dmx::dmx::DmxRgbChannels object where the size is 0 if a pointer parameter is nullptr.
 *
 */
TEST_F(DmxRgbChannelsTestSuite, construct_nullptr_returns_size_0) {
  const uint8_t value = 1;
  std::vector<DmxRgbChannels> dut;

  dut.push_back({1, nullptr, &value, &value});
  dut.push_back({1, &value, nullptr, &value});
  dut.push_back({1, &value, &value, nullptr});

  for (const auto& entry : dut) {
    EXPECT_EQ(entry.size(), 0);
    EXPECT_EQ(entry.red(0), 0);
    EXPECT_EQ(entry.green(0), 0);
    EXPECT_EQ(entry.blue(0), 0);
  }
}

/**
 * @brief This test case tests whether the assignment operator creates a copy of the original
 * midi2dmx::dmx::DmxRgbChannels object.
 *
 */
TEST_F(DmxRgbChannelsTestSuite, assignment_operator) {
  const std::vector<uint8_t> rgb{1, 2, 3};
  DmxRgbChannels obj(1, &rgb[0], &rgb[1], &rgb[2]);

  auto other = obj;

  EXPECT_EQ(other.size(), 1);
  EXPECT_EQ(other.red(0), rgb[0]);
  EXPECT_EQ(other.green(0), rgb[1]);
  EXPECT_EQ(other.blue(0), rgb[2]);
}

/**
 * @brief This test case tests whether the midi2dmx::dmx::DmxRgbChannels::red() function returns the
 * correct red channel value.
 *
 */
TEST_F(DmxRgbChannelsTestSuite, red_returns_r_value) {
  const std::vector<uint8_t> rgb{1, 2, 3};
  DmxRgbChannels dut(1, &rgb[0], &rgb[1], &rgb[2]);

  EXPECT_EQ(dut.red(0), rgb[0]);
}

/**
 * @brief This test case tests whether the midi2dmx::dmx::DmxRgbChannels::green() function returns
 * the correct green channel value.
 *
 */
TEST_F(DmxRgbChannelsTestSuite, green_returns_g_value) {
  const std::vector<uint8_t> rgb{1, 2, 3};
  DmxRgbChannels dut(1, &rgb[0], &rgb[1], &rgb[2]);

  EXPECT_EQ(dut.green(0), rgb[1]);
}

/**
 * @brief This test case tests whether the midi2dmx::dmx::DmxRgbChannels::blue() function returns
 * the correct blue channel value.
 *
 */
TEST_F(DmxRgbChannelsTestSuite, blue_returns_b_value) {
  const std::vector<uint8_t> rgb{1, 2, 3};
  DmxRgbChannels dut(1, &rgb[0], &rgb[1], &rgb[2]);

  EXPECT_EQ(dut.blue(0), rgb[2]);
}

/**
 * @brief This test case tests whether the function midi2dmx::dmx::DmxRgbChannels::red() returns 0
 * if an attempt is made to access outside the array limits.
 *
 */
TEST_F(DmxRgbChannelsTestSuite, red_returns_0_if_outOfBounds) {
  const std::vector<uint8_t> rgb{1, 2, 3};
  DmxRgbChannels dut(1, &rgb[0], &rgb[1], &rgb[2]);

  EXPECT_EQ(dut.red(1), 0);
}

/**
 * @brief This test case tests whether the function midi2dmx::dmx::DmxRgbChannels::green() returns 0
 * if an attempt is made to access outside the array limits.
 *
 */
TEST_F(DmxRgbChannelsTestSuite, green_returns_0_if_outOfBounds) {
  const std::vector<uint8_t> rgb{1, 2, 3};
  DmxRgbChannels dut(1, &rgb[0], &rgb[1], &rgb[2]);

  EXPECT_EQ(dut.green(1), 0);
}

/**
 * @brief This test case tests whether the function midi2dmx::dmx::DmxRgbChannels::blue() returns 0
 * if an attempt is made to access outside the array limits.
 *
 */
TEST_F(DmxRgbChannelsTestSuite, blue_returns_0_if_outOfBounds) {
  const std::vector<uint8_t> rgb{1, 2, 3};
  DmxRgbChannels dut(1, &rgb[0], &rgb[1], &rgb[2]);

  EXPECT_EQ(dut.blue(1), 0);
}
}  // namespace midi2dmx::unittest
