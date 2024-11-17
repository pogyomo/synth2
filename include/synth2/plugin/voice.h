#ifndef SYNTH2_PLUGIN_VOICE_H_
#define SYNTH2_PLUGIN_VOICE_H_

#include <stdbool.h>
#include <stdint.h>

/// This struct represent a ringing sounds.
typedef struct synth2_plugin_voice {
    /// True if corresponding key is being pressed.
    bool holding;

    /// The position of generation, in radian.
    float phase;

    // Derived from clap_event_note_t.
    int16_t note_id;
    int16_t channel;
    int16_t key;
} synth2_plugin_voice_t;

#endif  // SYNTH2_PLUGIN_VOICE_H_
