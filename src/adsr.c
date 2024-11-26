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

#include "synth2/adsr.h"

#include <assert.h>

static inline double physical_time(const synth2_adsr_t* adsr) {
    return (double)adsr->t / adsr->sample_rate;
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
    adsr->t = 0;
    adsr->keyoff = false;
}

void synth2_adsr_keyoff(synth2_adsr_t* adsr) {
    if (adsr->keyoff) return;
    adsr->t = 0;
    adsr->keyoff = true;
}

synth2_adsr_stage_t synth2_adsr_current_stage(const synth2_adsr_t* adsr) {
    const double t = physical_time(adsr);
    if (!adsr->keyoff) {
        if (t < adsr->a) {
            return SYNTH2_ADSR_STAGE_A;
        } else if (t < adsr->a + adsr->d) {
            return SYNTH2_ADSR_STAGE_D;
        } else {
            return SYNTH2_ADSR_STAGE_S;
        }
    } else {
        if (t < adsr->r) {
            return SYNTH2_ADSR_STAGE_R;
        } else {
            return SYNTH2_ADSR_STAGE_END;
        }
    }
}

double synth2_adsr_sample(synth2_adsr_t* adsr) {
    const double t = physical_time(adsr);
    adsr->t++;

    if (!adsr->keyoff) {
        if (t < adsr->a) {
            return (1.0 / adsr->a) * t;
        } else if (t < adsr->a + adsr->d) {
            return 1.0 - ((1.0 - adsr->s) / adsr->d) * (t - adsr->a);
        } else {
            return adsr->s;
        }
    } else {
        if (t < adsr->r) {
            return adsr->s - (adsr->s / adsr->r) * t;
        } else {
            return 0.0;
        }
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
