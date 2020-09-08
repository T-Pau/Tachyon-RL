#include "dos-internal.h"

#include <stddef.h>

#include "ci.h"

const unsigned char *ultimate_dos_identify(unsigned char instance) {
    if (!ultimate_ci_detect()) {
        return NULL;
    }

    return ultimate_dos_get_string(instance, ULTIMATE_DOS_CMD_IDENTIFY);
}
