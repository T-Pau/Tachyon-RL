#include "ramlink-backup.h"

#include <stdio.h>

unsigned char backup_reu(const char *filename) {
    static unsigned long address;
    
#if ENABLE_DOS
    if (ultimate_dos_open_file(1, filename, ULTIMATE_DOS_OPEN_CREATE_ALWAYS|ULTIMATE_DOS_OPEN_CREATE_NEW|ULTIMATE_DOS_OPEN_WRITE) != 0) {
        printf("can't open '%s':\n  %s\n", filename, ultimate_ci_status);
        return 1;
    }
#endif
    
    printf("%cCopied   0 of %3u\n", 147, (unsigned int)(ramlink_size >> 16));
    for (address = 0; address < ramlink_size; address += BUFFER_SIZE) {
        printf("%cCopied %3u", 19, (unsigned int)(address>>16));
#if ENABLE_RAMLINK
        ramlink_reu_copy(address, buffer, BUFFER_SIZE, REU_COMMAND_REU_TO_C64);
#endif
#if ENABLE_REU
        reu_copy(address, buffer, BUFFER_SIZE, REU_COMMAND_C64_TO_REU);
#endif
    }
    printf("%cCopied %3u\n", 19, (unsigned int)(address>>16));
    
    printf("Saving REU\n");
    
#if ENABLE_DOS
    if (ultimate_dos_save_reu(1, 0, ramlink_size) == NULL) {
        printf("can't save REU:\n  %s\n", filename, ultimate_ci_status);
        ultimate_dos_close_file(1);
        return 1;
    }
    ultimate_dos_close_file(1);
#endif
    
    return 0;
}
