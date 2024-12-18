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

#ifndef SYNTH2_RENDER_AUDIO_H_
#define SYNTH2_RENDER_AUDIO_H_

#include "synth2/plugin.h"

/// Rendering preprocessed audio to buffer of type float.
void synth2_render_audio_f(
    synth2_plugin_t *plugin,
    uint32_t start,
    uint32_t end,
    float *outputL,
    float *outputR
);

/// Rendering preprocessed audio to buffer of type double.
void synth2_render_audio_d(
    synth2_plugin_t *plugin,
    uint32_t start,
    uint32_t end,
    double *outputL,
    double *outputR
);

#endif  // SYNTH2_RENDER_AUDIO_H_
