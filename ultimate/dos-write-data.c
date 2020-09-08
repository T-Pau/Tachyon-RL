#include "dos-internal.h"

#include "ci.h"

unsigned char ultimate_dos_write_data(unsigned char instance, const unsigned char *buffer, unsigned int length) {
    unsigned int n;

    while (length > 0) {
        n = length > 256 ? 256 : length;
        ULTIMATE_CI.command = instance;
        ULTIMATE_CI.command = ULTIMATE_DOS_CMD_WRITE_DATA;
        ULTIMATE_CI.command = 0;
        ULTIMATE_CI.command = 0;
        ultimate_ci_write(buffer, n);
        ultimate_ci_execute();
        ultimate_ci_done();
        if (ultimate_ci_status_code != 0) {
            return ultimate_ci_status_code;
        }
        length -= n;
        buffer += n;
    }

    return 0;
}
