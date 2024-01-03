/**
 * @file midi2dmx.h
 * @author Christian Neukam
 * @brief API header file of the midi2dmx library.
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
/*
  Copyright 2023 Christian Neukam

  Licensed under the Apache License, Version 2.0 (the "License");
  you may not use this file except in compliance with the License.
  You may obtain a copy of the License at

      http://www.apache.org/licenses/LICENSE-2.0

  Unless required by applicable law or agreed to in writing, software
  distributed under the License is distributed on an "AS IS" BASIS,
  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  See the License for the specific language governing permissions and
  limitations under the License.
*/
#ifndef __MIDI2DMX_H__
#define __MIDI2DMX_H__

#include "ISerialReader.h"
#include "midi2dmx/Dmx.h"
#include "midi2dmx/MidiReader.h"

using midi2dmx::ISerialReader;
using midi2dmx::dmx::Dmx;
using midi2dmx::dmx::DmxOnChangeCallback;
using midi2dmx::midi::MidiReader;

/**
 * @brief This class defines the API of the midi2dmx library.
 *
 * With the help of this API, MIDI Continuos Controller (CC) signals can be converted into DMX
 * control signals. The MIDI data is provided via a serial interface, which is abstracted via
 * midi2dmx::ISerialReader and must be implemented by the application.
 *
 * As soon as valid MIDI CC signals are received via a specific MIDI channel, a
 * midi2dmx::dmx::DmxOnChangeCallback callback is triggered, which contains the current DMX control
 * signals. One callback is triggered for each MIDI CC signal received.
 *
 * In order to adapt the brightness of the connected lighting to the local conditions, a gain can be
 * set to adjust the brightness. The signal can only be attenuated.
 *
 */
class Midi2Dmx {
 public:
  /**
   * @brief Construct a new Midi2Dmx object.
   *
   * @param[in] channel the MIDI channel to listen to
   * @param[in] callback the callback to trigger once the DMX values change
   * @param[in] serial the serial interface
   */
  Midi2Dmx(const uint8_t channel, DmxOnChangeCallback callback, ISerialReader& serial);

  /**
   * @brief Destroy the Midi2Dmx object.
   *
   */
  virtual ~Midi2Dmx() = default;

  /**
   * @brief Sets the gain attenuation for the following MIDI-to-DMX conversions.
   *
   * The gain shall be in the range [0, midi2dmx::dmx::kUnityGainValue] otherwise it is clipped
   * whereas unity gain does mean no attenuation.
   *
   * @param[in] gain the integer based gain attenuation to apply
   */
  void gainUpdate(const uint16_t gain);

  /**
   * @brief Read the next MIDI CC value and update the DMX state.
   *
   */
  void serialUpdate();

 private:
  Dmx mDmx;           /**< the DMX handler object */
  MidiReader mReader; /**< the MIDI reader object */
};

#endif
