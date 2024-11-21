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

#include "synth2/ext/note-ports.h"

#include <string.h>

static uint32_t
synth2_plugin_note_ports_count(const clap_plugin_t *plugin, bool is_input) {
    return is_input ? 1 : 0;
}

static bool synth2_plugin_note_ports_get(
    const clap_plugin_t *plugin,
    uint32_t index,
    bool is_input,
    clap_note_port_info_t *info
) {
    if (!is_input || index > 0) return false;

    info->id = 0;
    info->supported_dialects =
        CLAP_NOTE_DIALECT_CLAP | CLAP_NOTE_DIALECT_MIDI_MPE | CLAP_NOTE_DIALECT_MIDI2;
    info->preferred_dialect = CLAP_NOTE_DIALECT_CLAP;
    strncpy(info->name, "", sizeof(info->name));
    return true;
}

const clap_plugin_note_ports_t synth2_plugin_note_ports = {
    .count = synth2_plugin_note_ports_count,
    .get = synth2_plugin_note_ports_get,
};
