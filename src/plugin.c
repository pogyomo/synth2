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

#include <assert.h>
#include <clap/plugin-features.h>
#include <stdlib.h>
#include <string.h>

#include "synth2/ext/audio-ports.h"
#include "synth2/ext/note-ports.h"
#include "synth2/ext/params.h"
#include "synth2/process-event.h"
#include "synth2/render-audio.h"

static bool plugin_init(const clap_plugin_t *plugin) {
    synth2_plugin_t *plug = plugin->plugin_data;
    plug->params = synth2_params_default_value;

    synth2_random_default(&plug->random);

    plug->next_voice_id = 0;
    for (size_t i = 0; i < SYNTH2_PLUGIN_MAX_VOICES; i++) {
        synth2_voice_t *voice = &plug->voices[i];
        voice->state = SYNTH2_VOICE_UNUSED;
    }

    return true;
}

static void plugin_destroy(const clap_plugin_t *plugin) {
    synth2_plugin_t *plug = plugin->plugin_data;
    free(plug);
}

static bool plugin_activate(
    const clap_plugin_t *plugin,
    double sample_rate,
    uint32_t min_frames_count,
    uint32_t max_frames_count
) {
    synth2_plugin_t *plug = plugin->plugin_data;
    plug->sample_rate = sample_rate;
    return true;
}

static void plugin_deactivate(const clap_plugin_t *plugin) {
    return;
}

static bool plugin_start_processing(const clap_plugin_t *plugin) {
    return true;
}

static void plugin_stop_processing(const clap_plugin_t *plugin) {
    return;
}

static void plugin_reset(const clap_plugin_t *plugin) {
    return;
}

static clap_process_status plugin_process(
    const clap_plugin_t *plugin,
    const clap_process_t *process
) {
    synth2_plugin_t *plug = plugin->plugin_data;

    assert(process->audio_inputs_count == 0);
    assert(process->audio_outputs_count == 1);

    const uint32_t n_frames = process->frames_count;
    const uint32_t n_in_events = process->in_events->size(process->in_events);
    uint32_t event_index = 0;
    uint32_t next_event_frame = n_in_events > 0 ? 0 : n_frames;

    for (uint32_t i = 0; i < n_frames;) {
        while (event_index < n_in_events && next_event_frame == i) {
            const clap_event_header_t *header = process->in_events->get(
                process->in_events, event_index
            );
            if (header->time != i) {
                next_event_frame = header->time;
                break;
            }

            synth2_process_event(plug, header);
            ++event_index;

            if (event_index == n_in_events) {
                next_event_frame = n_frames;
                break;
            }
        }

        if (process->audio_outputs[0].data32) {
            float *outoutL = process->audio_outputs[0].data32[0];
            float *outoutR = process->audio_outputs[0].data32[1];
            synth2_render_audio_f(plug, i, next_event_frame, outoutL, outoutR);
        } else if (process->audio_outputs[0].data64) {
            double *outoutL = process->audio_outputs[0].data64[0];
            double *outoutR = process->audio_outputs[0].data64[1];
            synth2_render_audio_d(plug, i, next_event_frame, outoutL, outoutR);
        }

        i = next_event_frame;
    }

    for (size_t i = 0; i < SYNTH2_PLUGIN_MAX_VOICES; i++) {
        synth2_voice_t *voice = &plug->voices[i];
        if (voice->state == SYNTH2_VOICE_POST_PROCESS) {
            clap_event_note_t event;
            event.header.size = sizeof(event);
            event.header.time = 0;
            event.header.space_id = CLAP_CORE_EVENT_SPACE_ID;
            event.header.type = CLAP_EVENT_NOTE_END;
            event.header.flags = 0;
            event.key = voice->key;
            event.note_id = voice->note_id;
            event.channel = voice->channel;
            event.port_index = 0;
            process->out_events->try_push(process->out_events, &event.header);
            voice->state = SYNTH2_VOICE_UNUSED;
        };
    }

    return CLAP_PROCESS_CONTINUE;
}

static const void *plugin_get_extension(
    const clap_plugin_t *plugin,
    const char *id
) {
    if (strcmp(id, CLAP_EXT_AUDIO_PORTS) == 0) {
        return &synth2_plugin_audio_ports;
    } else if (strcmp(id, CLAP_EXT_NOTE_PORTS) == 0) {
        return &synth2_plugin_note_ports;
    } else if (strcmp(id, CLAP_EXT_PARAMS) == 0) {
        return &synth2_plugin_params;
    } else {
        return NULL;
    }
}

static void plugin_on_main_thread(const clap_plugin_t *plugin) {
    return;
}

// clang-format off
static const char *features[] = {
    CLAP_PLUGIN_FEATURE_INSTRUMENT,
    CLAP_PLUGIN_FEATURE_SYNTHESIZER,
    CLAP_PLUGIN_FEATURE_STEREO,
    NULL
};
// clang-format on

const clap_plugin_descriptor_t synth2_plugin_descriptor = {
    .clap_version = CLAP_VERSION_INIT,
    .id = "com.github.pogyomo.synth2",
    .name = "synth2",
    .vendor = "pogyomo",
    .url = "https://github.com/pogyomo/synth2",
    .manual_url = NULL,
    .support_url = NULL,
    .version = "0.1.0",
    .description = "Yet another synthesizer",
    .features = features,
};

const synth2_plugin_t *synth2_plugin_create(const clap_host_t *host) {
    synth2_plugin_t *plugin = calloc(1, sizeof(synth2_plugin_t));
    if (!plugin) return NULL;

    plugin->host = host;
    plugin->plugin.desc = &synth2_plugin_descriptor;
    plugin->plugin.plugin_data = plugin;
    plugin->plugin.init = plugin_init;
    plugin->plugin.destroy = plugin_destroy;
    plugin->plugin.activate = plugin_activate;
    plugin->plugin.deactivate = plugin_deactivate;
    plugin->plugin.start_processing = plugin_start_processing;
    plugin->plugin.stop_processing = plugin_stop_processing;
    plugin->plugin.reset = plugin_reset;
    plugin->plugin.process = plugin_process;
    plugin->plugin.get_extension = plugin_get_extension;
    plugin->plugin.on_main_thread = plugin_on_main_thread;

    return plugin;
}
