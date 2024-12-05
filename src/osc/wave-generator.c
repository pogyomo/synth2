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

#include "synth2/osc/wave-generator.h"

#include <math.h>

#include "synth2/macros.h"

static double generator_sine(double phase, double duty) {
    return sin(phase);
}

static double generator_triangle(double phase, double duty) {
    const double p = phase / PI2 + 1.0 / 4.0;
    return 4.0 * fabs(p - floor(p + 1.0 / 2.0)) - 1.0;
}

static double generator_saw(double phase, double duty) {
    return (2.0 * phase / PI2) - 1.0;
}

static double generator_square(double phase, double duty) {
    return phase < PI * duty ? 1.0 : -1.0;
}

synth2_osc_wave_generator synth2_osc_wave_generator_by_wave(
    enum synth2_osc_wave wave
) {
    switch (wave) {
        case SYNTH2_OSC_SINE:
            return generator_sine;
        case SYNTH2_OSC_TRIANGLE:
            return generator_triangle;
        case SYNTH2_OSC_SAW:
            return generator_saw;
        default:  // SYNTH2_OSC_SQUARE
            return generator_square;
    }
}
