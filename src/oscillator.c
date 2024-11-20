#include "synth2/oscillator.h"

#include <math.h>

#define PI 3.141592

static inline double k2f(double p) {
    return 440.0 * exp2((p - 69.0) / 12.0);
}

static inline double sine(double x, double duty) {
    return sin(x * 2.0 * PI);
}

static inline double triangle(double x, double duty) {
    return 0.0;  // TODO
}

static inline double saw(double x, double duty) {
    return 0.0;  // TODO
}

static inline double square(double x, double duty) {
    return 0.0;  // TODO
}

static inline double sample(synth2_oscillator_t *osc, double (*gen)(double, double)) {
    const double amp = gen(osc->phase, osc->duty);
    osc->phase += k2f(osc->key) / osc->sample_rate;
    if (osc->phase >= 1.0) osc->phase -= 1.0;
    return amp;
}

static double sample_sine(synth2_oscillator_t *osc) {
    return sample(osc, sine);
}

static double sample_triangle(synth2_oscillator_t *osc) {
    return sample(osc, triangle);
}

static double sample_saw(synth2_oscillator_t *osc) {
    return sample(osc, saw);
}

static double sample_square(synth2_oscillator_t *osc) {
    return sample(osc, square);
}

void synth2_oscillator_init(
    synth2_oscillator_t *osc,
    synth2_oscillator_type_t type,
    double sample_rate,
    double key,
    double phase,
    double duty
) {
    osc->sample_rate = sample_rate;
    osc->key = key;
    osc->phase = phase;
    osc->duty = duty;
    if (type == SYNTH2_OSC_SINE) {
        osc->sample = sample_sine;
    } else if (type == SYNTH2_OSC_TRIANGLE) {
        osc->sample = sample_triangle;
    } else if (type == SYNTH2_OSC_SAW) {
        osc->sample = sample_saw;
    } else {
        osc->sample = sample_square;
    }
}
