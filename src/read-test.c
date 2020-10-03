/*
  read-test.c -- Test program to read file from DOS.
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
