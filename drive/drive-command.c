#include "drive.h"

#include <cbm.h>
#include <errno.h>

const char *drive_command(uint8_t id, const char *command) {
    static char buffer[256];
    static uint8_t i;
    
    if (cbm_open(15, id, 15, command) != 0) {
        return NULL;
    }
    
    if ((i = cbm_k_chkin(15)) != 0) {
        _oserror = i;
        cbm_k_close(15);
        return NULL;
    }
    
    i = 0;
    while (i < 254) {
        buffer[i] = cbm_k_basin();
        if (buffer[i] == 0x0d) {
            break;
        }
        ++i;
    }
        
    buffer[i] = '\0';
        
    cbm_k_clrch();
    cbm_k_close(15);
    
    return buffer;
}
