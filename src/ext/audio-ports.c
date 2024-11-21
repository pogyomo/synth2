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

#include "synth2/ext/audio-ports.h"

#include <stdio.h>

static uint32_t
synth2_plugin_audio_ports_count(const clap_plugin_t *plugin, bool is_input) {
    return is_input ? 0 : 1;
}

static bool synth2_plugin_audio_ports_get(
    const clap_plugin_t *plugin,
    uint32_t index,
    bool is_input,
    clap_audio_port_info_t *info
) {
    if (is_input || index > 0) return false;

    info->id = 0;
    snprintf(info->name, sizeof(info->name), "");
    info->flags = CLAP_AUDIO_PORT_IS_MAIN;
    info->channel_count = 2;
    info->port_type = CLAP_PORT_STEREO;
    info->in_place_pair = CLAP_INVALID_ID;
    return true;
}

const clap_plugin_audio_ports_t synth2_plugin_audio_ports = {
    .count = synth2_plugin_audio_ports_count,
    .get = synth2_plugin_audio_ports_get,
};
