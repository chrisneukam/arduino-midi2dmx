/**
 * @file ContinuousController.h
 * @author Christian Neukam
 * @brief Definition of the midi2dmx::midi::ContinuousController class
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
#ifndef __MIDI2DMX_MIDI_CC_H__
#define __MIDI2DMX_MIDI_CC_H__

#include <stdint.h>

namespace midi2dmx::dmx {
class DmxValue; /**< forward declaration */
}

namespace midi2dmx::midi {

using midi2dmx::dmx::DmxValue;

/**
 * @brief This class defines the MIDI Continuous Controller (CC) for the conversion to a DMX value.
 *
 */
class ContinuousController {
 public:
  /**
   * @brief Default-Construct a new Continuous Controller object.
   *
   * All members will be set to zero.
   *
   */
  ContinuousController();

  /**
   * @brief Construct a new ContinuousController object.
   *
   * @param[in] controller the MIDI CC controller, i.e. the second MIDI byte
   * @param[in] value the MIDI CC controller value, i.e. the third MIDI byte
   */
  ContinuousController(const uint8_t controller, const uint8_t value);

  /**
   * @brief Destroy the ContinuousController object.
   *
   */
  virtual ~ContinuousController() = default;

  /**
   * @brief Compare operator for a ContinuousController object.
   *
   * @param[in] rhs the right-hand-side ContinuousController oject to compare to
   * @return true in case both object are equal
   * @return false otherwise
   */
  bool operator==(const ContinuousController& rhs) const;

  /**
   * @brief Compare operator for a ContinuousController object.
   *
   * @param[in] rhs the right-hand-side ContinuousController oject to compare to
   * @return true in case both object are equal
   * @return false otherwise
   */
  bool operator!=(const ContinuousController& rhs) const;

  /**
   * @brief Convert the MIDI Continuous Controller command (CC) to a DMX command.
   *
   * @return midi2dmx::dmx::DmxValue - the DMX value representing this MIDI CC command
   */
  DmxValue toDmx() const;

 private:
  const uint8_t mController; /**< the MIDI CC controller */
  const uint8_t mValue;      /**< the MIDI CC value */
};
}  // namespace midi2dmx::midi
#endif
