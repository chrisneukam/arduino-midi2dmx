/**
 * @file Basic_IO.ino
 * @author Christian Neukam
 * @brief midi2dmx library example to demonstrate the basic IO functionality.
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
#include <midi2dmx.h>

#if defined(ARDUINO_SAM_DUE) || defined(USBCON) || defined(__MK20DX128__) || \
    defined(__MK20DX256__) || defined(__MKL26Z64__)
#define ArduinoSerial Serial1 /**< Leonardo, Due and other USB boards use Serial1 by default. */
#else
#define ArduinoSerial Serial /**< Other boards use Serial instead. */
#endif

/**
 * @brief Implementation of the midi2dmx::ISerialReader interface.
 *
 * As the interface midi2dmx::ISerialReader is defined as an abstraction layer
 * of the Arduino Serial API it just forwards the serial calls.
 *
 */
class SerialReader : public midi2dmx::ISerialReader {
 public:
  /**
   * @brief Construct a new SerialReader object.
   *
   * Initialize the serial adapter at the MIDI baud rate.
   *
   */
  SerialReader() { ArduinoSerial.begin(31250); }

  int available() override { return ArduinoSerial.available(); }

  int read() override { return ArduinoSerial.read(); }

  void sleep(uint16_t sleep_ms) override { delay(sleep_ms); }
};

/**
 * @brief Implementation of the callback midi2dmx::dmx::DmxOnChangeCallback.
 *
 * This callback is always called as soon as a new DMX date is generated from a
 * different MIDI CC signal. The built-in LED will flash according to the DMX channel.
 * The DMX data can then be sent further via a DMX library, e.g. DMXSerial.
 *
 * @see https://www.arduino.cc/reference/en/libraries/dmxserial/
 *
 * @param[in] channel the DMX channel
 * @param[in] value the DMX value
 */
static void onDmxChange(const uint8_t channel, const uint8_t value) {
  for (uint8_t c = 0; c < channel; c++) {
    digitalWrite(LED_BUILTIN, HIGH);
    delay(100);
    digitalWrite(LED_BUILTIN, LOW);
    delay(100);
  }
}

#define kMidiChannel 1      /**< the MIDI channel to listen to in the range [1, 16] */
static SerialReader reader; /**< the implementation of midi2dmx::ISerialReader */
static Midi2Dmx midiToDmx(kMidiChannel, onDmxChange, reader); /**< the instance of midi2dmx */

/**
 * @brief Setup the Arduino board.
 *
 */
void setup() { pinMode(LED_BUILTIN, OUTPUT); }

/**
 * @brief Main processing loop.
 *
 */
void loop() { midiToDmx.listen(); }
