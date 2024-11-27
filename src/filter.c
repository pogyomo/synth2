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

// These code is referenced from:
// - https://www.utsbox.com/?page_id=523
// - https://www.w3.org/TR/audio-eq-cookbook/

#include "synth2/filter.h"

#include <math.h>

#include "synth2/macros.h"

static inline double res2q(double res) {
    const double base = 1.0 / sqrt(2.0);
    return res * (4.0 - base) + base;
}

static void init_params_lp(synth2_filter_t *filter) {
    const double omega = 2.0 * PI * filter->freq / filter->sample_rate;
    const double alpha = sin(omega) / (2.0 * res2q(filter->res));
    filter->a0 = 1.0 + alpha;
    filter->a1 = -2.0 * cos(omega);
    filter->a2 = 1.0 - alpha;
    filter->b0 = (1.0 - cos(omega)) / 2.0;
    filter->b1 = 1.0 - cos(omega);
    filter->b2 = (1.0 - cos(omega)) / 2.0;
}

static void init_params_bp(synth2_filter_t *filter) {
    const double omega = 2.0 * PI * filter->freq / filter->sample_rate;
    const double alpha = sin(omega) / (2.0 * res2q(filter->res));
    filter->a0 = 1.0 + alpha;
    filter->a1 = -2.0 * cos(omega);
    filter->a2 = 1.0 - alpha;
    filter->b0 = alpha;
    filter->b1 = 0.0;
    filter->b2 = -alpha;
}

static void init_params_hp(synth2_filter_t *filter) {
    const double omega = 2.0 * PI * filter->freq / filter->sample_rate;
    const double alpha = sin(omega) / (2.0 * res2q(filter->res));
    filter->a0 = 1.0 + alpha;
    filter->a1 = -2.0 * cos(omega);
    filter->a2 = 1.0 - alpha;
    filter->b0 = (1.0 + cos(omega)) / 2.0;
    filter->b1 = -(1.0 + cos(omega));
    filter->b2 = (1.0 + cos(omega)) / 2.0;
}

void synth2_filter_init(
    synth2_filter_t *filter,
    synth2_filter_type_t type,
    double sample_rate,
    double freq,
    double res
) {
    filter->type = type;
    filter->sample_rate = sample_rate;
    filter->freq = freq;
    filter->res = res;
    filter->in1 = filter->out1 = 0.0;
    filter->in2 = filter->out2 = 0.0;
    switch (type) {
        case SYNTH2_FILTER_LP:
            init_params_lp(filter);
            break;
        case SYNTH2_FILTER_BP:
            init_params_bp(filter);
            break;
        default:  // SYNTH2_FILTER_HP
            init_params_hp(filter);
            break;
    }
}

double synth2_filter_process(synth2_filter_t *filter, double signal) {
    const double n1 = filter->b0 / filter->a0 * signal;
    const double n2 = filter->b1 / filter->a0 * filter->in1;
    const double n3 = filter->b2 / filter->a0 * filter->in2;
    const double n4 = filter->a1 / filter->a0 * filter->out1;
    const double n5 = filter->a2 / filter->a0 * filter->out2;
    const double output = n1 + n2 + n3 - n4 - n5;
    filter->in2 = filter->in1;
    filter->in1 = signal;
    filter->out2 = filter->out1;
    filter->out1 = output;
    return output;
}

void synth2_filter_set_freq(synth2_filter_t *filter, double freq) {
    filter->freq = freq;
    switch (filter->type) {
        case SYNTH2_FILTER_LP:
            init_params_lp(filter);
            break;
        case SYNTH2_FILTER_BP:
            init_params_bp(filter);
            break;
        default:  // SYNTH2_FILTER_HP
            init_params_hp(filter);
            break;
    }
}
