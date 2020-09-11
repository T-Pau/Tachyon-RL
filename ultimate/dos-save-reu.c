/*
  dos-save-reu.c -- Save data from REU to open file.
  Copyright (C) 2020 Dieter Baron

  This file is part of ultimate, a cc65 implementation of the
  Ultimate II command interface.
  The authors can be contacted at <ultimate@tpau.group>.

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

#include "dos-internal.h"

#include <stddef.h>

#define PART_SIZE ((unsigned long)8*1024*1024)

unsigned char ultimate_dos_save_reu(unsigned char instance, unsigned long address, unsigned long length) {
    if (length & 0xff000000) {
        if (address > 0) {
            --length;
        }
        else {
            ULTIMATE_CI.command = instance;
            ULTIMATE_CI.command = ULTIMATE_DOS_CMD_SAVE_REU;
            ultimate_ci_write_long(address);
            ultimate_ci_write_long(PART_SIZE);
            if (ultimate_ci_execute() != 0) {
                return ultimate_ci_status_code;
            }
            ultimate_ci_done();
            address += PART_SIZE;
            length -= PART_SIZE;
        }
    }

    ULTIMATE_CI.command = instance;
    ULTIMATE_CI.command = ULTIMATE_DOS_CMD_SAVE_REU;
    ultimate_ci_write_long(address);
    ultimate_ci_write_long(length);
    if (ultimate_ci_execute() != 0) {
        return ultimate_ci_status_code;
    }
    ultimate_ci_done();

    return 0;
}
