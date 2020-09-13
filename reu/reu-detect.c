/*
  reu-detect.c -- Detect REU and get size.
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

#include "reu.h"

unsigned int reu_detect(void) {
	static unsigned char backup[256];
	unsigned char buffer[1];
	unsigned char bank;
	unsigned char value;
	unsigned int size;

	REU.reu_address = 0;
	REU.length = 1;

	/* back up first byte of each bank */
	bank = 0;
	do {
		REU.c64_address = backup + bank;
        REU.reu_bank = bank;
		REU.command = REU_COMMAND_DEFAULT | REU_COMMAND_REU_TO_C64;
		++bank;
	} while (bank != 0);

    /* see if REU is present at all */
    buffer[0] = backup[0] ^ 0xff;
    REU.c64_address = buffer;
    REU.reu_bank = 0;
	REU.command = REU_COMMAND_DEFAULT | REU_COMMAND_REU_TO_C64;
    if (buffer[0] != backup[0]) {
        return 0;
    }

	/* write bank number to first byte of each bank */
	REU.c64_address = buffer;
	bank = 0;
	do {
		buffer[0] = bank;
		REU.reu_bank = bank;
		REU.command = REU_COMMAND_DEFAULT | REU_COMMAND_C64_TO_REU;
		++bank;
	} while (bank != 0);

	size = 256;
	/* read back bank number from first byte of each bank */
	bank = 0;
	do {
		REU.reu_bank = bank;
		REU.command = REU_COMMAND_DEFAULT | REU_COMMAND_REU_TO_C64;
		//printf("bank %02x read %02x\n", bank, buffer[0]);
		if (bank == 0) {
			value = buffer[0];
		}
		else if (buffer[0] != value) {
			size = bank;
			break;
		}
		++value;
		++bank;
	} while (bank != 0);

	/* restore first byte of each bank */
	bank = 0;
	do {
		REU.c64_address = (backup + bank);
        REU.reu_bank = bank;
		REU.command = REU_COMMAND_DEFAULT | REU_COMMAND_C64_TO_REU;
		++bank;
	} while (bank != 0);

	return size;
}
