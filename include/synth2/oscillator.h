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

#ifndef SYNTH2_OSCILLATOR_H_
#define SYNTH2_OSCILLATOR_H_

#include <stdint.h>

typedef enum synth2_oscillator_method {
    SYNTH2_OSC_METHOD_NAIVE,
} synth2_oscillator_method_t;

typedef enum synth2_oscillator_wave {
    SYNTH2_OSC_WAVE_SINE,
    SYNTH2_OSC_WAVE_TRIANGLE,
    SYNTH2_OSC_WAVE_SAW,
    SYNTH2_OSC_WAVE_SQUARE,
} synth2_oscillator_wave_t;

typedef struct synth2_oscillator {
    /// Sample rate to sample a point of wave.
    double sample_rate;

    /// MIDI1 key number to generate wave.
    double freq;

    /// Phase in wave. Must be in [0, 2π).
    double phase;

    /// Duty cycle for square wave generation.
    double duty;

    /// Previously sampled value.
    double prev;

    /// Sample a point of wave, then advance phase.
    double (*sample)(struct synth2_oscillator *osc);
} synth2_oscillator_t;

/// Initialize oscillator to generates specified wave.
///
/// If type == SYNTH2_OSC_SQUARE, then duty must be specified and in [0, 1].
/// Otherwise, this parameter is just ignored.
void synth2_oscillator_init(
    synth2_oscillator_t *osc,
    synth2_oscillator_method_t method,
    synth2_oscillator_wave_t wave,
    double sample_rate,
    double freq,
    double duty
);

#endif  // SYNTH2_OSCILLATOR_H_
