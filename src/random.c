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

#include "synth2/random.h"

#include <assert.h>

void synth2_random_init(synth2_random_t *random, synth2_random_value_t seed) {
    assert(SYNTH2_RANDOM_MIN <= seed && seed <= SYNTH2_RANDOM_MAX);
    random->x = 123456789;
    random->y = 362436069;
    random->z = 521288629;
    random->w = seed;
}

void synth2_random_default(synth2_random_t *random) {
    synth2_random_init(random, 88675123);
}

synth2_random_value_t synth2_random_gen(synth2_random_t *random) {
    // use xorshift128 algorithm
    const synth2_random_value_t x = random->x;
    const synth2_random_value_t w = random->w;
    const synth2_random_value_t t = x ^ (x << 11);
    random->x = random->y;
    random->y = random->z;
    random->z = random->w;
    return random->w = (w ^ (w >> 19)) ^ (t ^ (t >> 8));
}
