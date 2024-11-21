#include "synth2/helper.h"

#include <math.h>

double k2f(int16_t k) {
    return 440.0 * exp2((double)(k - 69) / 12.0);
}
