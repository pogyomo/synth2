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
#include "synth2-osc/osc.h"
#include "synth2/helper.h"
#include "synth2/params.h"

static inline double convert_amp_a(const synth2_params_amp_t *amp) {
    return ((double)amp->a / 128.0) * 2.0;
}

static inline double convert_amp_d(const synth2_params_amp_t *amp) {
    return ((double)amp->d / 128.0) * 2.0;
}

static inline double convert_amp_s(const synth2_params_amp_t *amp) {
    return (double)amp->s / 128.0;
}

static inline double convert_amp_r(const synth2_params_amp_t *amp) {
    return ((double)amp->r / 128.0) * 2.0;
}

static void init_voice(
    synth2_plugin_voice_t *voice,
    synth2_plugin_t *plugin,
    const clap_event_note_t *note
) {
    const synth2_params_osc1_t *osc1 = &plugin->params.osc1;
    const synth2_params_osc2_t *osc2 = &plugin->params.osc2;
    const synth2_params_oscs_t *oscs = &plugin->params.oscs;
    const synth2_params_amp_t *amp = &plugin->params.amp;

    const double osc1_freq = k2f(note->key);
    const double osc1_duty = (double)osc1->duty / 128.0;
    synth2_osc_init(&voice->osc1, osc1->wave, plugin->sample_rate, osc1_freq, osc1_duty);

    const double osc2_freq = k2f(note->key + osc2->pitch) + (double)osc2->cent;
    const double osc2_duty = (double)osc2->duty / 128.0;
    synth2_osc_init(&voice->osc2, osc2->wave, plugin->sample_rate, osc2_freq, osc2_duty);

    const double amp_a = convert_amp_a(amp);
    const double amp_d = convert_amp_d(amp);
    const double amp_s = convert_amp_s(amp);
    const double amp_r = convert_amp_r(amp);
    synth2_adsr_init(&voice->amp, plugin->sample_rate, amp_a, amp_d, amp_s, amp_r);
}

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
            voice->note_id = note->note_id;
            voice->channel = note->channel;
            voice->key = note->key;
            init_voice(voice, plugin, note);
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
            synth2_adsr_keyoff(&voice->amp);
            break;
        }
    } else if (event->type == CLAP_EVENT_PARAM_VALUE) {
        // TODO: Need mutex for changing parameters?
        const clap_event_param_value_t *value = (clap_event_param_value_t *)event;
        synth2_params_update(&plugin->params, value->param_id, value->value);
    }
}
