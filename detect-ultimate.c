#include <stdio.h>

#include "ultimate/dos.h"
#include "ultimate/ci.h"

int main(void) {
    unsigned char buffer[256];
	printf("%c", 0x8E);

    if (ultimate_ci_detect() ==0) {
        printf("no ultiamte command line interface.\n");
    }
    else if (ultimate_dos_identify(1, buffer, sizeof(buffer)) == 0) {
        printf("ultimate dos interface not found.\n");
    }
    else {
        printf("%s\n", buffer);
    }

    return 0;
}
