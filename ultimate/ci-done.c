#include "ci.h"

void ultimate_ci_done(void) {
    while (ULTIMATE_CI.control & ULTIMATE_CI_STATE_DATA_LAST) {
        ULTIMATE_CI.control = ULTIMATE_CI_DATA_ACC;
        while ((ULTIMATE_CI.control & ULTIMATE_CI_STATE_MASK) == ULTIMATE_CI_STATE_BUSY) {
            ;
        }
    }
}
