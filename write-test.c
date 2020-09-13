/*
  write-test.c -- Test program to write file to DOS.
  Copyright (C) 2020 Dieter Baron

  This file is part of Tachyon RL, a backup program for your RAMLink.
  The authors can be contacted at <tachyon-rl@tpau.group>.

  Redistribution and use in source and binary forms, with or without
  modification, are permitted provided that the following conditions
  are met:
  1. Redistributions of source code must retain the above copyright
     notice, this list of conditions and the following disclaimer.
  2. The names of the authors may not be used to endorse or promote
     products derived from this software without specific prior
     written permission.

  THIS SOFTWARE IS PROVIDED BY THE AUTHORS ``AS IS'' AND ANY EXPRESS
  OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
  WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
  ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY
  DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE
  GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
  INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER
  IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
  OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN
  IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

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

    ultimate_dos_delete_file(1, "test.dat");

	timer_start();
    if ((i=ultimate_dos_open_file(1, "test.dat", mode)) != 0) {
        printf("can't open file: %u - %s\n", i, ultimate_ci_status);
        return 1;
    }
    printf("open_file status: %s\n", ultimate_ci_status);

    for (i = 0; i < 32; ++i) {
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
