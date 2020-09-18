#include "drive.h"

#include <stddef.h>

const char *drive_identify(uint8_t id) {
    char *status = (char *)drive_command(id, "ui");
    uint8_t i = 3;
    
    if (status == NULL) {
        return NULL;
    }
    
    if (status[0] != '7' || status[1] != '3' || status[2] != ',') {
        /* TODO: set error */
        return NULL;
    }
    
    while (status[i] != ',' && status[i] != '\0') {
        ++i;
    }
    status[i] = '\0';
    
    return status + 3;
}
