#include "dos.h"

#include "ci.h"

unsigned int ultimate_dos_identify(unsigned char instance, unsigned char *buffer, unsigned int length) {
    ultimate_dos_cmd[0] = instance;
    ultimate_dos_cmd[1] = ULTIMATE_DOS_CMD_IDENTIFY;

    ultimate_ci_write(ultimate_dos_cmd, 2);
    if (ultimate_ci_execute() != 0) {
        return 0;
    }

    length = ultimate_ci_read(buffer, length - 1);
    buffer[length] = '\0';
    ultimate_ci_done();
    return length;
}
