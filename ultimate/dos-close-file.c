#include "dos.h"

#include "ci.h"

unsigned char ultimate_dos_close_file(unsigned char instance) {
    ultimate_dos_cmd[0] = instance;
    ultimate_dos_cmd[1] = ULTIMATE_DOS_CMD_CLOSE_FILE;
    return ultimate_ci_execute();
}
