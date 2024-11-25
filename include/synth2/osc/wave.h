#ifndef SYNTH2_OSC_WAVE_H_
#define SYNTH2_OSC_WAVE_H_

/// Wave types the oscillator can generate.
typedef enum {
    SYNTH2_OSC_WAVE_SINE,
    SYNTH2_OSC_WAVE_TRIANGLE,
    SYNTH2_OSC_WAVE_SAW,
    SYNTH2_OSC_WAVE_SQUARE,
    SYNTH2_OSC_WAVE_MIN = SYNTH2_OSC_WAVE_SINE,
    SYNTH2_OSC_WAVE_MAX = SYNTH2_OSC_WAVE_SQUARE,
} synth2_osc_wave_t;

#endif  // SYNTH2_OSC_WAVE_H_
