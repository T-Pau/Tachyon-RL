#include <cbm.h>
#include <errno.h>
#include <stdio.h>
#include <stdint.h>

#include "drive/drive.h"
#include "timer.h"

#define DEVICE 8

uint8_t buffer[16*1024];

int main(void) {
    static uint8_t i;
    static uint16_t j;

    timer_start();
    if (cbm_open(1, DEVICE, 2, "test.dat") != 0) {
        printf("can't open file: %u.\n", _oserror);
        return 1;
    }
    
    for (i=0; i < 1; i++) {
        if (drive_read(1, buffer, sizeof(buffer)) != sizeof(buffer)) {
            printf("\nRead error: %u.\n", _oserror);
            break;
        }
        printf(".");
    }
    
    printf("\n");
    cbm_close(1);
    timer_stop();
    
    timer_output();
    printf("\n");
    
    for (j = 0; j < sizeof(buffer); j += 2) {
        if (buffer[j] != (j & 0xff) || buffer[j + 1] != (j >> 8)) {
            printf("Wrong data at %u.\n", j);
            break;
        }
    }
    
    return 1;
}
