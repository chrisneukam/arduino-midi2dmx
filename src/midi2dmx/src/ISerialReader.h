/**
 * @file ISerialReader.h
 * @author Christian Neukam
 * @brief Definition of the midi2dmx::ISerialReader interface.
 * @version 1.0
 * @date 2023-12-31
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
#ifndef __MIDI2DMX_I_SERIAL_READER_H__
#define __MIDI2DMX_I_SERIAL_READER_H__

#include <stdint.h>

namespace midi2dmx {

/**
 * @brief Interface of an object reading data from a serial hardware interface.
 *
 */
class ISerialReader {
 public:
  /**
   * @brief Destroy the ISerialReader object.
   *
   */
  virtual ~ISerialReader() = default;

  /**
   * @brief Return the number of available bytes in the serial input buffer.
   *
   * @return int - the number of bytes available in the input buffer
   */
  virtual int available() = 0;

  /**
   * @brief Get the next byte from the serial input stack.
   *
   * @return int - the value of the data
   */
  virtual int read() = 0;

  /**
   * @brief Delay the current thread for the given time.
   *
   * @param[in] sleep_ms the wait time in ms
   */
  virtual void delay(uint8_t sleep_ms) = 0;
};
}  // namespace midi2dmx

#endif
