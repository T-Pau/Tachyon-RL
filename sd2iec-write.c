#include <cbm.h>
#include <errno.h>
#include <stdio.h>
#include <stdint.h>

#include "drive/drive.h"
#include "timer.h"


uint8_t buffer[16*1024];

int main(void) {
    static uint8_t i;
    static uint16_t j;

    for (j = 0; j < sizeof(buffer); j += 2) {
        buffer[j] = j & 0xff;
        buffer[j + 1] = (j >> 8);
    }

    timer_start();
    if (cbm_open(1, 9, 1, "test.dat") != 0) {
        printf("can't open file: %u.\n", _oserror);
    }
    
    for (i=0; i < 1; i++) {
        if (!drive_write(1, buffer, sizeof(buffer))) {
            printf("\nwrite error: %u.\n", _oserror);
            break;
        }
        printf(".");
    }
    
    printf("\n");
    cbm_close(1);
    timer_stop();
    
    timer_output();
    printf("\n");
    
    return 1;
}
