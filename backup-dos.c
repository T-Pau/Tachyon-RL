#include "tachyon.h"

#include <conio.h>
#include <stdio.h>

unsigned char backup_dos(void) {
    static unsigned long address;
    
    printf("Saving RAMLink to disk:   0 of %3u", (unsigned int)(ramlink_size >> 16));
    for (address = 0; address < ramlink_size; address += BUFFER_SIZE) {
        gotox(0);
        printf("Saving RAMLink to disk: %3u", (unsigned int)(address>>16));
#if ENABLE_RAMLINK
        ramlink_reu_copy(address, buffer, BUFFER_SIZE, REU_COMMAND_REU_TO_C64);
#endif
#if ENABLE_DOS
        if (ultimate_dos_write_data(1, buffer, BUFFER_SIZE) != 0) {
            printf("Write error: %s\n", ultimate_ci_status);
            return 1;
        }
#endif
    }
    
    gotox(0);
    printf("Saving RAMLink to disk: %3u\n", (unsigned int)(address>>16));
        
    return 0;
}
