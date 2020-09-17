#include "tachyon.h"

#include <stdio.h>

const char *types[] = {
    "none",
    "unknown",
    "1541",
    "1571",
    "CMD FD",
    "CMD HD",
    "RAMDrive",
    "RAMLink"
};

int main(void) {
    static unsigned char i;
    
    printf("detecting drives.\n");
    detect_drives();
    printf("done.\n");
    
    for (i = 8; i < 32; ++i) {
        if (drive_types[i] != 0) {
            printf("%u: %s\n", i, types[drive_types[i]]);
        }
    }
    
    return 0;
}
