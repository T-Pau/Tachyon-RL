#include "tachyon.h"

#include <stdio.h>

void detect_cpu(void) {
    if (((*(uint8_t *)0xd0bc) & 0x80) == 0) {
        if ((*(uint8_t *)0xd0b0) & 0x80) {
            cpu = CPU_SUPERCPU_V1;
        }
        else {
            cpu = CPU_SUPERCPU_V2;
        }
        
        if ((*(uint8_t *)0xd0b5) & 0x40) {
            cpu_speed = 1;
        }
        else {
            cpu_speed = 20;
        }
    }
    else if (*(uint8_t *)0xd030 == 0xfc) {
        cpu = CPU_C128;
        cpu_speed = 2;
    }
    else {
        cpu = CPU_C64;
        cpu_speed = 1;
    }
}
