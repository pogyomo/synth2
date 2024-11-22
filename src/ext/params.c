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

#include "synth2/ext/params.h"

#include <string.h>

#include "clap/events.h"
#include "synth2/plugin.h"
#include "synth2/plugin/process-event.h"

static uint32_t synth2_plugin_params_count(const clap_plugin_t *plugin) {
    return 1;
}

static bool synth2_plugin_params_get_info(
    const clap_plugin_t *plugin,
    uint32_t index,
    clap_param_info_t *info
) {
    if (index > 0) return false;
    info->id = 0;
    info->flags = CLAP_PARAM_IS_ENUM | CLAP_PARAM_IS_STEPPED;
    info->cookie = NULL;
    strncpy(info->name, "Wave", sizeof(info->name));
    strncpy(info->module, "Oscillator", sizeof(info->module));
    info->min_value = 0;
    info->max_value = 3;
    info->default_value = 0;
    return true;
}

static bool synth2_plugin_params_get_value(
    const clap_plugin_t *plugin,
    clap_id param_id,
    double *out_value
) {
    const synth2_plugin_t *plug = plugin->plugin_data;
    if (param_id > 0) return false;
    *out_value = (double)plug->osc_wave;
    return true;
}

static bool synth2_plugin_params_value_to_text(
    const clap_plugin_t *plugin,
    clap_id param_id,
    double value,
    char *out_buffer,
    uint32_t out_buffer_capacity
) {
    synth2_osc_wave_t wave = (synth2_osc_wave_t)value;
    if (wave == SYNTH2_OSC_WAVE_SINE) {
        strncpy(out_buffer, "sine", out_buffer_capacity);
    } else if (wave == SYNTH2_OSC_WAVE_TRIANGLE) {
        strncpy(out_buffer, "triangle", out_buffer_capacity);
    } else if (wave == SYNTH2_OSC_WAVE_SAW) {
        strncpy(out_buffer, "saw", out_buffer_capacity);
    } else {
        strncpy(out_buffer, "square", out_buffer_capacity);
    }
    return true;
}

static bool synth2_plugin_params_text_to_value(
    const clap_plugin_t *plugin,
    clap_id param_id,
    const char *param_value_text,
    double *out_value
) {
    return false;
}

static void synth2_plugin_params_flush(
    const clap_plugin_t *plugin,
    const clap_input_events_t *in,
    const clap_output_events_t *out
) {
    uint32_t in_size = in->size(in);
    for (uint32_t i = 0; i < in_size; i++) {
        const clap_event_header_t *event = in->get(in, i);
        synth2_plugin_process_event(plugin->plugin_data, event);
    }
    return;
}

const clap_plugin_params_t synth2_plugin_params = {
    .count = synth2_plugin_params_count,
    .get_info = synth2_plugin_params_get_info,
    .get_value = synth2_plugin_params_get_value,
    .value_to_text = synth2_plugin_params_value_to_text,
    .text_to_value = synth2_plugin_params_text_to_value,
    .flush = synth2_plugin_params_flush,
};
