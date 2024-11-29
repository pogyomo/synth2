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

#include "synth2/params.h"

#include <stdio.h>
#include <string.h>

const synth2_params_t synth2_params_default_value = {
    {SYNTH2_OSC_WAVE_SINE, 128, 0, 0, false},
    {SYNTH2_OSC_WAVE_SINE, 128, 0, 0, false},
    {64, 0},
    {SYNTH2_PARAM_MOD_FM, 0, 0, 128, 0, 0},
    {0, 0, 128, 0, 64},
    {SYNTH2_FILTER_LP, 0, 0, 128, 0, 0, 128, 0},
    {1, 0},
    {64},
};

bool synth2_params_get_info(uint32_t param_index, clap_param_info_t *info) {
    const synth2_params_t *params = &synth2_params_default_value;
    switch ((synth2_param_id_t)param_index) {
        case SYNTH2_PARAM_ID_OSC1_WAVE:
            info->id = param_index;
            info->flags = CLAP_PARAM_IS_ENUM | CLAP_PARAM_IS_STEPPED;
            strncpy(info->name, "Wave", sizeof(info->name));
            strncpy(info->module, "Oscillator1", sizeof(info->module));
            info->min_value = SYNTH2_OSC_WAVE_MIN;
            info->max_value = SYNTH2_OSC_WAVE_MAX;
            info->default_value = params->osc1.wave;
            return true;
        case SYNTH2_PARAM_ID_OSC1_DUTY:
            info->id = param_index;
            info->flags = 0;
            strncpy(info->name, "Duty", sizeof(info->name));
            strncpy(info->module, "Oscillator1", sizeof(info->module));
            info->min_value = 0;
            info->max_value = 128;
            info->default_value = params->osc1.duty;
            return true;
        case SYNTH2_PARAM_ID_OSC1_PITCH:
            info->id = param_index;
            info->flags = 0;
            strncpy(info->name, "Pitch", sizeof(info->name));
            strncpy(info->module, "Oscillator1", sizeof(info->module));
            info->min_value = -64;
            info->max_value = 64;
            info->default_value = params->osc1.pitch;
            return true;
        case SYNTH2_PARAM_ID_OSC1_CENT:
            info->id = param_index;
            info->flags = 0;
            strncpy(info->name, "Cent", sizeof(info->name));
            strncpy(info->module, "Oscillator1", sizeof(info->module));
            info->min_value = -64;
            info->max_value = 64;
            info->default_value = params->osc1.cent;
            return true;
        case SYNTH2_PARAM_ID_OSC1_TRACK:
            info->id = param_index;
            info->flags = CLAP_PARAM_IS_STEPPED;
            strncpy(info->name, "Track", sizeof(info->name));
            strncpy(info->module, "Oscillator1", sizeof(info->module));
            info->min_value = false;
            info->max_value = true;
            info->default_value = params->osc1.track;
            return true;
        case SYNTH2_PARAM_ID_OSC2_WAVE:
            info->id = param_index;
            info->flags = CLAP_PARAM_IS_ENUM | CLAP_PARAM_IS_STEPPED;
            strncpy(info->name, "Wave", sizeof(info->name));
            strncpy(info->module, "Oscillator2", sizeof(info->module));
            info->min_value = SYNTH2_OSC_WAVE_MIN;
            info->max_value = SYNTH2_OSC_WAVE_MAX;
            info->default_value = params->osc2.wave;
            return true;
        case SYNTH2_PARAM_ID_OSC2_DUTY:
            info->id = param_index;
            info->flags = 0;
            strncpy(info->name, "Duty", sizeof(info->name));
            strncpy(info->module, "Oscillator2", sizeof(info->module));
            info->min_value = 0;
            info->max_value = 128;
            info->default_value = params->osc2.duty;
            return true;
        case SYNTH2_PARAM_ID_OSC2_PITCH:
            info->id = param_index;
            info->flags = 0;
            strncpy(info->name, "Pitch", sizeof(info->name));
            strncpy(info->module, "Oscillator2", sizeof(info->module));
            info->min_value = -64;
            info->max_value = 64;
            info->default_value = params->osc2.pitch;
            return true;
        case SYNTH2_PARAM_ID_OSC2_CENT:
            info->id = param_index;
            info->flags = 0;
            strncpy(info->name, "Cent", sizeof(info->name));
            strncpy(info->module, "Oscillator2", sizeof(info->module));
            info->min_value = -64;
            info->max_value = 64;
            info->default_value = params->osc2.cent;
            return true;
        case SYNTH2_PARAM_ID_OSC2_TRACK:
            info->id = param_index;
            info->flags = CLAP_PARAM_IS_STEPPED;
            strncpy(info->name, "Track", sizeof(info->name));
            strncpy(info->module, "Oscillator2", sizeof(info->module));
            info->min_value = false;
            info->max_value = true;
            info->default_value = params->osc2.track;
            return true;
        case SYNTH2_PARAM_ID_OSCS_MIX:
            info->id = param_index;
            info->flags = 0;
            strncpy(info->name, "Mix", sizeof(info->name));
            strncpy(info->module, "Oscillators", sizeof(info->module));
            info->min_value = 0;
            info->max_value = 128;
            info->default_value = params->oscs.mix;
            return true;
        case SYNTH2_PARAM_ID_OSCS_PHASE:
            info->id = param_index;
            info->flags = 0;
            strncpy(info->name, "Phase", sizeof(info->name));
            strncpy(info->module, "Oscillators", sizeof(info->module));
            info->min_value = 0;
            info->max_value = 128;
            info->default_value = params->oscs.phase;
            return true;
        case SYNTH2_PARAM_ID_MOD_TYPE:
            info->id = param_index;
            info->flags = CLAP_PARAM_IS_ENUM | CLAP_PARAM_IS_STEPPED;
            strncpy(info->name, "Type", sizeof(info->name));
            strncpy(info->module, "Modulator", sizeof(info->module));
            info->min_value = SYNTH2_PARAM_MOD_MIN;
            info->max_value = SYNTH2_PARAM_MOD_MAX;
            info->default_value = params->mod.type;
            return true;
        case SYNTH2_PARAM_ID_MOD_A:
            info->id = param_index;
            info->flags = 0;
            strncpy(info->name, "A", sizeof(info->name));
            strncpy(info->module, "Modulator", sizeof(info->module));
            info->min_value = 0;
            info->max_value = 128;
            info->default_value = params->mod.a;
            return true;
        case SYNTH2_PARAM_ID_MOD_D:
            info->id = param_index;
            info->flags = 0;
            strncpy(info->name, "D", sizeof(info->name));
            strncpy(info->module, "Modulator", sizeof(info->module));
            info->min_value = 0;
            info->max_value = 128;
            info->default_value = params->mod.d;
            return true;
        case SYNTH2_PARAM_ID_MOD_S:
            info->id = param_index;
            info->flags = 0;
            strncpy(info->name, "S", sizeof(info->name));
            strncpy(info->module, "Modulator", sizeof(info->module));
            info->min_value = 0;
            info->max_value = 128;
            info->default_value = params->mod.s;
            return true;
        case SYNTH2_PARAM_ID_MOD_R:
            info->id = param_index;
            info->flags = 0;
            strncpy(info->name, "R", sizeof(info->name));
            strncpy(info->module, "Modulator", sizeof(info->module));
            info->min_value = 0;
            info->max_value = 128;
            info->default_value = 0;
            info->default_value = params->mod.r;
            return true;
        case SYNTH2_PARAM_ID_MOD_AMT:
            info->id = param_index;
            info->flags = 0;
            strncpy(info->name, "Amt", sizeof(info->name));
            strncpy(info->module, "Modulator", sizeof(info->module));
            info->min_value = 0;
            info->max_value = 128;
            info->default_value = params->mod.amt;
            return true;
        case SYNTH2_PARAM_ID_AMP_A:
            info->id = param_index;
            info->flags = 0;
            strncpy(info->name, "A", sizeof(info->name));
            strncpy(info->module, "Amplifier", sizeof(info->module));
            info->min_value = 0;
            info->max_value = 128;
            info->default_value = params->amp.a;
            return true;
        case SYNTH2_PARAM_ID_AMP_D:
            info->id = param_index;
            info->flags = 0;
            strncpy(info->name, "D", sizeof(info->name));
            strncpy(info->module, "Amplifier", sizeof(info->module));
            info->min_value = 0;
            info->max_value = 128;
            info->default_value = params->amp.d;
            return true;
        case SYNTH2_PARAM_ID_AMP_S:
            info->id = param_index;
            info->flags = 0;
            strncpy(info->name, "S", sizeof(info->name));
            strncpy(info->module, "Amplifier", sizeof(info->module));
            info->min_value = 0;
            info->max_value = 128;
            info->default_value = params->amp.s;
            return true;
        case SYNTH2_PARAM_ID_AMP_R:
            info->id = param_index;
            info->flags = 0;
            strncpy(info->name, "R", sizeof(info->name));
            strncpy(info->module, "Amplifier", sizeof(info->module));
            info->min_value = 0;
            info->max_value = 128;
            info->default_value = 0;
            info->default_value = params->amp.r;
            return true;
        case SYNTH2_PARAM_ID_AMP_GAIN:
            info->id = param_index;
            info->flags = 0;
            strncpy(info->name, "Gain", sizeof(info->name));
            strncpy(info->module, "Amplifier", sizeof(info->module));
            info->min_value = 0;
            info->max_value = 128;
            info->default_value = params->amp.gain;
            return true;
        case SYNTH2_PARAM_ID_FILTER_TYPE:
            info->id = param_index;
            info->flags = CLAP_PARAM_IS_ENUM | CLAP_PARAM_IS_STEPPED;
            strncpy(info->name, "Type", sizeof(info->name));
            strncpy(info->module, "Filter", sizeof(info->module));
            info->min_value = SYNTH2_FILTER_MIN;
            info->max_value = SYNTH2_FILTER_MAX;
            info->default_value = params->filter.type;
            return true;
        case SYNTH2_PARAM_ID_FILTER_A:
            info->id = param_index;
            info->flags = 0;
            strncpy(info->name, "A", sizeof(info->name));
            strncpy(info->module, "Filter", sizeof(info->module));
            info->min_value = 0;
            info->max_value = 128;
            info->default_value = params->filter.a;
            return true;
        case SYNTH2_PARAM_ID_FILTER_D:
            info->id = param_index;
            info->flags = 0;
            strncpy(info->name, "D", sizeof(info->name));
            strncpy(info->module, "Filter", sizeof(info->module));
            info->min_value = 0;
            info->max_value = 128;
            info->default_value = params->filter.d;
            return true;
        case SYNTH2_PARAM_ID_FILTER_S:
            info->id = param_index;
            info->flags = 0;
            strncpy(info->name, "S", sizeof(info->name));
            strncpy(info->module, "Filter", sizeof(info->module));
            info->min_value = 0;
            info->max_value = 128;
            info->default_value = params->filter.s;
            return true;
        case SYNTH2_PARAM_ID_FILTER_R:
            info->id = param_index;
            info->flags = 0;
            strncpy(info->name, "R", sizeof(info->name));
            strncpy(info->module, "Filter", sizeof(info->module));
            info->min_value = 0;
            info->max_value = 128;
            info->default_value = params->filter.r;
            return true;
        case SYNTH2_PARAM_ID_FILTER_AMT:
            info->id = param_index;
            info->flags = 0;
            strncpy(info->name, "Amt", sizeof(info->name));
            strncpy(info->module, "Filter", sizeof(info->module));
            info->min_value = -64;
            info->max_value = 64;
            info->default_value = params->filter.amt;
            return true;
        case SYNTH2_PARAM_ID_FILTER_FREQ:
            info->id = param_index;
            info->flags = 0;
            strncpy(info->name, "Freq", sizeof(info->name));
            strncpy(info->module, "Filter", sizeof(info->module));
            info->min_value = 0;
            info->max_value = 128;
            info->default_value = params->filter.freq;
            return true;
        case SYNTH2_PARAM_ID_FILTER_RES:
            info->id = param_index;
            info->flags = 0;
            strncpy(info->name, "Res", sizeof(info->name));
            strncpy(info->module, "Filter", sizeof(info->module));
            info->min_value = 0;
            info->max_value = 128;
            info->default_value = params->filter.res;
            return true;
        case SYNTH2_PARAM_ID_UNISON_SIZE:
            info->id = param_index;
            info->flags = 0;
            strncpy(info->name, "Size", sizeof(info->name));
            strncpy(info->module, "Unison", sizeof(info->module));
            info->min_value = 1;
            info->max_value = 6;
            info->default_value = params->unison.size;
            return true;
        case SYNTH2_PARAM_ID_UNISON_DEPTH:
            info->id = param_index;
            info->flags = 0;
            strncpy(info->name, "Depth", sizeof(info->name));
            strncpy(info->module, "Unison", sizeof(info->module));
            info->min_value = 0;
            info->max_value = 128;
            info->default_value = params->unison.depth;
            return true;
        case SYNTH2_PARAM_ID_CTRL_VOLUME:
            info->id = param_index;
            info->flags = 0;
            strncpy(info->name, "Volume", sizeof(info->name));
            strncpy(info->module, "Contorl", sizeof(info->module));
            info->min_value = 0;
            info->max_value = 128;
            info->default_value = params->ctrl.volume;
            return true;
        default:
            return false;
    }
}

bool synth2_params_get_value(
    const synth2_params_t *params,
    synth2_param_id_t param_id,
    double *out_value
) {
    switch (param_id) {
        case SYNTH2_PARAM_ID_OSC1_WAVE:
            *out_value = params->osc1.wave;
            return true;
        case SYNTH2_PARAM_ID_OSC1_DUTY:
            *out_value = params->osc1.duty;
            return true;
        case SYNTH2_PARAM_ID_OSC1_PITCH:
            *out_value = params->osc1.pitch;
            return true;
        case SYNTH2_PARAM_ID_OSC1_CENT:
            *out_value = params->osc1.cent;
            return true;
        case SYNTH2_PARAM_ID_OSC1_TRACK:
            *out_value = params->osc1.track;
            return true;
        case SYNTH2_PARAM_ID_OSC2_WAVE:
            *out_value = params->osc2.wave;
            return true;
        case SYNTH2_PARAM_ID_OSC2_DUTY:
            *out_value = params->osc2.duty;
            return true;
        case SYNTH2_PARAM_ID_OSC2_PITCH:
            *out_value = params->osc2.pitch;
            return true;
        case SYNTH2_PARAM_ID_OSC2_CENT:
            *out_value = params->osc2.cent;
            return true;
        case SYNTH2_PARAM_ID_OSC2_TRACK:
            *out_value = params->osc2.track;
            return true;
        case SYNTH2_PARAM_ID_OSCS_MIX:
            *out_value = params->oscs.mix;
            return true;
        case SYNTH2_PARAM_ID_OSCS_PHASE:
            *out_value = params->oscs.phase;
            return true;
        case SYNTH2_PARAM_ID_MOD_TYPE:
            *out_value = params->mod.type;
            return true;
        case SYNTH2_PARAM_ID_MOD_A:
            *out_value = params->mod.a;
            return true;
        case SYNTH2_PARAM_ID_MOD_D:
            *out_value = params->mod.d;
            return true;
        case SYNTH2_PARAM_ID_MOD_S:
            *out_value = params->mod.s;
            return true;
        case SYNTH2_PARAM_ID_MOD_R:
            *out_value = params->mod.r;
            return true;
        case SYNTH2_PARAM_ID_MOD_AMT:
            *out_value = params->mod.amt;
            return true;
        case SYNTH2_PARAM_ID_AMP_A:
            *out_value = params->amp.a;
            return true;
        case SYNTH2_PARAM_ID_AMP_D:
            *out_value = params->amp.d;
            return true;
        case SYNTH2_PARAM_ID_AMP_S:
            *out_value = params->amp.s;
            return true;
        case SYNTH2_PARAM_ID_AMP_R:
            *out_value = params->amp.r;
            return true;
        case SYNTH2_PARAM_ID_AMP_GAIN:
            *out_value = params->amp.gain;
            return true;
        case SYNTH2_PARAM_ID_FILTER_TYPE:
            *out_value = params->filter.type;
            return true;
        case SYNTH2_PARAM_ID_FILTER_A:
            *out_value = params->filter.a;
            return true;
        case SYNTH2_PARAM_ID_FILTER_D:
            *out_value = params->filter.d;
            return true;
        case SYNTH2_PARAM_ID_FILTER_S:
            *out_value = params->filter.s;
            return true;
        case SYNTH2_PARAM_ID_FILTER_R:
            *out_value = params->filter.r;
            return true;
        case SYNTH2_PARAM_ID_FILTER_AMT:
            *out_value = params->filter.amt;
            return true;
        case SYNTH2_PARAM_ID_FILTER_FREQ:
            *out_value = params->filter.freq;
            return true;
        case SYNTH2_PARAM_ID_FILTER_RES:
            *out_value = params->filter.res;
            return true;
        case SYNTH2_PARAM_ID_UNISON_SIZE:
            *out_value = params->unison.size;
            return true;
        case SYNTH2_PARAM_ID_UNISON_DEPTH:
            *out_value = params->unison.depth;
            return true;
        case SYNTH2_PARAM_ID_CTRL_VOLUME:
            *out_value = params->ctrl.volume;
            return true;
        default:
            return false;
    }
}

bool synth2_params_value_to_text(
    synth2_param_id_t param_id,
    double value,
    char *out_buffer,
    uint32_t out_buffer_capacity
) {
    switch (param_id) {
        case SYNTH2_PARAM_ID_OSC1_WAVE:
        case SYNTH2_PARAM_ID_OSC2_WAVE:
            switch ((synth2_osc_wave_t)value) {
                case SYNTH2_OSC_WAVE_SINE:
                    strncpy(out_buffer, "Sine", out_buffer_capacity);
                    return true;
                case SYNTH2_OSC_WAVE_TRIANGLE:
                    strncpy(out_buffer, "Triangle", out_buffer_capacity);
                    return true;
                case SYNTH2_OSC_WAVE_SAW:
                    strncpy(out_buffer, "Saw", out_buffer_capacity);
                    return true;
                case SYNTH2_OSC_WAVE_SQUARE:
                    strncpy(out_buffer, "Square", out_buffer_capacity);
                    return true;
                default:
                    return false;
            }
        case SYNTH2_PARAM_ID_MOD_TYPE:
            switch ((synth2_param_mod_type_t)value) {
                case SYNTH2_PARAM_MOD_FM:
                    strncpy(out_buffer, "FM", out_buffer_capacity);
                    return true;
                case SYNTH2_PARAM_MOD_AM:
                    strncpy(out_buffer, "AM", out_buffer_capacity);
                    return true;
                default:
                    return false;
            }
        case SYNTH2_PARAM_ID_FILTER_TYPE:
            switch ((synth2_filter_type_t)value) {
                case SYNTH2_FILTER_LP:
                    strncpy(out_buffer, "LP", out_buffer_capacity);
                    return true;
                case SYNTH2_FILTER_BP:
                    strncpy(out_buffer, "BP", out_buffer_capacity);
                    return true;
                case SYNTH2_FILTER_HP:
                    strncpy(out_buffer, "HP", out_buffer_capacity);
                    return true;
                default:
                    return false;
            }
            return true;
        case SYNTH2_PARAM_ID_OSC1_TRACK:
        case SYNTH2_PARAM_ID_OSC2_TRACK:
            if ((bool)value) {
                strncpy(out_buffer, "ON", out_buffer_capacity);
            } else {
                strncpy(out_buffer, "OFF", out_buffer_capacity);
            }
            return true;
        case SYNTH2_PARAM_ID_OSC1_DUTY:
        case SYNTH2_PARAM_ID_OSC1_PITCH:
        case SYNTH2_PARAM_ID_OSC1_CENT:
        case SYNTH2_PARAM_ID_OSC2_DUTY:
        case SYNTH2_PARAM_ID_OSC2_PITCH:
        case SYNTH2_PARAM_ID_OSC2_CENT:
        case SYNTH2_PARAM_ID_OSCS_MIX:
        case SYNTH2_PARAM_ID_OSCS_PHASE:
        case SYNTH2_PARAM_ID_MOD_A:
        case SYNTH2_PARAM_ID_MOD_D:
        case SYNTH2_PARAM_ID_MOD_S:
        case SYNTH2_PARAM_ID_MOD_R:
        case SYNTH2_PARAM_ID_MOD_AMT:
        case SYNTH2_PARAM_ID_AMP_A:
        case SYNTH2_PARAM_ID_AMP_D:
        case SYNTH2_PARAM_ID_AMP_S:
        case SYNTH2_PARAM_ID_AMP_R:
        case SYNTH2_PARAM_ID_AMP_GAIN:
        case SYNTH2_PARAM_ID_FILTER_A:
        case SYNTH2_PARAM_ID_FILTER_D:
        case SYNTH2_PARAM_ID_FILTER_S:
        case SYNTH2_PARAM_ID_FILTER_R:
        case SYNTH2_PARAM_ID_FILTER_AMT:
        case SYNTH2_PARAM_ID_FILTER_FREQ:
        case SYNTH2_PARAM_ID_FILTER_RES:
        case SYNTH2_PARAM_ID_UNISON_SIZE:
        case SYNTH2_PARAM_ID_UNISON_DEPTH:
        case SYNTH2_PARAM_ID_CTRL_VOLUME:
            snprintf(out_buffer, out_buffer_capacity, "%d", (int)value);
            return true;
        default:
            return false;
    }
}

bool synth2_params_text_to_value(
    synth2_param_id_t param_id,
    const char *param_value_text,
    double *out_value
) {
    return false;
}

bool synth2_params_update(
    synth2_params_t *params,
    synth2_param_id_t param_id,
    double value
) {
    switch (param_id) {
        case SYNTH2_PARAM_ID_OSC1_WAVE:
            params->osc1.wave = value;
            return true;
        case SYNTH2_PARAM_ID_OSC1_DUTY:
            params->osc1.duty = value;
            return true;
        case SYNTH2_PARAM_ID_OSC1_PITCH:
            params->osc1.pitch = value;
            return true;
        case SYNTH2_PARAM_ID_OSC1_CENT:
            params->osc1.cent = value;
            return true;
        case SYNTH2_PARAM_ID_OSC1_TRACK:
            params->osc1.track = value;
            return true;
        case SYNTH2_PARAM_ID_OSC2_WAVE:
            params->osc2.wave = value;
            return true;
        case SYNTH2_PARAM_ID_OSC2_DUTY:
            params->osc2.duty = value;
            return true;
        case SYNTH2_PARAM_ID_OSC2_PITCH:
            params->osc2.pitch = value;
            return true;
        case SYNTH2_PARAM_ID_OSC2_CENT:
            params->osc2.cent = value;
            return true;
        case SYNTH2_PARAM_ID_OSC2_TRACK:
            params->osc2.track = value;
            return true;
        case SYNTH2_PARAM_ID_OSCS_MIX:
            params->oscs.mix = value;
            return true;
        case SYNTH2_PARAM_ID_OSCS_PHASE:
            params->oscs.phase = value;
            return true;
        case SYNTH2_PARAM_ID_MOD_TYPE:
            params->mod.type = value;
            return true;
        case SYNTH2_PARAM_ID_MOD_A:
            params->mod.a = value;
            return true;
        case SYNTH2_PARAM_ID_MOD_D:
            params->mod.d = value;
            return true;
        case SYNTH2_PARAM_ID_MOD_S:
            params->mod.s = value;
            return true;
        case SYNTH2_PARAM_ID_MOD_R:
            params->mod.r = value;
            return true;
        case SYNTH2_PARAM_ID_MOD_AMT:
            params->mod.amt = value;
            return true;
        case SYNTH2_PARAM_ID_AMP_A:
            params->amp.a = value;
            return true;
        case SYNTH2_PARAM_ID_AMP_D:
            params->amp.d = value;
            return true;
        case SYNTH2_PARAM_ID_AMP_S:
            params->amp.s = value;
            return true;
        case SYNTH2_PARAM_ID_AMP_R:
            params->amp.r = value;
            return true;
        case SYNTH2_PARAM_ID_AMP_GAIN:
            params->amp.gain = value;
            return true;
        case SYNTH2_PARAM_ID_FILTER_TYPE:
            params->filter.type = value;
            return true;
        case SYNTH2_PARAM_ID_FILTER_A:
            params->filter.a = value;
            return true;
        case SYNTH2_PARAM_ID_FILTER_D:
            params->filter.d = value;
            return true;
        case SYNTH2_PARAM_ID_FILTER_S:
            params->filter.s = value;
            return true;
        case SYNTH2_PARAM_ID_FILTER_R:
            params->filter.r = value;
            return true;
        case SYNTH2_PARAM_ID_FILTER_AMT:
            params->filter.amt = value;
            return true;
        case SYNTH2_PARAM_ID_FILTER_FREQ:
            params->filter.freq = value;
            return true;
        case SYNTH2_PARAM_ID_FILTER_RES:
            params->filter.res = value;
            return true;
        case SYNTH2_PARAM_ID_UNISON_SIZE:
            params->unison.size = value;
            return true;
        case SYNTH2_PARAM_ID_UNISON_DEPTH:
            params->unison.depth = value;
            return true;
        case SYNTH2_PARAM_ID_CTRL_VOLUME:
            params->ctrl.volume = value;
            return true;
        default:
            return false;
    }
}
