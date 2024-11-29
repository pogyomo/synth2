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

#ifndef SYNTH2_PLUGIN_H_
#define SYNTH2_PLUGIN_H_

#include <clap/plugin.h>
#include <stdint.h>

#include "synth2/params.h"
#include "synth2/random.h"
#include "synth2/voice.h"

#define SYNTH2_PLUGIN_MAX_VOICES 32

typedef struct synth2_plugin {
    const clap_host_t *host;
    clap_plugin_t plugin;

    /// Host's sample rate.
    double sample_rate;

    /// Parameters for modules
    synth2_params_t params;

    /// Random generator for initial osc phase.
    synth2_random_t random;

    /// Voices to be used to render audio.
    synth2_voice_id_t next_voice_id;
    synth2_voice_t voices[SYNTH2_PLUGIN_MAX_VOICES];
} synth2_plugin_t;

/// Descriptor of synth2 plugin.
extern const clap_plugin_descriptor_t synth2_plugin_descriptor;

/// Create plugin, return pointer to it.
const synth2_plugin_t *synth2_plugin_create(const clap_host_t *host);

#endif  // SYNTH2_PLUGIN_H_
