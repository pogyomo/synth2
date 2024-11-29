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

#ifndef SYNTH2_RANDOM_H_
#define SYNTH2_RANDOM_H_

#include <stdint.h>

#define SYNTH2_RANDOM_MIN 1
#define SYNTH2_RANDOM_MAX UINT32_MAX

typedef uint32_t synth2_random_value_t;

typedef struct synth2_random {
    synth2_random_value_t x, y, z, w;
} synth2_random_t;

/// Initialize random generator with given seed.
/// Seed must be in between SYNTH2_RANDOM_MIN and SYNTH2_RANDOM_MAX.
void synth2_random_init(synth2_random_t *random, synth2_random_value_t seed);

/// Initialize random generator with default state.
void synth2_random_default(synth2_random_t *random);

/// Generate random number between SYNTH2_RANDOM_MIN and SYNTH2_RANDOM_MAX.
synth2_random_value_t synth2_random_gen(synth2_random_t *random);

#endif  // SYNTH2_RANDOM_H_
