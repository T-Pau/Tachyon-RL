#include "tachyon.h"
#include "timer.h"

#include <stdio.h>

void delay(void) {
    static unsigned long counter;

    for (counter = 0; counter < 0x10000; counter++);
}

int main(void) {
    timer_start();
    delay();
    timer_stop();

    printf("1Mhz: ");
    timer_output();
    printf("\n");

    timer_start();
    c128_2mhz();
    delay();
    c128_1mhz();
    timer_stop();

    printf("2Mhz: ");
    timer_output();
    printf("\n");

    return 0;
}