#include "dos-internal.h"

#include <stddef.h>

#include "ci.h"

const unsigned char *ultimate_dos_get_path(unsigned char instance) {
    return ultimate_dos_get_string(instance, ULTIMATE_DOS_CMD_GET_PATH);
}
