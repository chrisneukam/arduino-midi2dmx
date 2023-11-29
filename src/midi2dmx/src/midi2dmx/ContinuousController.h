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
#ifndef __MIDI2DMX_MIDI_H__
#define __MIDI2DMX_MIDI_H__

#include "Dmx.h"

namespace midi2dmx::midi {

/**
 * @brief This class defines the MIDI Continuous Controller (CC) for the conversion to a DMX value.
 *
 */
class ContinuousController {
 public:
  /**
   * @brief Construct a new ContinuousController object.
   *
   * @param[in] controller the MIDI CC controller, i.e. the second MIDI byte
   * @param[in] value the MIDI CC controller value, i.e. the third MIDI byte
   */
  ContinuousController(const unsigned int controller, const unsigned int value);

  /**
   * @brief Destroy the ContinuousController object.
   *
   */
  virtual ~ContinuousController() = default;

  /**
   * @brief Set the DMX gain.
   *
   * The gain is in the range [0, ::kUnityGainValue].
   *
   * @param[in] gain the integer based gain value to apply
   */
  void setGain(const unsigned int gain);

  /**
   * @brief Convert the MIDI Continuous Controller command (CC) to a DMX command.
   *
   * @return Dmx - the DMX value representing this MIDI CC command
   */
  Dmx toDmx() const;

 private:
  /**
   * @brief Apply the supplied gain value to the DMX value.
   *
   * @param[in] value the DMX value to apply the gain to
   * @return unsigned int - the modified DMX value
   */
  unsigned int applyGain(const unsigned int value) const;

  const unsigned int mController; /**< the MIDI CC controller */
  const unsigned int mValue;      /**< the MIDI CC value */
  unsigned int mGain;             /**< the gain to scale the value */
};
}  // namespace midi2dmx::midi
#endif
