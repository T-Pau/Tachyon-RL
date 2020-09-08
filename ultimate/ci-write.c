#include "ci.h"

void ultimate_ci_write(const unsigned char *data, unsigned int length) {
    while (length > 0) {
        ULTIMATE_CI.command = *data;
        --length;
        ++data;
    }
}
