#include <stdio.h>

#include "ultimate-dos.h"
#include "ultimate-cli.h"

int main(void) {
    unsigned char buffer[256];
	printf("%c", 0x8E);

    if (ultimate_cli_detect() ==0) {
        printf("no ultiamte command line interface.\n");
    }
    else if (ultimate_dos_identify(buffer, sizeof(buffer)) == 0) {
        printf("ultimate dos interface not found.\n");
    }
    else {
        printf("%s\n", buffer);
    }

    return 0;
}
