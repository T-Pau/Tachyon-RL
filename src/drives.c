#include "tachyon.h"

#include <stdio.h>
#include <errno.h>

const char *types[] = {
    "none",
    "1541",
    "1570",
    "1571",
    "1581",
    "CMD FD",
    "CMD HD",
    "RAMDrive",
    "RAMLink",
    "SD2IEC",
    "IDE64",
    "IDESERV"
};

int main(void) {
    static unsigned char i;
    
    drive_detect();
    
    for (i = 8; i < 32; ++i) {
        if (drive_types[i] != 0) {
            if (drive_types[i] == DRIVE_TYPE_UNKNOWN) {
                printf("%2u: unknown drive\n", i);
            }
            else {
                printf("%2u: %s\n", i, types[drive_types[i]]);
            }
        }
    }
    
    return 0;
}
