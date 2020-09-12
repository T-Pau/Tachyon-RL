#include "tachyon.h"

#include <conio.h>
#include <stdio.h>

unsigned char restore_dos(void) {
    static unsigned long address;
    
    printf("Loading RAMLink from disk:   0 of %3u", (unsigned int)(ramlink_size >> 16));
    for (address = 0; address < ramlink_size; address += BUFFER_SIZE) {
        gotox(0);
        printf("Loading RAMLink from disk: %3u\n", (unsigned int)(address>>16));
#if ENABLE_DOS
        if (ultimate_dos_read_data(1, buffer, BUFFER_SIZE) != BUFFER_SIZE) {
            printf("Read error: %s\n", ultimate_ci_status);
            return 1;
        }
#endif
#if ENABLE_RAMLINK
        ramlink_reu_copy(address, buffer, BUFFER_SIZE, REU_COMMAND_C64_TO_REU);
#endif
    }
    
    gotox(0);
    printf("Loading RAMLink from disk: %3u\n", (unsigned int)(address>>16));
    
    return 0;
}
