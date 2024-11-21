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

#include "synth2/plugin/render-audio.h"

void synth2_plugin_render_audio(
    synth2_plugin_t *plugin,
    uint32_t start,
    uint32_t end,
    float *outputL,
    float *outputR
) {
    for (uint32_t i = start; i < end; i++) {
        float output = 0.0f;
        for (size_t i = 0; i < SYNTH2_PLUGIN_MAX_VOICES; i++) {
            synth2_plugin_voice_t *voice = &plugin->voices[i];
            if (voice->state == SYNTH2_PLUGIN_VOICE_HOLDING) {
                output += voice->osc.sample(&voice->osc) * 0.2;
            } else if (voice->state == SYNTH2_PLUGIN_VOICE_RELEASE) {
                // TODO: It maybe good to add short decay for preventing clipping noise.

                // Currently we immediately stops sound and goto post process.
                voice->state = SYNTH2_PLUGIN_VOICE_POST_PROCESS;
            }
        }
        outputL[i] = outputR[i] = output;
    }
}
