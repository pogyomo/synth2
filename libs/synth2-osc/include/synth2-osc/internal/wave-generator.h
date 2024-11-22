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

#ifndef SYNTH2_OSC_INTERNAL_WAVE_GENERATOR_H_
#define SYNTH2_OSC_INTERNAL_WAVE_GENERATOR_H_

#include "synth2-osc/osc.h"

/// The wave generation function. Accept following arguments.
/// 1. phase: position in one-cycle wave. Must be in [0, 2π).
/// 2. prev:  previously sampled value.
/// 3. duty:  duty of the wave, but is maybe unused.
typedef double (*wave_generator)(double phase, double prev, double duty);

/// Returns wave_generator based on wave type.
wave_generator synth2_osc_get_wave_generator(synth2_osc_wave_t wave);

#endif  // SYNTH2_OSC_INTERNAL_WAVE_GENERATOR_H_
