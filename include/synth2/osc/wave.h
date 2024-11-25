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

#ifndef SYNTH2_OSC_WAVE_H_
#define SYNTH2_OSC_WAVE_H_

/// Wave types the oscillator can generate.
typedef enum {
    SYNTH2_OSC_WAVE_SINE,
    SYNTH2_OSC_WAVE_TRIANGLE,
    SYNTH2_OSC_WAVE_SAW,
    SYNTH2_OSC_WAVE_SQUARE,
    SYNTH2_OSC_WAVE_MIN = SYNTH2_OSC_WAVE_SINE,
    SYNTH2_OSC_WAVE_MAX = SYNTH2_OSC_WAVE_SQUARE,
} synth2_osc_wave_t;

#endif  // SYNTH2_OSC_WAVE_H_
