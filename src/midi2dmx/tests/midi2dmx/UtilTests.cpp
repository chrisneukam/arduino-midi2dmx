/**
 * @file MidiReaderTest.cpp
 * @author Christian Neukam
 * @brief Unit Tests for the midi2dmx::util methods.
 * @version 1.0
 * @date 2024-01-07
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

#include <algorithm>

#include "util.h"

namespace midi2dmx::unittest {
using namespace midi2dmx::util;

/**
 * @brief This class provides the fixture for the Test Suite, which checks the
 * midi2dmx::util methods.
 *
 */
class UtilTestSuite : public testing::Test {};

/**
 * @brief This test case tests whether the function midi2dmx::util::max() returns the same result as
 * std::max().
 *
 */
TEST_F(UtilTestSuite, max_equals_std_max) {
  int a = 1;
  int b = 2;

  EXPECT_EQ(std::max(a, b), max(a, b));
  EXPECT_EQ(std::max(b, a), max(b, a));
  EXPECT_EQ(std::max(a, a), max(a, a));
}

/**
 * @brief This test case tests whether the function midi2dmx::util::min() returns the same result as
 * std::min().
 *
 */
TEST_F(UtilTestSuite, min_equals_std_min) {
  int a = 1;
  int b = 2;

  EXPECT_EQ(min(a, b), std::min(a, b));
  EXPECT_EQ(min(b, a), std::min(b, a));
  EXPECT_EQ(min(a, a), std::min(a, a));
}

/**
 * @brief This test case tests whether the function midi2dmx::util::min() returns the same result as
 * std::min().
 *
 */
TEST_F(UtilTestSuite, absDiff_returns_absoluteDifference) {
  int a = 1;
  int b = 2;

  EXPECT_EQ(absDiff(a, b), std::abs(a - b));
  EXPECT_EQ(absDiff(b, a), std::abs(b - a));
  EXPECT_EQ(absDiff(a, a), 0);
}
}  // namespace midi2dmx::unittest
