/**
 * @file midi2dmx.h
 * @author Christian Neukam
 * @brief API header file of the midi2dmx library
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

#include "midi2dmx/ContinuousController.h"

/**
 * @brief This namespace defines the scope of the \p midi2dmx library.
 *
 * It contains all classes, functions and symbols that are available both publicly and privately.
 *
 */
namespace midi2dmx {}

/**
 * @brief This namespace bundles all entities of the \p midi2dmx library that relate to MIDI input
 * and output.
 *
 */
namespace midi2dmx::midi {}

#endif
