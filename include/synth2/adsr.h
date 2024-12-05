#ifndef SYNTH2_ADSR_H_
#define SYNTH2_ADSR_H_

#include <stdbool.h>
#include <stdint.h>

enum synth2_adsr_stage {
    SYNTH2_ADSR_STAGE_A,
    SYNTH2_ADSR_STAGE_D,
    SYNTH2_ADSR_STAGE_S,
    SYNTH2_ADSR_STAGE_R,
    SYNTH2_ADSR_STAGE_END,
};

struct synth2_adsr {
    double fs;       // Sample rate.
    double a, d, r;  // Times for each stages. In seconds.
    double s;        // Sustain level. Must be in [[0, 1]].
    double top;      // Latest sampled value before release.
    uint64_t t;      // Logical elapsed time.
    bool hold;       // false if release called.
};

/// Initialize adsr.
/// a, d and r is in seconds, and s must be normalized.
void synth2_adsr_init(
    struct synth2_adsr *this,
    double fs,
    double a,
    double d,
    double s,
    double r
);

/// Initialize adsr but accept normalized parameters except fs.
/// These parameter is mapped into proper value by implementation-defind manner.
void synth2_adsr_init_normalized(
    struct synth2_adsr *this,
    double fs,
    double a,
    double d,
    double s,
    double r
);

/// Go on to release stage.
/// There is no effect for calling this more than twice.
void synth2_adsr_release(struct synth2_adsr *this);

/// Returns current stage.
enum synth2_adsr_stage synth2_adsr_stage(struct synth2_adsr *this);

/// Returns value in [[0, 1]], increase internal times.
double synth2_adsr_sample(struct synth2_adsr *this);

#endif  // SYNTH2_ADSR_H_
