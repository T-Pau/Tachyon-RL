#include "ultimate-dos.h"

#define DOS_CMD_IDENTIFY 0x01

#include "ultimate-cli.h"

unsigned char ultimate_dos_instance = 1;

static unsigned char cmd[16];

unsigned int ultimate_dos_identify(unsigned char *buffer, unsigned int length) {
    cmd[0] = ultimate_dos_instance;
    cmd[1] = DOS_CMD_IDENTIFY;

    ultimate_cli_write(cmd, 2);
    if (ultimate_cli_execute() != 0) {
        return 0;
    }

    length = ultimate_cli_read(buffer, length - 1);
    buffer[length] = '\0';
    ultimate_cli_done();
    return length;
}

