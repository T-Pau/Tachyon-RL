#include "dos-internal.h"

#include "ci.h"

unsigned int ultimate_dos_read_data(unsigned char instance, unsigned char *buffer, unsigned int length) {
    ULTIMATE_CI.command = instance;
    ULTIMATE_CI.command = ULTIMATE_DOS_CMD_READ_DATA;
    ULTIMATE_CI.command = length & 0xff;
    ULTIMATE_CI.command = length >> 8;
    if (ultimate_ci_execute() != 0) {
        return 0;
    }
    return ultimate_ci_read(buffer, length);
}
