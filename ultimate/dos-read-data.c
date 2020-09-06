#include "dos.h"

#include "ci.h"

unsigned char ultimate_dos_read_data(unsigned char instance, unsigned char *buffer, unsigned int length) {
    ultimate_dos_cmd[0] = instance;
    ultimate_dos_cmd[1] = ULTIMATE_DOS_CMD_READ_DATA;
    ultimate_dos_cmd[2] = length & 0xff;
    ultimate_dos_cmd[3] = length << 8;
    ultimate_ci_write(ultimate_dos_cmd, 4);
    if (ultimate_ci_execute() != 0) {
        return 0;
    }
    return ultimate_ci_read(buffer, length);
}
