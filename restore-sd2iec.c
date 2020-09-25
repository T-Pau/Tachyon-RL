/*
  restore-sd2iec.c -- Read from SD2IEC.
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

#include "tachyon.h"

#include <conio.h>
#include <stdio.h>

bool restore_sd2iec(void) {
    static unsigned long address;
    
    printf("Not implemented yet.\n");
    return false;
    
#if ENABLE_DOS
    if (cbm_open(1, sd2iec_device, 2, filename) != 0) {
        printf("Can't open file.\n"); /* TODO: error message */
        cbm_close(1);
        return false;
    }
#endif

    printf("Loading RAMLink from disk:   0 of %3u", (unsigned int)(ramlink_size >> 16));
    for (address = 0; address < ramlink_size; address += BUFFER_SIZE) {
        gotox(0);
        printf("Loading RAMLink from disk: %3u\n", (unsigned int)(address>>16));
#if ENABLE_DOS
        if (drive_read(1, buffer, BUFFER_SIZE) != BUFFER_SIZE) {
            printf("\nRead error."); /* TODO: error detail. */
            cbm_close(1);
            return false;
        }
#endif
#if ENABLE_RAMLINK
        ramlink_reu_copy(address, buffer, BUFFER_SIZE, REU_COMMAND_C64_TO_REU);
#endif
    }
    
    gotox(0);
    printf("Loading RAMLink from disk: %3u\n", (unsigned int)(address>>16));
    
#if ENABLE_DOS
    cbm_close(1);
#endif

    return true;
}

