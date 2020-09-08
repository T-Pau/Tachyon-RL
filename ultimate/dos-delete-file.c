#include "dos-internal.h"

unsigned char ultimate_dos_delete_file(unsigned char instance, const unsigned char *name) {
    ULTIMATE_CI.command = instance;
    ULTIMATE_CI.command = ULTIMATE_DOS_CMD_DELETE_FILE;
    ultimate_ci_write_string(name);
    ultimate_ci_execute();
    ultimate_ci_done();
    return ultimate_ci_status_code;
}