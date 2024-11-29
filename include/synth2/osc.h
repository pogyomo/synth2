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

#ifndef SYNTH2_OSC_H_
#define SYNTH2_OSC_H_

#include "synth2/osc/wave-generator.h"
#include "synth2/osc/wave.h"

/// Holds contexts for wave generation.
typedef struct synth2_osc {
    synth2_osc_wave_t wave;
    double sample_rate, freq, duty;
    double phase, prev;
    synth2_osc_wave_generator gen;  // Synchronized with wave.
} synth2_osc_t;

/// Initialize oscillator with given parameters
/// phase must be in [0, 2π)
void synth2_osc_init(
    synth2_osc_t* osc,
    synth2_osc_wave_t wave,
    double sample_rate,
    double freq,
    double duty,
    double phase
);

/// Sample a point from generated wave, then prepare for next sample.
double synth2_osc_sample(synth2_osc_t* osc);

/// Change wave to generate.
void synth2_osc_set_wave(synth2_osc_t* osc, synth2_osc_wave_t wave);

/// Returns currently generating wave.
synth2_osc_wave_t synth2_osc_get_wave(const synth2_osc_t* osc);

/// Change frequency of wave to generate.
void synth2_osc_set_freq(synth2_osc_t* osc, double freq);

/// Returns current frequency of generating wave.
double synth2_osc_get_freq(const synth2_osc_t* osc);

/// Change duty cycle for square wave.
void synth2_osc_set_duty(synth2_osc_t* osc, double duty);

/// Returns current duty cycle.
double synth2_osc_get_duty(const synth2_osc_t* osc);

#endif  // SYNTH2_OSC_H_
