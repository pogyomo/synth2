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

#ifndef SYNTH2_PARAMS_H_
#define SYNTH2_PARAMS_H_

#include <stdint.h>

#include "clap/ext/params.h"
#include "synth2-osc/osc.h"

#define SYNTH2_NUM_PARAMS 12

/// ID for each parameters.
typedef enum synth2_param_id {
    SYNTH2_PARAM_ID_OSC1_WAVE = 0,
    SYNTH2_PARAM_ID_OSC1_DUTY,
    SYNTH2_PARAM_ID_OSC2_WAVE,
    SYNTH2_PARAM_ID_OSC2_DUTY,
    SYNTH2_PARAM_ID_OSC2_PITCH,
    SYNTH2_PARAM_ID_OSC2_CENT,
    SYNTH2_PARAM_ID_OSCS_MIX,
    SYNTH2_PARAM_ID_AMP_A,
    SYNTH2_PARAM_ID_AMP_D,
    SYNTH2_PARAM_ID_AMP_S,
    SYNTH2_PARAM_ID_AMP_R,
    SYNTH2_PARAM_ID_AMP_GAIN,
} synth2_param_id_t;

typedef struct synth2_params_osc1 {
    synth2_osc_wave_t wave;
    uint8_t duty;  // 0..=128
} synth2_params_osc1_t;

typedef struct synth2_params_osc2 {
    synth2_osc_wave_t wave;
    uint8_t duty;  // 0..=128
    int8_t pitch;  // -12..=12
    int8_t cent;   // -64..=64
} synth2_params_osc2_t;

typedef struct synth2_params_oscs {
    uint8_t mix;  // 0..=128
} synth2_params_oscs_t;

typedef struct synth2_params_amp {
    uint8_t a, d, s, r;  // 0..=128
    uint8_t gain;        // 0..=128
} synth2_params_amp_t;

typedef struct synth2_params {
    synth2_params_osc1_t osc1;
    synth2_params_osc2_t osc2;
    synth2_params_oscs_t oscs;
    synth2_params_amp_t amp;
} synth2_params_t;

bool synth2_params_get_info(
    const synth2_params_t *params,
    uint32_t param_index,
    clap_param_info_t *info
);

bool synth2_params_get_value(
    const synth2_params_t *params,
    synth2_param_id_t param_id,
    double *out_value
);

bool synth2_params_value_to_text(
    const synth2_params_t *params,
    synth2_param_id_t param_id,
    double value,
    char *out_buffer,
    uint32_t out_buffer_capacity
);

bool synth2_params_text_to_value(
    const synth2_params_t *params,
    synth2_param_id_t param_id,
    const char *param_value_text,
    double *out_value
);

bool synth2_params_update(
    synth2_params_t *params,
    synth2_param_id_t param_id,
    double value
);

#endif  // SYNTH2_PARAMS_H_
