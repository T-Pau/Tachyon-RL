#include "ramlink-backup.h"

#include <stdio.h>

unsigned char restore_reu_dma(const char *filename) {
    static unsigned int page;
    static unsigned int length;
    const static unsigned char *string;
    
#if ENABLE_DOS
    if (ultimate_dos_open_file(1, filename, ULTIMATE_DOS_OPEN_READ) != 0) {
        printf("can't open '%s':\n  %s\n", filename, ultimate_ci_status);
        return 1;
    }
    /* TODO: check file size */
#endif
    
    page = 0;
    length = ramlink_pages;
    if (length > reu_pages) {
        length = reu_pages;
    }
    
    do {
        printf("Loading REU: ");
#if ENABLE_DOS
        if ((string=ultimate_dos_load_reu(1, 0, length)) == NULL) {
            printf("\ncan't load REU:\n  %s\n", filename, ultimate_ci_status);
            ultimate_dos_close_file(1);
            return 1;
        }
        printf("%s\n", string);
#endif

        printf("Copying to RAMLink.\n");
#if ENABLE_RAMLINK && ENABLE_REU
        ramlink_reu_dma(REU_COMMAND_REU_TO_C64, page, 0, length);
#endif
        page += length;
    } while (page != ramlink_pages);
    
#if ENABLE_DOS
    ultimate_dos_close_file(1);
#endif

    return 0;
}
