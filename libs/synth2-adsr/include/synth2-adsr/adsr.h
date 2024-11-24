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

#ifndef SYNTH2_ADSR_ADSR_H_
#define SYNTH2_ADSR_ADSR_H_

#include <stdbool.h>

typedef enum synth2_adsr_state {
    SYNTH2_ADSR_STATE_A,
    SYNTH2_ADSR_STATE_D,
    SYNTH2_ADSR_STATE_S,
    SYNTH2_ADSR_STATE_R,
    SYNTH2_ADSR_STATE_STOP,
} synth2_adsr_state_t;

/// This object provides functional for generate [0, 1] normalized value
/// changes through time.
typedef struct synth2_adsr {
    double sample_rate;
    double a, d, s, r;
    double t, curr, prev;
    synth2_adsr_state_t state;
} synth2_adsr_t;

/// Initialize this ADSR with given parameters.
/// a, d and r is in seconds, and s must be in [0, 1].
void synth2_adsr_init(
    synth2_adsr_t* adsr,
    double sample_rate,
    double a,
    double d,
    double s,
    double r
);

/// Returns current state of the adsr.
synth2_adsr_state_t synth2_adsr_current_state(const synth2_adsr_t* adsr);

/// Change state into release.
void synth2_adsr_keyoff(synth2_adsr_t* adsr);

/// Sample value, prepear for next sample.
double synth2_adsr_sample(synth2_adsr_t* adsr);

/// Returns current attack time.
void synth2_adsr_set_a(synth2_adsr_t* adsr, double a);

/// Set attack time.
double synth2_adsr_get_a(const synth2_adsr_t* adsr);

/// Returns current decay time.
void synth2_adsr_set_d(synth2_adsr_t* adsr, double d);

/// Set decay time.
double synth2_adsr_get_d(const synth2_adsr_t* adsr);

/// Returns current sustain.
void synth2_adsr_set_s(synth2_adsr_t* adsr, double s);

/// Set sustain.
double synth2_adsr_get_s(const synth2_adsr_t* adsr);

/// Returns current release time.
void synth2_adsr_set_r(synth2_adsr_t* adsr, double r);

/// Set release time.
double synth2_adsr_get_r(const synth2_adsr_t* adsr);

#endif  // SYNTH2_ADSR_ADSR_H_
