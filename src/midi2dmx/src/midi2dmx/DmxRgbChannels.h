/**
 * @file DmxRgbChannels.h
 * @author Christian Neukam
 * @brief Definition of the DmxRgbChannels class and the DmxRgb struct.
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
#ifndef __MIDI2DMX_DMX_RGB_H__
#define __MIDI2DMX_DMX_RGB_H__

#include <stdint.h>

namespace midi2dmx::dmx {
static const uint8_t kMaxRgbSize = 42; /**< corresponds to floor(128 / 3) */

/**
 * @brief This struct defines a color in the red-green-blue (RGB) domain.
 *
 */
struct DmxRgb {
  uint8_t red;   /**< the red color intensity */
  uint8_t green; /**< the green color intensity */
  uint8_t blue;  /**< the blue color intensity */
};

/**
 * @brief This class defines the DMX channels associated with the RGB colors of the lightning
 * system.
 *
 */
class DmxRgbChannels {
 public:
  /**
   * @brief Construct a new DmxRgbChannels object.
   *
   */
  DmxRgbChannels();

  /**
   * @brief Construct a new DmxRgbChannels object.
   *
   * If the number of channels as specified via \p s exceeds the maximum number of supported
   * channels \p kMaxRgbSize, the incoming value is clipped to kMaxRgbSize.
   *
   * @param[in] s the size of the following arrays
   * @param[in] r the red DMX channels
   * @param[in] g the green DMX channels
   * @param[in] b the blue DMX channels
   */
  DmxRgbChannels(const uint8_t s, uint8_t const* const r, uint8_t const* const g,
                 uint8_t const* const b);

  /**
   * @brief Assignment operator for a DmxRgbChannels object.
   *
   * @param[in] rhs the right-hand-side object
   */
  void operator=(const DmxRgbChannels& rhs);

  /**
   * @brief Get the size of the RGB channels.
   *
   * @return uint8_t - the size of the container
   */
  uint8_t size() const;

  /**
   * @brief Get the R (red) value of the given channel.
   *
   * @param[in] ch the channel to query
   * @return uint8_t - the R value
   */
  uint8_t red(const uint8_t ch) const;

  /**
   * @brief Get the G (green) value of the given channel.
   *
   * @param[in] ch the channel to query
   * @return uint8_t - the G value
   */
  uint8_t green(const uint8_t ch) const;

  /**
   * @brief Get the B (blue) value of the given channel.
   *
   * @param[in] ch the channel to query
   * @return uint8_t - the B value
   */
  uint8_t blue(const uint8_t ch) const;

 private:
  uint8_t mSize;               /**< the size of the channel arrays */
  uint8_t mRed[kMaxRgbSize];   /**< the red DMX channels */
  uint8_t mGreen[kMaxRgbSize]; /**< the green DMX channels */
  uint8_t mBlue[kMaxRgbSize];  /**< the blue DMX channels */
};
}  // namespace midi2dmx::dmx
#endif
