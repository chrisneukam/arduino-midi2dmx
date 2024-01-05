/**
 * @file SleepMock.h
 * @author Christian Neukam
 * @brief Mock definition of the midi2dmx::ISleep interface
 * @version 1.0
 * @date 2024-01-06
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

#include "ISleep.h"

namespace midi2dmx::unittest {
/**
 * @brief This class provides the mock implementation of the midi2dmx::ISleep interface.
 *
 */
class SleepMock : public midi2dmx::ISleep {
 public:
  /**
   * @brief Mock methods from midi2dmx::ISleep.
   *
   */
  ///@{
  MOCK_METHOD(void, sleep, (uint16_t sleep_ms), (override));
  ///@}
};
}  // namespace midi2dmx::unittest
