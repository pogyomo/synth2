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

void synth2_random_init(struct synth2_random *this, uint32_t seed) {
    assert(SYNTH2_RANDOM_MIN <= seed && seed <= SYNTH2_RANDOM_MAX);
    this->x = 123456789;
    this->y = 362436069;
    this->z = 521288629;
    this->w = seed;
}

void synth2_random_default(struct synth2_random *this) {
    synth2_random_init(this, 88675123);
}

uint32_t synth2_random_gen(struct synth2_random *this) {
    // use xorshift128 algorithm
    const uint32_t x = this->x;
    const uint32_t w = this->w;
    const uint32_t t = x ^ (x << 11);
    this->x = this->y;
    this->y = this->z;
    this->z = this->w;
    return this->w = (w ^ (w >> 19)) ^ (t ^ (t >> 8));
}
