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

#include "synth2-adsr/adsr.h"

#include <assert.h>

static inline double clamp01(double value) {
    if (value < 0.0) {
        return 0.0;
    } else if (value > 1.0) {
        return 1.0;
    } else {
        return value;
    }
}

static void prepare_a(synth2_adsr_t* adsr) {
    adsr->t = 0.0;
    adsr->dt = 1.0 / adsr->a;
    adsr->curr = 0.0;
    adsr->state = SYNTH2_ADSR_STATE_A;
}

static void prepare_d(synth2_adsr_t* adsr) {
    adsr->t = 0.0;
    adsr->dt = (1.0 - adsr->s) / adsr->d;
    adsr->curr = 1.0;
    adsr->state = SYNTH2_ADSR_STATE_D;
}

static void prepare_s(synth2_adsr_t* adsr) {
    adsr->t = 0.0;
    adsr->dt = 0.0;
    adsr->curr = adsr->s;
    adsr->state = SYNTH2_ADSR_STATE_S;
}

static void prepare_r(synth2_adsr_t* adsr) {
    adsr->t = 0.0;
    adsr->dt = adsr->curr / adsr->r;
    adsr->state = SYNTH2_ADSR_STATE_R;
}

static void prepare_stop(synth2_adsr_t* adsr) {
    adsr->t = 0.0;
    adsr->dt = 0.0;
    adsr->curr = 0.0;
    adsr->state = SYNTH2_ADSR_STATE_STOP;
}

static void process_a(synth2_adsr_t* adsr) {
    adsr->curr = clamp01(adsr->curr + adsr->dt / adsr->sample_rate);
    adsr->t += 1.0 / adsr->sample_rate;
    if (adsr->t > adsr->a) prepare_d(adsr);
}

static void process_d(synth2_adsr_t* adsr) {
    adsr->curr = clamp01(adsr->curr - adsr->dt / adsr->sample_rate);
    adsr->t += 1.0 / adsr->sample_rate;
    if (adsr->t > adsr->d) prepare_s(adsr);
}

static void process_r(synth2_adsr_t* adsr) {
    adsr->curr = clamp01(adsr->curr - adsr->dt / adsr->sample_rate);
    adsr->t += 1.0 / adsr->sample_rate;
    if (adsr->t > adsr->r) prepare_stop(adsr);
}

static void init_state(synth2_adsr_t* adsr) {
    if (adsr->a < 1e-10) {
        if (adsr->d < 1e-10) {
            prepare_s(adsr);
        } else {
            prepare_d(adsr);
        }
    } else {
        prepare_a(adsr);
    }
}

void synth2_adsr_init(
    synth2_adsr_t* adsr,
    double sample_rate,
    double a,
    double d,
    double s,
    double r
) {
    assert(0.0 <= s && s <= 1.0);
    adsr->sample_rate = sample_rate;
    adsr->a = a;
    adsr->d = d;
    adsr->s = s;
    adsr->r = r;
    init_state(adsr);
}

void synth2_adsr_keyoff(synth2_adsr_t* adsr) {
    if (adsr->r < 1e-10) {
        prepare_stop(adsr);
    } else {
        prepare_r(adsr);
    }
}

synth2_adsr_state_t synth2_adsr_current_state(const synth2_adsr_t* adsr) {
    return adsr->state;
}

double synth2_adsr_sample(synth2_adsr_t* adsr) {
    const double result = adsr->curr;
    switch (adsr->state) {
        case SYNTH2_ADSR_STATE_A:
            process_a(adsr);
            break;
        case SYNTH2_ADSR_STATE_D:
            process_d(adsr);
            break;
        case SYNTH2_ADSR_STATE_S:
            // Wait until synth2_adsr_keyoff called.
            break;
        case SYNTH2_ADSR_STATE_R:
            process_r(adsr);
            break;
        default:  // SYNTH2_ADSR_STOP
            return 0.0;
    }
    return result;
}

void synth2_adsr_set_a(synth2_adsr_t* adsr, double a) {
    adsr->a = a;
}

double synth2_adsr_get_a(const synth2_adsr_t* adsr) {
    return adsr->a;
}

void synth2_adsr_set_d(synth2_adsr_t* adsr, double d) {
    adsr->d = d;
}

double synth2_adsr_get_d(const synth2_adsr_t* adsr) {
    return adsr->d;
}

void synth2_adsr_set_s(synth2_adsr_t* adsr, double s) {
    adsr->s = s;
}

double synth2_adsr_get_s(const synth2_adsr_t* adsr) {
    return adsr->s;
}

void synth2_adsr_set_r(synth2_adsr_t* adsr, double r) {
    adsr->r = r;
}

double synth2_adsr_get_r(const synth2_adsr_t* adsr) {
    return adsr->r;
}
