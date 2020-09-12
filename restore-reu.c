#include "tachyon.h"

#include <conio.h>
#include <stdio.h>

unsigned char restore_reu(void) {
    static unsigned long address;
    
    printf("Loading REU.\n");
    
#if ENABLE_DOS
    if (ultimate_dos_load_reu(1, 0, ramlink_size) != NULL) {
        printf("Can't load REU: %s\n", ultimate_ci_status);
        return 1;
    }
#endif
    
    printf("Copying REU to RAMLink:   0 of %3u", (unsigned int)(ramlink_size >> 16));
    for (address = 0; address < ramlink_size; address += BUFFER_SIZE) {
        gotox(0);
        printf("Copying REU to RAMLink: %3u", (unsigned int)(address>>16));
#if ENABLE_REU
        reu_copy(address, buffer, BUFFER_SIZE, REU_COMMAND_REU_TO_C64);
#endif
#if ENABLE_RAMLINK
        ramlink_reu_copy(address, buffer, BUFFER_SIZE, REU_COMMAND_C64_TO_REU);
#endif
    }
    gotox(0);
    printf("Copying REU to RAMLink: %3u\n", (unsigned int)(address>>16));
    
    return 0;
}
