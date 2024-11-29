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

#ifndef SYNTH2_VOICE_H_
#define SYNTH2_VOICE_H_

#include <stdbool.h>
#include <stdint.h>

#include "synth2/adsr.h"
#include "synth2/filter.h"
#include "synth2/osc.h"

typedef uint64_t synth2_voice_id_t;

/// The state of synth2_plugin_voice_t.
/// The state changes from top to bottom, then back to top.
typedef enum synth2_voice_state {
    /// The voice is not attached to any sound.
    SYNTH2_VOICE_UNUSED,

    /// The voice is attached to a sound generated by pressing key.
    SYNTH2_VOICE_HOLDING,

    /// Key was released, decaying sound.
    SYNTH2_VOICE_RELEASE,

    /// Sound generation finished. Do post process for host.
    SYNTH2_VOICE_POST_PROCESS,
} synth2_voice_state_t;

/// This struct represent a maybe playing sounds.
typedef struct synth2_voice {
    /// Current state of this voice.
    synth2_voice_state_t state;

    /// When this voice lastly used.
    /// Voice with smaller id is older.
    synth2_voice_id_t id;

    /// Objects for wave generation.
    synth2_osc_t osc1;
    synth2_osc_t osc2;
    synth2_adsr_t amp;
    synth2_adsr_t mod;
    synth2_adsr_t filter_adsr;
    synth2_filter_t filter;

    // Derived from clap_event_note_t.
    int16_t note_id;
    int16_t channel;
    int16_t key;
} synth2_voice_t;

#endif  // SYNTH2_VOICE_H_
