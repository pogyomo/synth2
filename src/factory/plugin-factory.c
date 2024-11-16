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

#include "synth2/factory/plugin-factory.h"

static uint32_t synth2_plugin_factory_get_plugin_count(
    const clap_plugin_factory_t *factory
) {
    return 0;
}

static const clap_plugin_descriptor_t *synth2_plugin_factory_get_plugin_descriptor(
    const clap_plugin_factory_t *factory,
    uint32_t index
) {
    return NULL;
}

static const clap_plugin_t *synth2_plugin_factory_create_plugin(
    const struct clap_plugin_factory *factory,
    const clap_host_t *host,
    const char *plugin_id
) {
    return NULL;
}

const clap_plugin_factory_t synth2_plugin_factory = {
    .get_plugin_count = synth2_plugin_factory_get_plugin_count,
    .get_plugin_descriptor = synth2_plugin_factory_get_plugin_descriptor,
    .create_plugin = synth2_plugin_factory_create_plugin,
};
