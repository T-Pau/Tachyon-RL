#include "ultimate-cli.h"

#include <stdio.h>

unsigned char ultimate_cli_status[257];
unsigned char ultimate_cli_status_length;

unsigned char ultimate_cli_detect(void) {
    return (ULTIMATE_CLI.command == 0xc9 && ULTIMATE_CLI.status == 0);
}

void ultimate_cli_done(void) {
    while (ULTIMATE_CLI.control & ULTIMATE_CLI_STATE_DATA_LAST) {
        ULTIMATE_CLI.control = ULTIMATE_CLI_DATA_ACC;
    }
}

unsigned char ultimate_cli_execute(void) {
    /* push command */
    ULTIMATE_CLI.control = ULTIMATE_CLI_PUSH_CMD;

    /* wait for command to finish */
    while (ULTIMATE_CLI.control & ULTIMATE_CLI_CMD_BUSY) {
        ;
    }

    /* read status */
    ultimate_cli_status_length = 0;
    while (ULTIMATE_CLI.control & ULTIMATE_CLI_STAT_AV) {
        ultimate_cli_status[ultimate_cli_status_length] = ULTIMATE_CLI.status;
        ++ultimate_cli_status_length;
    }
    ultimate_cli_status[ultimate_cli_status_length] = '\0';

    if (ultimate_cli_status_length < 2) {
        return 0;
    }
    return (ultimate_cli_status[0] - '0') * 10 + (ultimate_cli_status[1] - '0');
}

unsigned int ultimate_cli_read(unsigned char *data, unsigned int length) {
    unsigned int i = 0;

    while (ULTIMATE_CLI.control & ULTIMATE_CLI_STATE_DATA_LAST) {
        while (ULTIMATE_CLI.control & ULTIMATE_CLI_DATA_AV) {
            data[i] = ULTIMATE_CLI.response;
            i++;
            if (i == length) {
                return i;
            }
        }
        ULTIMATE_CLI.control = ULTIMATE_CLI_DATA_ACC;
    }

    return i;
}

void ultimate_cli_write(const unsigned char *data, unsigned int length) {
    unsigned int i = 0;
    while (i < length) {
        ULTIMATE_CLI.command = data[i];
        ++i;
    }
}
