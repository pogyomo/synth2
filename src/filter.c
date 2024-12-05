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

#include <assert.h>
#include <math.h>
#include <stdint.h>

#include "synth2/helper.h"
#include "synth2/macros.h"

static inline double clamp01(double value) {
    if (value < 0.0) {
        return 0.0;
    } else if (value > 1.0) {
        return 1.0;
    } else {
        return value;
    }
}

static inline double cut2f(double cut) {
    const double scaled = cut * 127.0;  // scaled in [[0, 127]]
    const int16_t key = scaled;
    const int16_t cent = modf(scaled, &(double){0}) * 100.0;
    return k2f(key, cent);
}

static inline double res2q(double res) {
    const double base = 1.0 / sqrt(2.0);
    return res * (4.0 - base) + base;
}

static inline double calc_omega(struct synth2_filter *this) {
    return 2.0 * PI * cut2f(this->cut) / this->sample_rate;
}

static inline double calc_alpha(struct synth2_filter *this, double omega) {
    return sin(omega) / (2.0 * res2q(this->res));
}

static void update_params_lp(struct synth2_filter *this) {
    const double omega = calc_omega(this);
    const double alpha = calc_alpha(this, omega);
    this->a0 = 1.0 + alpha;
    this->a1 = -2.0 * cos(omega);
    this->a2 = 1.0 - alpha;
    this->b0 = (1.0 - cos(omega)) / 2.0;
    this->b1 = 1.0 - cos(omega);
    this->b2 = (1.0 - cos(omega)) / 2.0;
}

static void update_params_bp(struct synth2_filter *this) {
    const double omega = calc_omega(this);
    const double alpha = calc_alpha(this, omega);
    this->a0 = 1.0 + alpha;
    this->a1 = -2.0 * cos(omega);
    this->a2 = 1.0 - alpha;
    this->b0 = alpha;
    this->b1 = 0.0;
    this->b2 = -alpha;
}

static void update_params_hp(struct synth2_filter *this) {
    const double omega = calc_omega(this);
    const double alpha = calc_alpha(this, omega);
    this->a0 = 1.0 + alpha;
    this->a1 = -2.0 * cos(omega);
    this->a2 = 1.0 - alpha;
    this->b0 = (1.0 + cos(omega)) / 2.0;
    this->b1 = -(1.0 + cos(omega));
    this->b2 = (1.0 + cos(omega)) / 2.0;
}

static void update_params(struct synth2_filter *this) {
    switch (this->type) {
        case SYNTH2_FILTER_LP:
            update_params_lp(this);
            break;
        case SYNTH2_FILTER_BP:
            update_params_bp(this);
            break;
        default:  // SYNTH2_FILTER_HP
            update_params_hp(this);
            break;
    }
}

void synth2_filter_init(
    struct synth2_filter *this,
    enum synth2_filter_type type,
    double sample_rate,
    double cut,
    double res
) {
    this->type = type;
    this->sample_rate = sample_rate;
    this->cut = cut;
    this->res = res;
    this->in1 = this->out1 = 0.0;
    this->in2 = this->out2 = 0.0;
}

double synth2_filter_process(struct synth2_filter *this, double signal) {
    update_params(this);
    const double n1 = this->b0 / this->a0 * signal;
    const double n2 = this->b1 / this->a0 * this->in1;
    const double n3 = this->b2 / this->a0 * this->in2;
    const double n4 = this->a1 / this->a0 * this->out1;
    const double n5 = this->a2 / this->a0 * this->out2;
    const double output = n1 + n2 + n3 - n4 - n5;
    this->in2 = this->in1;
    this->in1 = signal;
    this->out2 = this->out1;
    this->out1 = output;
    return output;
}
