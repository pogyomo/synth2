// Copyright 2024 pogyomo
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#ifndef SYNTH2_PLUGIN_VOICE_H_
#define SYNTH2_PLUGIN_VOICE_H_

#include <stdbool.h>
#include <stdint.h>

/// This struct represent a ringing sounds.
typedef struct synth2_plugin_voice {
    /// True if corresponding key is being pressed.
    bool holding;

    /// The position of generation, in radian.
    float phase;

    // Derived from clap_event_note_t.
    int16_t note_id;
    int16_t channel;
    int16_t key;
} synth2_plugin_voice_t;

#endif  // SYNTH2_PLUGIN_VOICE_H_
