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

/// This object provides functional for generate [0, 1] normalized value
/// changes through time.
typedef struct synth2_adsr synth2_adsr_t;

/// Create a new synth2_adsr_t object, return pointer to it.
/// a, d and r is in seconds, and s must be in [0, 1].
synth2_adsr_t*
synth2_adsr_create(double sample_rate, double a, double d, double s, double r);

/// Reset current state, restart from attack.
void synth2_adsr_keyon(synth2_adsr_t* adsr);

/// Change state into release.
void synth2_adsr_keyoff(synth2_adsr_t* adsr);

/// Sample value, prepear for next sample.
double synth2_adsr_sample(synth2_adsr_t* adsr);

/// Returns current attack time.
void synth2_set_a(synth2_adsr_t* adsr, double a);

/// Set attack time.
double synth2_get_a(const synth2_adsr_t* adsr);

/// Returns current decay time.
void synth2_set_d(synth2_adsr_t* adsr, double d);

/// Set decay time.
double synth2_get_d(const synth2_adsr_t* adsr);

/// Returns current sustain.
void synth2_set_s(synth2_adsr_t* adsr, double s);

/// Set sustain.
double synth2_get_s(const synth2_adsr_t* adsr);

/// Returns current release time.
void synth2_set_r(synth2_adsr_t* adsr, double r);

/// Set release time.
double synth2_get_r(const synth2_adsr_t* adsr);

#endif  // SYNTH2_ADSR_ADSR_H_
