#include "dos.h"

#include <string.h>

#include "ci.h"

unsigned char ultimate_dos_open_file(unsigned char instance, const unsigned char *name, unsigned char mode) {
    ultimate_dos_cmd[0] = instance;
    ultimate_dos_cmd[1] = ULTIMATE_DOS_CMD_OPEN_FILE;
    ultimate_dos_cmd[2] = mode;
    ultimate_ci_write(ultimate_dos_cmd, 3);
    ultimate_ci_write(name, strlen(name));
    return ultimate_ci_execute();
}
