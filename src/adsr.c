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

/// Convert [[0, 1]] normalized time into physical time.
static inline double t2p(double t) {
    return t * 2.0 + 0.005;
}

/// Convert logical elapsed time into physical time.
static inline double l2p(double sample_rate, uint64_t t) {
    return (double)t / sample_rate;
}

void synth2_adsr_init(
    struct synth2_adsr* this,
    double sample_rate,
    double a,
    double d,
    double s,
    double r
) {
    assert(0.0 <= a && a <= 1.0);
    assert(0.0 <= d && d <= 1.0);
    assert(0.0 <= s && s <= 1.0);
    assert(0.0 <= r && r <= 1.0);
    this->sample_rate = sample_rate;
    this->a = t2p(a);
    this->d = t2p(d);
    this->s = s;
    this->r = t2p(r);
    this->top = 0.0;
    this->t = 0;
    this->keyon = true;
}

enum synth2_adsr_stage synth2_adsr_stage(const struct synth2_adsr* this) {
    const double t = l2p(this->sample_rate, this->t);
    if (this->keyon) {
        if (t < this->a) {
            return SYNTH2_ADSR_STAGE_A;
        } else if (t < this->a + this->d) {
            return SYNTH2_ADSR_STAGE_D;
        } else {
            return SYNTH2_ADSR_STAGE_S;
        }
    } else {
        if (t < this->r) {
            return SYNTH2_ADSR_STAGE_R;
        } else {
            return SYNTH2_ADSR_STAGE_END;
        }
    }
}

void synth2_adsr_keyoff(struct synth2_adsr* this) {
    if (!this->keyon) return;
    this->t = 0;
    this->keyon = false;
}

static double sample_keyon(struct synth2_adsr* this) {
    const double t = l2p(this->sample_rate, this->t++);
    if (t < this->a) {
        return this->top = (1.0 / this->a) * t;
    } else if (t < this->a + this->d) {
        return this->top = 1.0 - ((1.0 - this->s) / this->d) * (t - this->a);
    } else {
        return this->top = this->s;
    }
}

static double sample_keyoff(struct synth2_adsr* this) {
    const double t = l2p(this->sample_rate, this->t++);
    if (t < this->r) {
        return this->top - (this->top / this->r) * t;
    } else {
        return 0.0;
    }
}

double synth2_adsr_sample(struct synth2_adsr* this) {
    if (this->keyon) {
        return sample_keyon(this);
    } else {
        return sample_keyoff(this);
    }
}
