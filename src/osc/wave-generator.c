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

#include "synth2/osc/macros.h"

static double wave_generator_sine(double x, double prev, double duty) {
    return sin(x);
}

static double wave_generator_triangle(double x, double prev, double duty) {
    const double p = x / PI2 + 1.0 / 4.0;
    return 4.0 * fabs(p - floor(p + 1.0 / 2.0)) - 1.0;
}

static double wave_generator_saw(double x, double prev, double duty) {
    return (2.0 * x / PI2) - 1.0;
}

static double wave_generator_square(double x, double prev, double duty) {
    return x < PI * duty ? 1.0 : -1.0;
}

synth2_osc_wave_generator synth2_osc_get_wave_generator(synth2_osc_wave_t wave) {
    switch (wave) {
        case SYNTH2_OSC_WAVE_SINE:
            return wave_generator_sine;
        case SYNTH2_OSC_WAVE_TRIANGLE:
            return wave_generator_triangle;
        case SYNTH2_OSC_WAVE_SAW:
            return wave_generator_saw;
        default:  // SYNTH2_OSC_WAVE_SQUARE
            return wave_generator_square;
    }
}
