#include "tachyon.h"

#include <stdio.h>

unsigned char restore_reu_dma(void) {
    static unsigned int page;
    static unsigned int length;
    
    page = 0;
    length = ramlink_pages;
    if (length > reu_pages) {
        length = reu_pages;
    }
    
    do {
        printf("Loading REU\n");
#if ENABLE_DOS
        if (ultimate_dos_load_reu(1, 0, length) != 0) {
            printf("Can't load REU:\n  %s\n", filename, ultimate_ci_status);
            return 1;
        }
#endif

        printf("Copying to RAMLink.\n");
#if ENABLE_RAMLINK && ENABLE_REU
        ramlink_reu_dma(REU_COMMAND_REU_TO_C64, page, 0, length);
#endif
        page += length;
    } while (page != ramlink_pages);
    
    return 0;
}
