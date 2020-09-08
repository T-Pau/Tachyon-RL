#include <stdio.h>

#include "ultimate/dos.h"
#include "ultimate/ci.h"

int main(void) {
    const unsigned char *identifier;

	printf("%c", 0x8E);

    if (ultimate_ci_detect() ==0) {
        printf("no ultiamte command line interface.\n");
    }
    else if ((identifier = ultimate_dos_identify(1)) == NULL) {
        printf("ultimate dos interface not found.\n");
    }
    else {
        puts(identifier);
        putchar('\n');
    }

    return 0;
}
