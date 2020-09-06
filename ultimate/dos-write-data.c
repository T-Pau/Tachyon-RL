#include "dos.h"

#include "ci.h"

unsigned char ultimate_dos_write_data(unsigned char instance, const unsigned char *buffer, unsigned int length) {
    unsigned int n, ret;
    ultimate_dos_cmd[0] = instance;
    ultimate_dos_cmd[1] = ULTIMATE_DOS_CMD_READ_DATA;
    ultimate_dos_cmd[2] = 0;
    ultimate_dos_cmd[3] = 0;

    while (length > 0) {
        n = length > 512 ? 512 : length;
        ultimate_ci_write(ultimate_dos_cmd, 4);
        ultimate_ci_write(buffer, n);
        ret = ultimate_ci_execute();
        if (ret != 0) {
            return ret;
        }
        length -= n;
        buffer += n;
    }

    return 0;
}
