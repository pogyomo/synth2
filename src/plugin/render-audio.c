#include "synth2/plugin/render-audio.h"

#include <math.h>

void synth2_plugin_render_audio(
    synth2_plugin_t *plugin,
    uint32_t start,
    uint32_t end,
    float *outputL,
    float *outputR
) {
    synth2_plugin_voice_t *voice = &plugin->voice;
    for (uint32_t i = start; i < end; i++) {
        float output = 0.0f;
        if (voice->holding) {
            output = sinf(voice->phase * 2.0f * 3.14159f) * 0.2f;
            voice->phase +=
                440.0f * exp2f((voice->key - 57.0f) / 12.0f) / plugin->sample_rate;
            voice->phase -= floorf(voice->phase);
        }
        outputL[i] = outputR[i] = output;
    }
}
