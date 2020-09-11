#include "tachyon.h"

#include <stdio.h>

int main(void) {
    static unsigned int reu_size;
    
    asm("sei");
    ramlink_activate();
    reu_size = reu_detect();
    ramlink_deactivate();
    asm("cli");
    
    printf("reu size: %u\n", reu_size);
    
    return 0;
}
