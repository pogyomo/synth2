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

#include "synth2/process-event.h"

#include <stdlib.h>

#include "synth2/adsr.h"
#include "synth2/filter.h"
#include "synth2/helper.h"
#include "synth2/macros.h"
#include "synth2/osc.h"
#include "synth2/params.h"
#include "synth2/random.h"

static inline double convert_amp_a(const synth2_params_amp_t *amp) {
    return ((double)amp->a / 128.0) * 2.0 + 0.005;
}

static inline double convert_amp_d(const synth2_params_amp_t *amp) {
    return ((double)amp->d / 128.0) * 2.0 + 0.005;
}

static inline double convert_amp_s(const synth2_params_amp_t *amp) {
    return (double)amp->s / 128.0;
}

static inline double convert_amp_r(const synth2_params_amp_t *amp) {
    return ((double)amp->r / 128.0) * 2.0 + 0.005;
}

static inline double convert_filter_a(const synth2_params_filter_t *filter) {
    return ((double)filter->a / 128.0) * 2.0 + 0.005;
}

static inline double convert_filter_d(const synth2_params_filter_t *filter) {
    return ((double)filter->d / 128.0) * 2.0 + 0.005;
}

static inline double convert_filter_s(const synth2_params_filter_t *filter) {
    return (double)filter->s / 128.0;
}

static inline double convert_filter_r(const synth2_params_filter_t *filter) {
    return ((double)filter->r / 128.0) * 2.0 + 0.005;
}

static inline double convert_duty(uint8_t duty) {
    return ((double)duty / 128.0) * 0.875 + 0.125;
}

static inline double convert_filter_freq(double sample_rate, uint8_t freq) {
    return k2f(freq, 0);
}

static double convert_osc1_freq(
    const synth2_params_osc1_t *osc1,
    int16_t key,
    double cent
) {
    if (osc1->track) {
        return k2f(69, 0);
    } else {
        return k2f(key + osc1->pitch, (double)osc1->cent + cent);
    }
}

static double convert_osc2_freq(
    const synth2_params_osc2_t *osc2,
    int16_t key,
    double cent
) {
    if (osc2->track) {
        return k2f(69, 0);
    } else {
        return k2f(key + osc2->pitch, (double)osc2->cent + cent);
    }
}

static inline double unison_cent_d(const synth2_params_unison_t *unison) {
    // Currently I consider depth is the cent from voice1 to voiceN.
    // Returns cent between for each voice.
    return (double)unison->depth / (double)unison->size;
}

static inline double convert_oscs_phase(
    synth2_random_t *random,
    const synth2_params_oscs_t *oscs
) {
    double phase;
    if (oscs->phase == 128) {
        const synth2_random_value_t value = synth2_random_gen(random);
        phase = (double)(value - SYNTH2_RANDOM_MIN) /
                (double)(SYNTH2_RANDOM_MAX - SYNTH2_RANDOM_MIN);
    } else {
        phase = (double)oscs->phase / 128.0;
    }
    return phase * PI2;
}

static void init_voice(
    synth2_voice_t *voice,
    synth2_plugin_t *plugin,
    const clap_event_note_t *note,
    const size_t unison_index
) {
    const synth2_params_osc1_t *osc1 = &plugin->params.osc1;
    const synth2_params_osc2_t *osc2 = &plugin->params.osc2;
    const synth2_params_oscs_t *oscs = &plugin->params.oscs;
    const synth2_params_amp_t *amp = &plugin->params.amp;
    const synth2_params_filter_t *filter = &plugin->params.filter;
    const synth2_params_unison_t *unison = &plugin->params.unison;
    const double unison_cent = unison_cent_d(unison) * unison_index;
    const double phase = convert_oscs_phase(&plugin->random, oscs);

    const double osc1_freq = convert_osc1_freq(osc1, note->key, unison_cent);
    const double osc1_duty = convert_duty(osc1->duty);
    synth2_osc_init(
        &voice->osc1, osc1->wave, plugin->sample_rate, osc1_freq, osc1_duty,
        phase
    );

    const double osc2_freq = convert_osc2_freq(osc2, note->key, unison_cent);
    const double osc2_duty = convert_duty(osc2->duty);
    synth2_osc_init(
        &voice->osc2, osc2->wave, plugin->sample_rate, osc2_freq, osc2_duty,
        phase
    );

    const double amp_a = convert_amp_a(amp);
    const double amp_d = convert_amp_d(amp);
    const double amp_s = convert_amp_s(amp);
    const double amp_r = convert_amp_r(amp);
    synth2_adsr_init(
        &voice->amp, plugin->sample_rate, amp_a, amp_d, amp_s, amp_r
    );

    const double filter_a = convert_filter_a(filter);
    const double filter_d = convert_filter_d(filter);
    const double filter_s = convert_filter_s(filter);
    const double filter_r = convert_filter_r(filter);
    synth2_adsr_init(
        &voice->filter_adsr, plugin->sample_rate, filter_a, filter_d, filter_s,
        filter_r
    );

    const double filter_freq = convert_filter_freq(
        plugin->sample_rate, plugin->params.filter.freq
    );
    const double filter_res = (double)plugin->params.filter.res / 128.0;
    synth2_filter_init(
        &voice->filter, plugin->params.filter.type, plugin->sample_rate,
        filter_freq, filter_res
    );
}

/// Find unused voice, or oldest voice if all voice used.
static size_t find_useable_voice_idx(synth2_voice_t *voices) {
    synth2_voice_id_t min_id = UINT64_MAX;
    size_t min_idx;
    for (size_t i = 0; i < SYNTH2_PLUGIN_MAX_VOICES; i++) {
        if (voices[i].id < min_id) {
            min_id = voices[i].id;
            min_idx = i;
        }
        if (voices[i].state == SYNTH2_PLUGIN_VOICE_UNUSED) {
            return i;
        }
    }
    return min_idx;
}

static void process_note_on(
    synth2_plugin_t *plugin,
    const clap_event_note_t *note
) {
    const synth2_voice_id_t id = plugin->next_voice_id++;
    for (size_t i = 0; i < plugin->params.unison.size; i++) {
        size_t voice_idx = find_useable_voice_idx(plugin->voices);
        synth2_voice_t *voice = &plugin->voices[voice_idx];
        voice->state = SYNTH2_PLUGIN_VOICE_HOLDING;
        voice->note_id = note->note_id;
        voice->channel = note->channel;
        voice->key = note->key;
        voice->id = id;
        init_voice(voice, plugin, note, i);
    }
}

static void process_note_off(
    synth2_plugin_t *plugin,
    const clap_event_note_t *note
) {
    for (size_t i = 0; i < SYNTH2_PLUGIN_MAX_VOICES; i++) {
        synth2_voice_t *voice = &plugin->voices[i];
        if (voice->state != SYNTH2_PLUGIN_VOICE_HOLDING) continue;
        if (note->key != -1 && voice->key != note->key) continue;
        if (note->note_id != -1 && voice->note_id != note->note_id) continue;
        if (note->channel != -1 && voice->channel != note->channel) continue;

        voice->state = SYNTH2_PLUGIN_VOICE_RELEASE;
        synth2_adsr_keyoff(&voice->amp);
        synth2_adsr_keyoff(&voice->filter_adsr);
    }
}

static void process_param_value(
    synth2_plugin_t *plugin,
    const clap_event_param_value_t *value
) {
    // TODO: Need mutex for changing parameters?
    synth2_params_update(&plugin->params, value->param_id, value->value);
}

void synth2_process_event(
    synth2_plugin_t *plugin,
    const clap_event_header_t *event
) {
    if (event->space_id != CLAP_CORE_EVENT_SPACE_ID) return;

    if (event->type == CLAP_EVENT_NOTE_ON) {
        process_note_on(plugin, (clap_event_note_t *)event);
    } else if (event->type == CLAP_EVENT_NOTE_OFF) {
        process_note_off(plugin, (clap_event_note_t *)event);
    } else if (event->type == CLAP_EVENT_PARAM_VALUE) {
        process_param_value(plugin, (clap_event_param_value_t *)event);
    }
}
