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

#include "synth2/macros.h"
#include "synth2/osc/wave-generator.h"

void synth2_osc_init(
    synth2_osc_t* osc,
    synth2_osc_wave_t wave,
    double sample_rate,
    double freq,
    double duty
) {
    osc->wave = wave;
    osc->sample_rate = sample_rate;
    osc->freq = freq;
    osc->duty = duty;
    osc->phase = 0.0;
    osc->prev = 0.0;
    osc->gen = synth2_osc_wave_generator_by_wave(wave);
}

double synth2_osc_sample(synth2_osc_t* osc) {
    osc->prev = osc->gen(osc->phase, osc->prev, osc->duty);
    osc->phase += PI2 * osc->freq / osc->sample_rate;
    if (osc->phase >= PI2) osc->phase -= PI2;
    return osc->prev;
}

void synth2_osc_set_wave(synth2_osc_t* osc, synth2_osc_wave_t wave) {
    osc->gen = synth2_osc_wave_generator_by_wave(osc->wave = wave);
}

synth2_osc_wave_t synth2_osc_get_wave(const synth2_osc_t* osc) {
    return osc->wave;
}

void synth2_osc_set_freq(synth2_osc_t* osc, double freq) {
    osc->freq = freq;
}

double synth2_osc_get_freq(const synth2_osc_t* osc) {
    return osc->freq;
}

void synth2_osc_set_duty(synth2_osc_t* osc, double duty) {
    osc->duty = duty;
}

double synth2_osc_get_duty(const synth2_osc_t* osc) {
    return osc->duty;
}
