#ifndef SYNTH2_OSCILLATOR_H_
#define SYNTH2_OSCILLATOR_H_

typedef enum synth2_oscillator_type {
    SYNTH2_OSC_SINE,
    SYNTH2_OSC_TRIANGLE,
    SYNTH2_OSC_SAW,
    SYNTH2_OSC_SQUARE,
} synth2_oscillator_type_t;

typedef struct synth2_oscillator {
    /// Parameters for wave generation.
    double sample_rate, key, phase, duty;

    /// Sample a point of wave, then advance phase.
    double (*sample)(struct synth2_oscillator *osc);
} synth2_oscillator_t;

/// Initialize oscillator to generates specified wave.
///
/// If type == SYNTH2_OSC_SQUARE, then duty must be specified and in [0.0, 1.0].
/// Otherwise, this parameter is just ignored.
void synth2_oscillator_init(
    synth2_oscillator_t *osc,
    synth2_oscillator_type_t type,
    double sample_rate,
    double key,
    double duty
);

#endif  // SYNTH2_OSCILLATOR_H_
