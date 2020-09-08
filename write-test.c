#include <stdio.h>

#include "ultimate/dos.h"
#include "ultimate/ci.h"

unsigned char block[512];

int main(void) {
    const unsigned char *string;
    unsigned char i = 0;
    unsigned char mode = ULTIMATE_DOS_OPEN_WRITE | ULTIMATE_DOS_OPEN_CREATE_NEW | ULTIMATE_DOS_OPEN_CREATE_ALWAYS;

    printf("mode: %02x\n", mode);

    do {
        block[i] = i;
        block[256+i] = i;
        ++i;
    } while (i != 0);

    if ((string = ultimate_dos_identify(1)) == NULL) {
        printf("no ultimate dos interface\n");
        return 1;
    }
    printf("identify status: %s\n", ultimate_ci_status);
    printf("version: %s\n", string);

    if ((string = ultimate_dos_get_path(1)) == NULL) {
        printf("can't get path: %s\n", ultimate_ci_status);
        return 1;
    }
    printf("get_path status: %s\n", ultimate_ci_status);
    printf("path: %s\n", string);

    if ((string=ultimate_dos_copy_home_path(1)) == NULL) {
        printf("can't copy home path: %s\n", ultimate_ci_status);
        return 1;
    }
    printf("copy_home_path: %s\n", ultimate_ci_status);
    printf("home path: %s\n", string);

#if 0
    if ((i=ultimate_dos_change_dir(1, "RAMLink")) != 0) {
        printf("can't change directory: %u - %s\n", i, ultimate_ci_status);
        return 1;
    }
    printf("change_dir: %s\n", ultimate_ci_status);

    if ((string = ultimate_dos_get_path(1)) == NULL) {
        printf("can't get path: %s\n", ultimate_ci_status);
        string = "";
    }
    printf("get_path: %s\n", ultimate_ci_status);
    printf("path: %s\n", string);
#endif

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

    return 0;
}
