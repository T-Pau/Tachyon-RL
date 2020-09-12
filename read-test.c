#include <stdio.h>

#include "ultimate/dos.h"
#include "ultimate/ci.h"
#include "timer.h"

unsigned char block[16*1024];

int main(void) {
    const unsigned char *string;
    static unsigned char i = 0;
    static unsigned int n;

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
    for (i = 0; i < 4; ++i) {
        if ((ultimate_dos_open_file(1, "test.dat", ULTIMATE_DOS_OPEN_READ)) != 0) {
            printf("can't open file: %s\n", ultimate_ci_status);
            return 1;
        }

        n = ultimate_dos_read_data(1, block, sizeof(block));
        if (ultimate_ci_status_code != 0) {
            printf("can't read data: %s\n", ultimate_ci_status);
            return 1;
        }
        if (n != sizeof(block)) {
            printf("short read (%u instead of %u\n", n, sizeof(block));
            return 1;
        }

        if ((ultimate_dos_close_file(1)) != 0) {
            printf("can't close file: %s\n", ultimate_ci_status);
            return 1;
        }
        printf(".");
    }
    printf("\n");

	timer_stop();
	printf("It took: ");
	timer_output();
	printf("\n");

    return 0;
}
