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

#include "synth2/osc.h"

#include <assert.h>

#include "synth2/macros.h"
#include "synth2/osc/wave-generator.h"

void synth2_osc_init(
    struct synth2_osc *this,
    enum synth2_osc_wave wave,
    double sample_rate,
    double freq,
    double duty,
    double phase
) {
    this->wave = wave;
    this->sample_rate = sample_rate;
    this->freq = freq;
    this->duty = duty;
    this->phase = phase;
    this->gen = synth2_osc_wave_generator_by_wave(wave);
}

double synth2_osc_sample(struct synth2_osc *this) {
    const double out = this->gen(this->phase, this->duty);
    this->phase += PI2 * this->freq / this->sample_rate;
    if (this->phase >= PI2) this->phase -= PI2;
    return out;
}
