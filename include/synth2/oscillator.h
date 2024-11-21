#ifndef SYNTH2_OSCILLATOR_H_
#define SYNTH2_OSCILLATOR_H_

#include <stdint.h>

typedef enum synth2_oscillator_type {
    SYNTH2_OSC_SINE,
    SYNTH2_OSC_TRIANGLE,
    SYNTH2_OSC_SAW,
    SYNTH2_OSC_SQUARE,
} synth2_oscillator_type_t;

typedef struct synth2_oscillator {
    /// Sample rate to sample a point of wave.
    double sample_rate;

    /// Phase in wave. Must be in [0, 2π).
    double phase;

    /// Duty cycle for square wave generation.
    double duty;

    /// Previously sampled value.
    double prev;

    /// MIDI1 key number to generate wave.
    int16_t key;

    /// Sample a point of wave, then advance phase.
    double (*sample)(struct synth2_oscillator *osc);
} synth2_oscillator_t;

/// Initialize oscillator to generates specified wave.
///
/// If type == SYNTH2_OSC_SQUARE, then duty must be specified and in [0, 1].
/// Otherwise, this parameter is just ignored.
void synth2_oscillator_init(
    synth2_oscillator_t *osc,
    synth2_oscillator_type_t type,
    double sample_rate,
    int16_t key,
    double duty
);

#endif  // SYNTH2_OSCILLATOR_H_
