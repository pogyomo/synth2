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

// TODO:
// This module is used by more than two file.
// So, maybe this file need to be independent module.

#include "synth2/plugin/process-event.h"

#include "synth2-adsr/adsr.h"
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
            voice->osc = synth2_osc_create(
                plugin->osc_wave, plugin->sample_rate, k2f(note->key), 1.0
            );
            voice->adsr_vol =
                synth2_adsr_create(plugin->sample_rate, 0.01, 0.5, 0.5, 0.01);
            synth2_adsr_keyon(voice->adsr_vol);
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
            synth2_adsr_keyoff(voice->adsr_vol);
            break;
        }
    } else if (event->type == CLAP_EVENT_PARAM_VALUE) {
        // TODO: Need mutex for changing parameters?
        const clap_event_param_value_t *value = (clap_event_param_value_t *)event;
        if (value->param_id > 0) return;
        plugin->osc_wave = (synth2_osc_wave_t)value->value;
    }
}
