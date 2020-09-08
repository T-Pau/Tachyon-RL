#include <stdio.h>

#include "ultimate/dos.h"
#include "ultimate/ci.h"
#include "timer.h"

unsigned char block[512];

int main(void) {
    const unsigned char *string;
    unsigned char i = 0;
    unsigned char mode = ULTIMATE_DOS_OPEN_WRITE | ULTIMATE_DOS_OPEN_CREATE_NEW | ULTIMATE_DOS_OPEN_CREATE_ALWAYS;

    do {
        block[i] = i;
        block[256+i] = i;
        ++i;
    } while (i != 0);

    if ((string = ultimate_dos_identify(1)) == NULL) {
        printf("no ultimate dos interface\n");
        return 1;
    }
    printf("version: %s\n", string);

    if ((string=ultimate_dos_copy_home_path(1)) == NULL) {
        printf("can't copy home path: %s\n", ultimate_ci_status);
        return 1;
    }
    printf("Current directory: %s\n", string);

	timer_start();
    if ((i=ultimate_dos_open_file(1, "test.dat", mode)) != 0) {
        printf("can't open file: %u - %s\n", i, ultimate_ci_status);
        return 1;
    }
    printf("open_file status: %s\n", ultimate_ci_status);

    for (i = 0; i < 4 /*32*/; ++i) {
        if (ultimate_dos_write_data(1, block, 512) != 0) {
            printf("can't write data: %s\n", ultimate_ci_status);
            return 1;
        }
        printf(".");
    }
    printf("\n");

    if ((i=ultimate_dos_close_file(1)) != 0) {
        printf("can't close file: %u - %s\n", i, ultimate_ci_status);
        return 1;
    }
    printf("close_file status: %s\n", ultimate_ci_status);

	timer_stop();
	printf("It took: ");
	timer_output();
	printf("\n");

    return 0;
}
