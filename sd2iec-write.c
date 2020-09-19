#include <cbm.h>
#include <stdio.h>
#include <stdint.h>

#include "timer.h"


uint8_t buffer[16*1024];

void do_write(unsigned char id, const unsigned char *buffer, unsigned int size);

int main(void) {
    static uint8_t i;

    timer_start();
    cbm_open(1, 10, 1, "test.dat");
    
    for (i=0; i < 64; i++) {
        drive_write(1, buffer, sizeof(buffer));
        printf(".");
    }
    
    printf("\n");
    cbm_close(1);
    timer_stop();
    
    timer_output();
    printf("\n");
    
    return 1;
}
