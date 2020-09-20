#include "tachyon.h"

uint16_t speed_factor[] = { /* ms/64k */
    /* Ultimate */
    0, /* 1Mhz */
    0, /* 2Mhz */
    0, /* SuperCPU V1 20Mhz */
    0, /* SuperCPU V2 20Mhz */

    /* Ultimate + REU */
    1875, /* 1Mhz */
    0, /* 2Mhz */
    0351, /* SuperCPU V1 20Mhz */
    0234, /* SuperCPU V2 20Mhz */

    /* SD2IEC */
    16875, /* 1Mhz */ /* TODO: estimate */
    0, /* 2Mhz */
    0, /* SuperCPU V1 20Mhz */
    0, /* SuperCPU V2 20Mhz */
};
