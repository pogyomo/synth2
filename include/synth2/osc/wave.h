#ifndef SYNTH2_OSC_WAVE_H_
#define SYNTH2_OSC_WAVE_H_

/// Wave types the oscillator can generate.
typedef enum {
    SYNTH2_OSC_WAVE_SINE = 0,
    SYNTH2_OSC_WAVE_TRIANGLE = 1,
    SYNTH2_OSC_WAVE_SAW = 2,
    SYNTH2_OSC_WAVE_SQUARE = 3,
} synth2_osc_wave_t;

#endif  // SYNTH2_OSC_WAVE_H_
