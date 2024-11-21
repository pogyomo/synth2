#ifndef SYNTH2_HELPER_H_
#define SYNTH2_HELPER_H_

#include <stdint.h>

/// Convert midi1 key number (0..127) into frequency.
double k2f(int16_t k);

#endif  // SYNTH2_HELPER_H_
