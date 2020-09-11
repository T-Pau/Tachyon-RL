#include "tachyon.h"

#include <stdio.h>

unsigned char backup(void) {
    unsigned char ret;
#if ENABLE_DOS
    if (ultimate_dos_open_file(1, filename, ULTIMATE_DOS_OPEN_CREATE_ALWAYS|ULTIMATE_DOS_OPEN_CREATE_NEW|ULTIMATE_DOS_OPEN_WRITE) != 0) {
        printf("Can't open '%s':\n  %s\n", filename, ultimate_ci_status);
        return 1;
    }
#endif
    
    if (reu_size >= ramlink_size) {
        ret = backup_reu();
    }
    else {
        ret = backup_dos();
    }
    
#ifdef ENABLE_DOS
    ultimate_dos_close_file(1);
#endif

    return ret;
}
