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

#include "synth2/plugin.h"

#include <clap/plugin-features.h>
#include <stdlib.h>
#include <string.h>

#include "synth2/ext/audio-ports.h"
#include "synth2/ext/note-ports.h"

static bool synth2_plugin_init(const clap_plugin_t *plugin) {
    return true;
}

static void synth2_plugin_destroy(const clap_plugin_t *plugin) {
    synth2_plugin_t *plug = plugin->plugin_data;
    free(plug);
}

static bool synth2_plugin_activate(
    const struct clap_plugin *plugin,
    double sample_rate,
    uint32_t min_frames_count,
    uint32_t max_frames_count
) {
    return true;
}

static void synth2_plugin_deactivate(const struct clap_plugin *plugin) {
    return;
}

static bool synth2_plugin_start_processing(const struct clap_plugin *plugin) {
    return true;
}

static void synth2_plugin_stop_processing(const struct clap_plugin *plugin) {
    return;
}

static void synth2_plugin_reset(const struct clap_plugin *plugin) {
    return;
}

static clap_process_status
synth2_plugin_process(const struct clap_plugin *plugin, const clap_process_t *process) {
    return CLAP_PROCESS_SLEEP;
}

static const void *
synth2_plugin_get_extension(const struct clap_plugin *plugin, const char *id) {
    if (strcmp(id, CLAP_EXT_AUDIO_PORTS) == 0) {
        return &synth2_plugin_audio_ports;
    } else if (strcmp(id, CLAP_EXT_NOTE_PORTS) == 0) {
        return &synth2_plugin_note_ports;
    } else {
        return NULL;
    }
}

static void synth2_plugin_on_main_thread(const struct clap_plugin *plugin) {
    return;
}

static const char *synth2_plugin_descriptor_features[] = {
    CLAP_PLUGIN_FEATURE_INSTRUMENT,
    CLAP_PLUGIN_FEATURE_SYNTHESIZER,
    CLAP_PLUGIN_FEATURE_STEREO,
    NULL
};

const clap_plugin_descriptor_t synth2_plugin_descriptor = {
    .clap_version = CLAP_VERSION,
    .id = "com.github.pogyomo.synth2",
    .name = "synth2",
    .vendor = "pogyomo",
    .url = "https://github.com/pogyomo/synth2",
    .manual_url = NULL,
    .support_url = NULL,
    .version = "0.1.0",
    .description = "Yet another synthesizer",
    .features = synth2_plugin_descriptor_features,
};

const clap_plugin_t *synth2_plugin_create(const clap_host_t *host) {
    synth2_plugin_t *plugin = calloc(1, sizeof(synth2_plugin_t));
    if (!plugin) return NULL;

    plugin->host = host;
    plugin->plugin.desc = &synth2_plugin_descriptor;
    plugin->plugin.plugin_data = plugin;
    plugin->plugin.init = synth2_plugin_init;
    plugin->plugin.destroy = synth2_plugin_destroy;
    plugin->plugin.activate = synth2_plugin_activate;
    plugin->plugin.deactivate = synth2_plugin_deactivate;
    plugin->plugin.start_processing = synth2_plugin_start_processing;
    plugin->plugin.stop_processing = synth2_plugin_stop_processing;
    plugin->plugin.reset = synth2_plugin_reset;
    plugin->plugin.process = synth2_plugin_process;
    plugin->plugin.get_extension = synth2_plugin_get_extension;
    plugin->plugin.on_main_thread = synth2_plugin_on_main_thread;

    return &plugin->plugin;
}
