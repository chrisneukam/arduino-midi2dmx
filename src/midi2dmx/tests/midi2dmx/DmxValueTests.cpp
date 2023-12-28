/**
 * @file DmxValueTests.cpp
 * @author Christian Neukam
 * @brief Unit Tests for the midi2dmx::dmx::DmxValue
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

#include "midi2dmx.h"

namespace midi2dmx::unittest {
using namespace midi2dmx::dmx;

/**
 * @brief This class provides the fixture for the Test Suite, which checks the
 * midi2dmx::dmx::DmxValue.
 *
 */
class DmxValueTestSuite : public testing::Test {};

/**
 * @brief This test case checks whether the copy constructor of the midi2dmx::dmx::DmxValue
 * initializes a new object equal to the right-hand-side object.
 *
 */
TEST_F(DmxValueTestSuite, construct_copy) {
  DmxValue dmxValue{21, 42};

  EXPECT_EQ(dmxValue, DmxValue(dmxValue));
}

/**
 * @brief This test case checks whether the assignment operator of the midi2dmx::dmx::DmxValue
 * initializes a new object equal to the right-hand-side object.
 *
 */
TEST_F(DmxValueTestSuite, construct_assignment) {
  DmxValue dmxValue{21, 42};

  auto dut = dmxValue;
  EXPECT_EQ(dmxValue, dut);
}

/**
 * @brief This test case checks whether the compare operators of a midi2dmx::dmx::DmxValue return
 * the anticipated result.
 *
 */
TEST_F(DmxValueTestSuite, compare_operators) {
  DmxValue dmxValue{21, 42};

  EXPECT_TRUE(dmxValue == DmxValue(dmxValue));
  EXPECT_FALSE(dmxValue != DmxValue(dmxValue));
  EXPECT_FALSE(dmxValue == DmxValue(0, 0));
  EXPECT_TRUE(dmxValue != DmxValue(0, 0));
}
}  // namespace midi2dmx::unittest
