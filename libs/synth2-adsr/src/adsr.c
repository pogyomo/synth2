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

#include "synth2-adsr/internal/adsr.h"

#include <assert.h>
#include <stdlib.h>

#include "synth2-adsr/adsr.h"

static inline double clamp01(double value) {
    if (value < 0.0) {
        return 0.0;
    } else if (value > 1.0) {
        return 1.0;
    } else {
        return value;
    }
}

static double process_a(synth2_adsr_t* adsr) {
    const double d = 1.0 / adsr->a;
    adsr->curr = clamp01(adsr->prev + d / adsr->sample_rate);
    adsr->t += 1.0 / adsr->sample_rate;
    if (adsr->t >= adsr->a) {
        adsr->t = 0.0;
        adsr->state = SYNTH2_ADSR_STATE_D;
    }
    return adsr->prev;
}

static double process_d(synth2_adsr_t* adsr) {
    const double d = (adsr->curr - adsr->s) / (adsr->d - adsr->t);
    adsr->curr = clamp01(adsr->prev - d / adsr->sample_rate);
    adsr->t += 1.0 / adsr->sample_rate;
    if (adsr->t >= adsr->d) {
        adsr->t = 0.0;
        adsr->state = SYNTH2_ADSR_STATE_S;
    }
    return adsr->prev;
}

static double process_s(synth2_adsr_t* adsr) {
    return adsr->prev;
}

static double process_r(synth2_adsr_t* adsr) {
    const double d = adsr->prev / (adsr->r - adsr->t);
    adsr->curr = clamp01(adsr->prev - d / adsr->sample_rate);
    adsr->t += 1.0 / adsr->sample_rate;
    return adsr->prev;
}

synth2_adsr_t*
synth2_adsr_create(double sample_rate, double a, double d, double s, double r) {
    assert(0.0 <= s && s <= 1.0);
    synth2_adsr_t* adsr = calloc(1, sizeof(synth2_adsr_t));
    if (!adsr) return NULL;
    adsr->sample_rate = sample_rate;
    adsr->a = a;
    adsr->d = d;
    adsr->s = s;
    adsr->r = r;
    adsr->t = 0.0;
    adsr->curr = adsr->prev = 0.0;
    adsr->state = SYNTH2_ADSR_STATE_A;
    return adsr;
}

void synth2_adsr_destroy(synth2_adsr_t* adsr) {
    free(adsr);
}

synth2_adsr_state_t synth2_adsr_current_state(const synth2_adsr_t* adsr) {
    return adsr->state;
}

void synth2_adsr_keyon(synth2_adsr_t* adsr) {
    adsr->t = 0.0;
    adsr->curr = adsr->prev = 0.0;
    adsr->state = SYNTH2_ADSR_STATE_A;
}

void synth2_adsr_keyoff(synth2_adsr_t* adsr) {
    adsr->t = 0.0;
    adsr->state = SYNTH2_ADSR_STATE_R;
}

double synth2_adsr_sample(synth2_adsr_t* adsr) {
    adsr->prev = adsr->curr;
    switch (adsr->state) {
        case SYNTH2_ADSR_STATE_A:
            return process_a(adsr);
        case SYNTH2_ADSR_STATE_D:
            return process_d(adsr);
        case SYNTH2_ADSR_STATE_S:
            return process_s(adsr);
        case SYNTH2_ADSR_STATE_R:
            return process_r(adsr);
        default:  // SYNTH2_ADSR_STOP
            return 0.0;
    }
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
