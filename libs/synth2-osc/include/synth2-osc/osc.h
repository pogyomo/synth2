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

#ifndef SYNTH2_OSC_OSC_H_
#define SYNTH2_OSC_OSC_H_

/// Wave types the oscillator can generate.
typedef enum {
    SYNTH2_OSC_WAVE_SINE = 0,
    SYNTH2_OSC_WAVE_TRIANGLE = 1,
    SYNTH2_OSC_WAVE_SAW = 2,
    SYNTH2_OSC_WAVE_SQUARE = 3,
} synth2_osc_wave_t;

/// Holds contexts for wave generation.
typedef struct synth2_osc synth2_osc_t;

/// Create new oscillator object.
synth2_osc_t* synth2_osc_create(void);

/// Freed allocated memory for oscillator.
void synth2_osc_destroy(synth2_osc_t* osc);

/// Initialize oscillator with given parameters
void synth2_osc_init(
    synth2_osc_t* osc,
    synth2_osc_wave_t wave,
    double sample_rate,
    double freq,
    double duty
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

#endif  // SYNTH2_OSC_OSC_H_
