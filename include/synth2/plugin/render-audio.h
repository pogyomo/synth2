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

#ifndef SYNTH2_PLUGIN_RENDER_AUDIO_H_
#define SYNTH2_PLUGIN_RENDER_AUDIO_H_

#include "synth2/plugin.h"

/// Rendering preprocessed audio.
void synth2_plugin_render_audio(
    synth2_plugin_t *plugin,
    uint32_t start,
    uint32_t end,
    float *outputL,
    float *outputR
);

#endif  // SYNTH2_PLUGIN_RENDER_AUDIO_H_
