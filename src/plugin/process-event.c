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

#include "synth2/helper.h"

void synth2_plugin_process_event(
    synth2_plugin_t *plugin,
    const clap_event_header_t *event
) {
    if (event->space_id != CLAP_CORE_EVENT_SPACE_ID) return;

    if (event->type == CLAP_EVENT_NOTE_ON) {
        const clap_event_note_t *note = (const clap_event_note_t *)event;
        for (size_t i = 0; i < SYNTH2_PLUGIN_MAX_VOICES; i++) {
            synth2_plugin_voice_t *voice = &plugin->voices[i];
            if (voice->state != SYNTH2_PLUGIN_VOICE_UNUSED) continue;

            voice->state = SYNTH2_PLUGIN_VOICE_HOLDING;
            voice->phase = 0.0f;
            voice->note_id = note->note_id;
            voice->channel = note->channel;
            voice->key = note->key;
            synth2_oscillator_init(
                &voice->osc, SYNTH2_OSC_METHOD_NAIVE, SYNTH2_OSC_WAVE_SINE,
                plugin->sample_rate, k2f(note->key), 0.0
            );
            break;
        }
    } else if (event->type == CLAP_EVENT_NOTE_OFF) {
        const clap_event_note_t *note = (const clap_event_note_t *)event;
        for (size_t i = 0; i < SYNTH2_PLUGIN_MAX_VOICES; i++) {
            synth2_plugin_voice_t *voice = &plugin->voices[i];
            if (voice->state != SYNTH2_PLUGIN_VOICE_HOLDING) continue;
            if (note->key != -1 && voice->key != note->key) continue;
            if (note->note_id != -1 && voice->note_id != note->note_id) continue;
            if (note->channel != -1 && voice->channel != note->channel) continue;

            voice->state = SYNTH2_PLUGIN_VOICE_RELEASE;
            break;
        }
    }
}
