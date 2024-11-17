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

#include <clap/entry.h>
#include <string.h>

#include "synth2/factory/plugin-factory.h"

static bool synth2_entry_init(const char *plugin_path) {
    return true;
}

static void synth2_entry_deinit(void) {
    return;
}

static const void *synth2_entry_get_factory(const char *factory_id) {
    if (strcmp(factory_id, CLAP_PLUGIN_FACTORY_ID) == 0) {
        return &synth2_plugin_factory;
    } else {
        return NULL;
    }
}

const clap_plugin_entry_t clap_entry = {
    .clap_version = CLAP_VERSION_INIT,
    .init = synth2_entry_init,
    .deinit = synth2_entry_deinit,
    .get_factory = synth2_entry_get_factory,
};
