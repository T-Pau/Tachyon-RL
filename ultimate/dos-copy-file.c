#include "dos-internal.h"

unsigned char ultimate_dos_copy_file(unsigned char instance, const unsigned char *old_name, const unsigned char *new_name) {
    ULTIMATE_CI.command = instance;
    ULTIMATE_CI.command = ULTIMATE_DOS_CMD_COPY_FILE;
    ultimate_ci_write_string(old_name);
    ULTIMATE_CI.command = 0;
    ultimate_ci_write_string(new_name);
    ultimate_ci_execute();
    ultimate_ci_done();
    return ultimate_ci_status_code;
}
