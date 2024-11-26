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

#ifndef SYNTH2_FILTER_H_
#define SYNTH2_FILTER_H_

typedef enum synth2_filter_type {
    SYNTH2_FILTER_LP,
    SYNTH2_FILTER_BP,
    SYNTH2_FILTER_HP,
    SYNTH2_FILTER_MIN = SYNTH2_FILTER_LP,
    SYNTH2_FILTER_MAX = SYNTH2_FILTER_HP,
} synth2_filter_type_t;

typedef struct synth2_filter {
    double sample_rate;
    double a0, a1, a2;
    double b0, b1, b2;
    double in1, out1;
    double in2, out2;
} synth2_filter_t;

/// Initialize filter with parameters.
/// freq is in hz, and res is in [0, 1].
void synth2_filter_init(
    synth2_filter_t *filter,
    synth2_filter_type_t type,
    double sample_rate,
    double freq,
    double res
);

/// Filter given signal.
double synth2_filter_process(synth2_filter_t *filter, double signal);

#endif  // SYNTH2_FILTER_H_
