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

#include "synth2/plugin/process-event.h"

void synth2_plugin_process_event(
    synth2_plugin_t *plugin,
    const clap_event_header_t *event
) {
    if (event->space_id != CLAP_CORE_EVENT_SPACE_ID) return;

    if (event->type == CLAP_EVENT_NOTE_ON) {
        const clap_event_note_t *note = (const clap_event_note_t *)event;
        plugin->voice = (synth2_plugin_voice_t){
            .holding = true,
            .phase = 0.0,
            .note_id = note->note_id,
            .channel = note->channel,
            .key = note->key,
        };
    } else if (event->type == CLAP_EVENT_NOTE_OFF) {
        const clap_event_note_t *note = (const clap_event_note_t *)event;
        if (note->key != -1 && plugin->voice.key != note->key) return;
        if (note->note_id != -1 && plugin->voice.note_id != note->note_id) return;
        if (note->channel != -1 && plugin->voice.channel != note->channel) return;
        plugin->voice.holding = false;
    }
}
