#include "tachyon.h"

#include <stdio.h>

unsigned char backup_reu_dma(void) {
    static unsigned int page;
    static unsigned int length;
    
    unsigned long length_bytes = ramlink_size;
    
    page = 0;
    length = ramlink_pages;
    if (length > reu_pages) {
        length = reu_pages;
        length_bytes = reu_size;
    }
    
    do {
        printf("Copying to REU.\n");
#if ENABLE_RAMLINK && ENABLE_REU
        ramlink_reu_dma(REU_COMMAND_C64_TO_REU, page, 0, length);
#endif
        printf("Saving REU.\n");
#if ENABLE_DOS
        if (ultimate_dos_save_reu(1, 0, length_bytes) != 0) {
            printf("\ncan't save REU:\n  %s\n", filename, ultimate_ci_status);
            return 1;
        }
#endif
        page += length;
    } while (page != ramlink_pages);
    
    return 0;
}
