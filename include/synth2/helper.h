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

#ifndef SYNTH2_HELPER_H_
#define SYNTH2_HELPER_H_

#include <stdint.h>

/// Convert MIDI1 key number (0..127) into frequency.
/// For cent, the equation holds: k2f(k, 100n) == k2f(k + n, 0).
double k2f(int16_t key, int16_t cent);

#endif  // SYNTH2_HELPER_H_
