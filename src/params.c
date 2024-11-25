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
    {SYNTH2_OSC_WAVE_SINE, 128},
    {SYNTH2_OSC_WAVE_SINE, 128, 0, 0},
    {64},
    {0, 0, 128, 0, 64},
};

bool synth2_params_get_info(uint32_t param_index, clap_param_info_t *info) {
    const synth2_params_t *params = &synth2_params_default_value;
    switch ((synth2_param_id_t)param_index) {
        case SYNTH2_PARAM_ID_OSC1_WAVE:
            info->id = param_index;
            info->flags = CLAP_PARAM_IS_ENUM | CLAP_PARAM_IS_STEPPED;
            strncpy(info->name, "Wave", sizeof(info->name));
            strncpy(info->module, "Oscillator1", sizeof(info->module));
            info->min_value = SYNTH2_OSC_WAVE_SINE;
            info->max_value = SYNTH2_OSC_WAVE_SQUARE;
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
        case SYNTH2_PARAM_ID_OSC2_WAVE:
            info->id = param_index;
            info->flags = CLAP_PARAM_IS_ENUM | CLAP_PARAM_IS_STEPPED;
            strncpy(info->name, "Wave", sizeof(info->name));
            strncpy(info->module, "Oscillator2", sizeof(info->module));
            info->min_value = SYNTH2_OSC_WAVE_SINE;
            info->max_value = SYNTH2_OSC_WAVE_SQUARE;
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
            info->min_value = -12;
            info->max_value = 12;
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
        case SYNTH2_PARAM_ID_OSCS_MIX:
            info->id = param_index;
            info->flags = 0;
            strncpy(info->name, "Mix", sizeof(info->name));
            strncpy(info->module, "Oscillators", sizeof(info->module));
            info->min_value = 0;
            info->max_value = 128;
            info->default_value = params->oscs.mix;
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
        case SYNTH2_PARAM_ID_OSCS_MIX:
            *out_value = params->oscs.mix;
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
                default:  // SYNTH2_OSC_WAVE_SQUARE:
                    strncpy(out_buffer, "Square", out_buffer_capacity);
                    return true;
            }
        case SYNTH2_PARAM_ID_OSC1_DUTY:
        case SYNTH2_PARAM_ID_OSC2_DUTY:
        case SYNTH2_PARAM_ID_OSC2_PITCH:
        case SYNTH2_PARAM_ID_OSC2_CENT:
        case SYNTH2_PARAM_ID_OSCS_MIX:
        case SYNTH2_PARAM_ID_AMP_A:
        case SYNTH2_PARAM_ID_AMP_D:
        case SYNTH2_PARAM_ID_AMP_S:
        case SYNTH2_PARAM_ID_AMP_R:
        case SYNTH2_PARAM_ID_AMP_GAIN:
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
        case SYNTH2_PARAM_ID_OSCS_MIX:
            params->oscs.mix = value;
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
        default:
            return false;
    }
}
