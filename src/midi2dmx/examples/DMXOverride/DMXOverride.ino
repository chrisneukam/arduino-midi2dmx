/**
 * @file DMXOverride.ino
 * @author Christian Neukam
 * @brief midi2dmx library example to demonstrate the DMX override functionality.
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

/**
 * @brief Implementation of the midi2dmx::ISerialReader interface.
 *
 * In this example, the implementation of the midi2dmx::ISerialReader interface simulates MIDI CC
 * data. As DMX override mode is active in this example, no data needs to be returned here.
 *
 */
class SerialReader : public midi2dmx::ISerialReader {
 public:
  int available() override { return 0; }

  int read() override { return 0; }

  void sleep(uint16_t sleep_ms) override { delay(sleep_ms); }
};

/**
 * @brief Implementation of the callback midi2dmx::dmx::DmxOnChangeCallback.
 *
 * This callback is always called as soon as a new DMX date is generated from a
 * different MIDI CC signal. The built-in LED lights up for different lengths of time depending on
 * the set gain value. The DMX data can then be sent further via a DMX library, e.g. DMXSerial.
 *
 * @see https://www.arduino.cc/reference/en/libraries/dmxserial/
 *
 * @param[in] channel the DMX channel
 * @param[in] value the DMX value
 */
void onDmxChange(const uint8_t channel, const uint8_t value) {
  digitalWrite(LED_BUILTIN, HIGH);
  delay(value);  // light up the LED
  digitalWrite(LED_BUILTIN, LOW);
  delay(value);  // switch off the LED
}

#define kMidiChannel 1      /**< the MIDI channel to listen to in the range [1, 16] */
static SerialReader reader; /**< the implementation of midi2dmx::ISerialReader */
static Midi2Dmx midiToDmx(kMidiChannel, onDmxChange, reader); /**< the instance of midi2dmx */

/**
 * @brief Setup the Arduino board.
 *
 */
void setup() {
  pinMode(LED_BUILTIN, OUTPUT);

  uint8_t ch = 1;  // assign the DMX channels for RGB here
  midiToDmx.setRgbOverride({1, &ch, &ch, &ch}, {0xff, 0xff, 0xff});
}

/**
 * @brief Main processing loop.
 *
 */
void loop() { midiToDmx.listen(true); }
