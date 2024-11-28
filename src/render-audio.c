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

#include "synth2/render-audio.h"

#include "synth2/adsr.h"
#include "synth2/filter.h"
#include "synth2/helper.h"

static inline int16_t clamp(
    int16_t value,
    int16_t min_value,
    int16_t max_value
) {
    if (value < min_value) {
        return min_value;
    } else if (value > max_value) {
        return max_value;
    } else {
        return value;
    }
}

static inline double process_oscs(
    const synth2_plugin_t *plugin,
    synth2_voice_t *voice
) {
    const double osc1 = synth2_osc_sample(&voice->osc1);
    const double osc2 = synth2_osc_sample(&voice->osc2);
    const double osc2_mix = (double)plugin->params.oscs.mix / 128.0;
    const double osc1_mix = 1.0 - osc2_mix;
    const double mixed = osc1 * osc1_mix + osc2 * osc2_mix;
    return mixed;
}

static inline double process_amp(
    const synth2_plugin_t *plugin,
    synth2_voice_t *voice,
    double in
) {
    const double sampled = synth2_adsr_sample(&voice->amp);
    const double volume = sampled * (double)plugin->params.amp.gain / 128.0;
    return volume * in;
}

static inline double process_filter(
    const synth2_plugin_t *plugin,
    synth2_voice_t *voice,
    double in
) {
    const double sampled = synth2_adsr_sample(&voice->filter_adsr);
    const int16_t diff = sampled * plugin->params.filter.amt * 2;
    const int16_t freq = plugin->params.filter.freq + diff;
    synth2_filter_set_freq(&voice->filter, k2f(clamp(freq, 0, 128), 0));
    return synth2_filter_process(&voice->filter, in);
}

static inline double process_unison(const synth2_plugin_t *plugin, double in) {
    return in / (double)plugin->params.unison.size;
}

static inline double process_ctrl(const synth2_plugin_t *plugin, double in) {
    const double volume = (double)plugin->params.ctrl.volume / 128.0;
    return volume * in;
}

static inline double generate_auido(
    const synth2_plugin_t *plugin,
    synth2_voice_t *voice
) {
    double out = process_oscs(plugin, voice);
    out = process_amp(plugin, voice, out);
    out = process_filter(plugin, voice, out);
    out = process_unison(plugin, out);
    return process_ctrl(plugin, out);
}

static double render_audio(synth2_plugin_t *plugin) {
    double output = 0.0f;
    for (size_t i = 0; i < SYNTH2_PLUGIN_MAX_VOICES; i++) {
        synth2_voice_t *voice = &plugin->voices[i];

        if (voice->state == SYNTH2_PLUGIN_VOICE_HOLDING ||
            voice->state == SYNTH2_PLUGIN_VOICE_RELEASE) {
            output += generate_auido(plugin, voice);
        }

        if (voice->state == SYNTH2_PLUGIN_VOICE_RELEASE) {
            const synth2_adsr_stage_t state = synth2_adsr_current_stage(
                &voice->amp
            );
            if (state == SYNTH2_ADSR_STAGE_END) {
                voice->state = SYNTH2_PLUGIN_VOICE_POST_PROCESS;
            }
        }
    }
    return output;
}

void synth2_render_audio_f(
    synth2_plugin_t *plugin,
    uint32_t start,
    uint32_t end,
    float *outputL,
    float *outputR
) {
    for (uint32_t i = start; i < end; i++) {
        outputL[i] = outputR[i] = render_audio(plugin);
    }
}

void synth2_render_audio_d(
    synth2_plugin_t *plugin,
    uint32_t start,
    uint32_t end,
    double *outputL,
    double *outputR
) {
    for (uint32_t i = start; i < end; i++) {
        outputL[i] = outputR[i] = render_audio(plugin);
    }
}
