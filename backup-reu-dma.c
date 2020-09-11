#include "ramlink-backup.h"

#include <stdio.h>

unsigned char backup_reu_dma(const char *filename) {
    static unsigned int page;
    static unsigned int length;
    static const unsigned char *string;
    
#if ENABLE_DOS
    if (ultimate_dos_open_file(1, filename, ULTIMATE_DOS_OPEN_CREATE_ALWAYS|ULTIMATE_DOS_OPEN_CREATE_NEW|ULTIMATE_DOS_OPEN_WRITE) != 0) {
        printf("can't open '%s':\n  %s\n", filename, ultimate_ci_status);
        return 1;
    }
#endif
    
    page = 0;
    length = ramlink_pages;
    if (length > reu_pages) {
        length = reu_pages;
    }
    
    do {
        printf("Copying to REU.\n");
#if ENABLE_RAMLINK && ENABLE_REU
        ramlink_reu_dma(REU_COMMAND_C64_TO_REU, page, 0, length);
#endif
        printf("Saving REU: ");
#if ENABLE_DOS
        if ((string=ultimate_dos_save_reu(1, 0, length)) == NULL) {
            printf("\ncan't save REU:\n  %s\n", filename, ultimate_ci_status);
            ultimate_dos_close_file(1);
            return 1;
        }
        printf("%s\n", string);
#endif
        page += length;
    } while (page != ramlink_pages);
    
#if ENABLE_DOS
    ultimate_dos_close_file(1);
#endif

    return 0;
}
