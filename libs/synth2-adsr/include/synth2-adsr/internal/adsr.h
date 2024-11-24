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

#ifndef SYNTH2_ADSR_INTERNAL_ADSR_H_
#define SYNTH2_ADSR_INTERNAL_ADSR_H_

#include "synth2-adsr/adsr.h"

typedef enum {
    SYNTH2_ADSR_A,
    SYNTH2_ADSR_D,
    SYNTH2_ADSR_S,
    SYNTH2_ADSR_R,
    SYNTH2_ADSR_STOP,
} synth2_adsr_state_t;

struct synth2_adsr {
    double sample_rate;
    double a, d, s, r;

    double t, curr, prev;
    synth2_adsr_state_t state;
};

#endif  // SYNTH2_ADSR_INTERNAL_ADSR_H_
