#include "ci.h"

void ultimate_ci_write(const unsigned char *data, unsigned int length) {
    unsigned int i = 0;
    while (i < length) {
        ULTIMATE_CI.command = data[i];
        ++i;
    }
}
