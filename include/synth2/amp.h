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

#ifndef SYNTH2_AMP_H_
#define SYNTH2_AMP_H_

#include "adsr.h"

struct synth2_amp {
    struct synth2_adsr adsr;
    double level;
};

/// Initialize amplifier.
/// level must be in [[0, 1]].
void synth2_amp_init(
    struct synth2_amp *this,
    struct synth2_adsr adsr,
    double level
);

/// Release internal adsr.
void synth2_amp_release(struct synth2_amp *this);

/// Amplify signal.
double synth2_amp_process(struct synth2_amp *this, double signal);

#endif  // SYNTH2_AMP_H_
