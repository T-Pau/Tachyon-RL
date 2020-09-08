#include "ci.h"

unsigned char ultimate_ci_execute(void) {
    /* push command */
    ULTIMATE_CI.control = ULTIMATE_CI_PUSH_CMD;

    /* wait for command to finish */
    while ((ULTIMATE_CI.control & ULTIMATE_CI_STATE_MASK) == ULTIMATE_CI_STATE_BUSY) {
        ;
    }

    /* read status */
    ultimate_ci_status_length = 0;
    while (ULTIMATE_CI.control & ULTIMATE_CI_STAT_AV) {
        ultimate_ci_status[ultimate_ci_status_length] = ULTIMATE_CI.status;
        ++ultimate_ci_status_length;
    }
    ultimate_ci_status[ultimate_ci_status_length] = '\0';

    if (ultimate_ci_status_length < 2) {
        return 0;
    }
    ultimate_ci_status_code = (ultimate_ci_status[0] - '0') * 10 + (ultimate_ci_status[1] - '0');
    return ultimate_ci_status_code;
}