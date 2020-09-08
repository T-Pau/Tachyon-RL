#include "dos-internal.h"

#include "ci.h"

unsigned char ultimate_dos_close_file(unsigned char instance) {
    ULTIMATE_CI.command = instance;
    ULTIMATE_CI.command = ULTIMATE_DOS_CMD_CLOSE_FILE;
    ultimate_ci_execute();
    ultimate_ci_done();
    return ultimate_ci_status_code;
}
