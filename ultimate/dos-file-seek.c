#include "dos-internal.h"

unsigned char ultimate_dos_file_seek(unsigned char instance, unsigned long position) {
    ULTIMATE_CI.command= instance;
    ULTIMATE_CI.command = ULTIMATE_DOS_CMD_FILE_SEEK;
    ULTIMATE_CI.command = position & 0xff;
    ULTIMATE_CI.command = (position >> 8) & 0xff;
    ULTIMATE_CI.command = (position >> 16) & 0xff;
    ULTIMATE_CI.command = position >> 24;
    ultimate_ci_execute();
    ultimate_ci_done();
    return ultimate_ci_status_code;
}
