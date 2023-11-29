/**
 * @file Dmx.h
 * @author Christian Neukam
 * @brief Definition of the midi2dmx::Dmx class
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
#ifndef __MIDI2DMX_TYPES_H__
#define __MIDI2DMX_TYPES_H__

namespace midi2dmx {
/**
 * @brief This struct defines a DMX datum.
 *
 */
struct Dmx {
  /**
   * @brief Construct a new Dmx object
   *
   * @param[in] channel the DMX channel
   * @param[in] value the DMX value
   */
  Dmx(const unsigned int channel, const unsigned int value) : channel(channel), value(value) {}

  /**
   * @brief Destroy the Dmx object
   *
   */
  virtual ~Dmx() = default;

  const unsigned int channel; /**< the DMX channel */
  const unsigned int value;   /**< the DMX value */
};
}  // namespace midi2dmx
#endif
