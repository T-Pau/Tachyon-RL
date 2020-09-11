#include "tachyon.h"

#include <stdio.h>

unsigned char restore(void) {
    const ultimate_dos_file_info_t *file_info;
    unsigned char ret;
    
#if ENABLE_DOS
    if (ultimate_dos_open_file(1, filename, ULTIMATE_DOS_OPEN_READ) != 0) {
        printf("Can't open '%s':\n  %s\n", filename, ultimate_ci_status);
        return 1;
    }
    
    if ((file_info = ultimate_dos_file_info(1)) == NULL) {
        printf("Can't get file info: %s\n", ultimate_ci_status);
        return 1;
    }

    if (file_info->size < ramlink_size) {
        printf("File is too short (%lud bytes)\n", file_info->size);
        return 1;
    }
    else if (file_info->size > ramlink_size) {
        printf("File is too long (%lud bytes)\n", file_info->size);
        return 1;
    }
#endif
    
    if (reu_size >= ramlink_size) {
        ret = restore_reu();
    }
    else {
        ret = restore_dos();
    }
    
#if ENABLE_DOS
    ultimate_dos_close_file(1);
#endif
    
    return ret;
}
