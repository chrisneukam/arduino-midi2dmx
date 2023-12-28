/**
 * @file DmxValue.h
 * @author Christian Neukam
 * @brief Definition of the midi2dmx::Dmx class
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
#ifndef __MIDI2DMX_DMX_VALUE_H__
#define __MIDI2DMX_DMX_VALUE_H__

#include <stdint.h>

namespace midi2dmx::dmx {

/**
 * @brief This class defines a DMX datum.
 *
 */
class DmxValue {
 public:
  /**
   * @brief Construct a new DmxValue object.
   *
   * @param[in] channel the DMX channel
   * @param[in] value the DMX value
   */
  DmxValue(const uint8_t channel, const uint8_t value);

  /**
   * @brief Destroy the DmxValue object.
   *
   */
  virtual ~DmxValue() = default;

  /**
   * @brief Assignment operator for a DmxValue object.
   *
   * @param[in] rhs the right-hand-side DmxValue to copy the values from
   * @return DmxValue - a new DmxValue object
   */
  DmxValue& operator=(const DmxValue& rhs);

  /**
   * @brief Compare operator for a DmxValue object
   *
   * @param[in] rhs the right-hand-side DmxValue oject to compare to
   * @return true in case both object are equal
   * @return false otherwise
   */
  bool operator==(const DmxValue& rhs) const;

  /**
   * @brief Compare operator for a DmxValue object
   *
   * @param[in] rhs the right-hand-side DmxValue oject to compare to
   * @return true in case both object are equal
   * @return false otherwise
   */
  bool operator!=(const DmxValue& rhs) const;

  /**
   * @brief Get the DMX channel
   *
   * @return uint8_t - the dmx channel
   */
  uint8_t channel() const;

  /**
   * @brief Get the DMX value
   *
   * @return uint8_t - the DMX value
   */
  uint8_t value() const;

 private:
  uint8_t mChannel; /**< the DMX channel */
  uint8_t mValue;   /**< teh DMX value */
};
}  // namespace midi2dmx::dmx
#endif
