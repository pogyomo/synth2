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

#ifndef SYNTH2_PLUGIN_PROCESS_EVENT_H_
#define SYNTH2_PLUGIN_PROCESS_EVENT_H_

#include "synth2/plugin.h"

/// Process given event.
void synth2_plugin_process_event(
    synth2_plugin_t *plugin,
    const clap_event_header_t *event
);

#endif  // SYNTH2_PLUGIN_PROCESS_EVENT_H_
