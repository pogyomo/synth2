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

#include "clap/events.h"
#include "synth2/params.h"
#include "synth2/plugin.h"
#include "synth2/plugin/process-event.h"

static uint32_t synth2_plugin_params_count(const clap_plugin_t *plugin) {
    return SYNTH2_NUM_PARAMS;
}

static bool synth2_plugin_params_get_info(
    const clap_plugin_t *plugin,
    uint32_t index,
    clap_param_info_t *info
) {
    return synth2_params_get_info(index, info);
}

static bool synth2_plugin_params_get_value(
    const clap_plugin_t *plugin,
    clap_id param_id,
    double *out_value
) {
    const synth2_plugin_t *plug = plugin->plugin_data;
    return synth2_params_get_value(&plug->params, param_id, out_value);
}

static bool synth2_plugin_params_value_to_text(
    const clap_plugin_t *plugin,
    clap_id param_id,
    double value,
    char *out_buffer,
    uint32_t out_buffer_capacity
) {
    return synth2_params_value_to_text(param_id, value, out_buffer, out_buffer_capacity);
}

static bool synth2_plugin_params_text_to_value(
    const clap_plugin_t *plugin,
    clap_id param_id,
    const char *param_value_text,
    double *out_value
) {
    return synth2_params_text_to_value(param_id, param_value_text, out_value);
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
