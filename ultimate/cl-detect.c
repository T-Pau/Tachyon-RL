#include "ci.h"

unsigned char ultimate_ci_detect(void) {
    return (ULTIMATE_CI.command == 0xc9 && ULTIMATE_CI.status == 0);
}
