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

#ifndef SYNTH2_VOICE_H_
#define SYNTH2_VOICE_H_

#include <stdint.h>

enum synth2_voice_state {
    SYNTH2_VOICE_UNUSED,
    SYNTH2_VOICE_HOLD,
    SYNTH2_VOICE_RELEASE,
    SYNTH2_VOICE_FINISH,
};

struct synth2_voice {
    enum synth2_voice_state state;
};

/// Initialize given voice so it become ready to use.
void synth2_voice_init(struct synth2_voice *this);

/// Render voice.
double synth2_voice_render(struct synth2_voice *this);

#endif  // SYNTH2_VOICE_H_
