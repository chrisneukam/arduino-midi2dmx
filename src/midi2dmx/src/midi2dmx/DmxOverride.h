/**
 * @file DmxOverride.h
 * @author Christian Neukam
 * @brief Definition of the DMX override mode handling class.
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
#ifndef __MIDI2DMX_DMX_OVERRIDE_MODE_H__
#define __MIDI2DMX_DMX_OVERRIDE_MODE_H__

#include <stdint.h>

#include "DmxRgbChannels.h"

namespace midi2dmx {
class ISleep; /**< forward declaration */
}

namespace midi2dmx::dmx {
class Dmx; /**< forward declaration */

/**
 * @brief This class defines the behavior of the DMX override mode.
 *
 * In DMX override mode, a predefined static scene is sent via the DMX interface at a constant time
 * interval instead of the translated MIDI CC signals.
 *
 */
class DmxOverride {
 public:
  /**
   * @brief Construct a new DmxOverride object
   *
   * @param[in] sleep the sleep handler object
   */
  DmxOverride(ISleep& sleep);

  /**
   * @brief Setup the properties of the DMX override mode.
   *
   * @param[in] channels the DMX channels associated with RGB
   * @param[in] rgb the RGB value to set
   */
  void setRgbOverride(const DmxRgbChannels& channels, const DmxRgb& rgb);

 protected:
  /**
   * @brief Send the actual static DMX scene to the DMX handler.
   *
   * @param[in] dmx the DMX handler object to send the scene to
   */
  void sendStaticScene(Dmx& dmx);

  ISleep& mSleep; /**< the sleep handler object */

 private:
  DmxRgb mRgb;              /**< the RGB value to set */
  DmxRgbChannels mChannels; /**< the RGB DMX channels */
};
}  // namespace midi2dmx::dmx
#endif
