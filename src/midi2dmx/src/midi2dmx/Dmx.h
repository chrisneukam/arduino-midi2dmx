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
#ifndef __MIDI2DMX_DMX_H__
#define __MIDI2DMX_DMX_H__

#include <stdint.h>

#ifndef ARDUINO
#include <functional>
#endif

#include "DmxValue.h"

namespace midi2dmx::dmx {
static const uint8_t kAnalogReadBits = 10; /**< bit resolution of analog read */
static const uint16_t kUnityGainValue = (1 << kAnalogReadBits); /**< factor for unity gain */
static const uint16_t kGainDeadZone = 1; /**< the offset specifying the dead zone for gain values */

/**
 * @brief Definition of the callback signature
 *
 */
#ifdef ARDUINO
using DmxOnChangeCallback = void (*)(const uint8_t channel, const uint8_t value);
#else
using DmxOnChangeCallback = std::function<void(const uint8_t, const uint8_t)>;
#endif

/**
 * @brief This class provides the processing of DMX values.
 *
 */
class Dmx {
 public:
  /**
   * @brief Default-Construct a new Dmx object.
   *
   * An object created via this constructor does not support update notification via callbacks.
   *
   */
  Dmx();

  /**
   * @brief Construct a new Dmx object.
   *
   * An object created via this constructor calls the registered callback as soon as the DMX values
   * have changed.
   *
   * @param[in] callback the callback to trigger once the DMX values change
   */
  Dmx(DmxOnChangeCallback callback);

  /**
   * @brief Destroy the Dmx object.
   *
   */
  virtual ~Dmx() = default;

  /**
   * @brief Update the DMX gain.
   *
   * The gain is only updated if the parameter passed is outside the dead zone as indicated by
   * \p kGainDeadZone. This behavior can be overridden via the parameter \p force.
   *
   * The gain shall be in the range [0, ::kUnityGainValue] otherwise it is clipped.
   *
   * @param[in] gain the integer based gain value to apply
   * @param[in] force force the update of the gain value
   */
  void update(const uint16_t gain, const bool force = false);

  /**
   * @brief Update the DMX value pair.
   *
   * @param[in] dmxValue the DMX value pair to apply
   * @param[in] force force the update of the DMX value
   */
  void update(const DmxValue& dmxValue, const bool force = false);

 private:
  /**
   * @brief Apply the supplied gain value to the DMX value.
   *
   * @return uint8_t - the modified DMX value
   */
  uint8_t valueScaled() const;

  DmxValue mDmxValue;            /**< the current DMX value pair */
  uint16_t mGain;                /**< the current DMX gain factor */
  DmxOnChangeCallback mCallback; /**< the registered on-change callback */
};
}  // namespace midi2dmx::dmx
#endif
