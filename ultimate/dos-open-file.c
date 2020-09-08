#include "dos-internal.h"

#include <string.h>

unsigned char ultimate_dos_open_file(unsigned char instance, const unsigned char *name, unsigned char mode) {
    ULTIMATE_CI.command = instance;
    ULTIMATE_CI.command = ULTIMATE_DOS_CMD_OPEN_FILE;
    ULTIMATE_CI.command = mode;
    ultimate_ci_write_string(name);
    ultimate_ci_execute();
    ultimate_ci_done();
    return ultimate_ci_status_code;
}
