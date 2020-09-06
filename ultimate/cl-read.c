#include "ci.h"

unsigned int ultimate_ci_read(unsigned char *data, unsigned int length) {
    unsigned int i = 0;

    while (ULTIMATE_CI.control & ULTIMATE_CI_STATE_DATA_LAST) {
        while (ULTIMATE_CI.control & ULTIMATE_CI_DATA_AV) {
            data[i] = ULTIMATE_CI.response;
            i++;
            if (i == length) {
                return i;
            }
        }
        ULTIMATE_CI.control = ULTIMATE_CI_DATA_ACC;
    }

    return i;
}
