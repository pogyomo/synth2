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

/// Convert normalized times into seconds.
static inline double nt2s(double t) {
    return t * 30;
}

/// Convert logical times into seconds.
static inline double lt2pt(double fs, uint64_t t) {
    return (double)t / fs;
}

static inline enum synth2_adsr_stage stage_hold(struct synth2_adsr *this) {
    const double t = lt2pt(this->fs, this->t);
    if (t < this->a)
        return SYNTH2_ADSR_STAGE_A;
    else if (t < this->a + this->d)
        return SYNTH2_ADSR_STAGE_D;
    else
        return SYNTH2_ADSR_STAGE_S;
}

static inline enum synth2_adsr_stage stage_release(struct synth2_adsr *this) {
    const double t = lt2pt(this->fs, this->t);
    if (t < this->r)
        return SYNTH2_ADSR_STAGE_R;
    else
        return SYNTH2_ADSR_STAGE_END;
}

static inline double sample_hold(struct synth2_adsr *this) {
    const double t = lt2pt(this->fs, this->t++);
    if (t < this->a)
        return this->top = (1.0 / this->a) * t;
    else if (t < this->a + this->d)
        return this->top = 1.0 - ((1.0 - this->s) / this->d) * (t - this->a);
    else
        return this->top = this->s;
}

static inline double sample_release(struct synth2_adsr *this) {
    const double t = lt2pt(this->fs, this->t++);
    if (t < this->r)
        return this->top - (this->top / this->r) * t;
    else
        return 0.0;
}

void synth2_adsr_init(
    struct synth2_adsr *this,
    double fs,
    double a,
    double d,
    double s,
    double r
) {
    assert(0.0 <= s && s <= 1.0);
    this->fs = fs;
    this->a = a;
    this->d = d;
    this->s = s;
    this->r = r;
    this->top = 0.0;
    this->t = 0;
    this->hold = true;
}

void synth2_adsr_init_normalized(
    struct synth2_adsr *this,
    double fs,
    double a,
    double d,
    double s,
    double r
) {
    assert(0.0 <= a && a <= 1.0);
    assert(0.0 <= d && d <= 1.0);
    assert(0.0 <= r && r <= 1.0);
    synth2_adsr_init(this, fs, nt2s(a), nt2s(d), s, nt2s(r));
}

void synth2_adsr_release(struct synth2_adsr *this) {
    if (!this->hold) return;
    this->hold = false;
    this->t = 0;
}

enum synth2_adsr_stage synth2_adsr_stage(struct synth2_adsr *this) {
    if (this->hold)
        return stage_hold(this);
    else
        return stage_release(this);
}

double synth2_adsr_sample(struct synth2_adsr *this) {
    if (this->hold)
        return sample_hold(this);
    else
        return sample_release(this);
}
