/*
  ramlink-reu-dma.c -- Copy page from RAMLink to REU in RAM Port.
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

#include "ramlink.h"

#include "../reu/reu.h"

#define REU_PAGE (*(unsigned int *)0xdf05)

void ramlink_reu_dma(unsigned char mode, unsigned int ramlink_page_, unsigned int reu_page_, unsigned int num_pages) {
	static unsigned char command;
    static unsigned int ramlink_page;
    static unsigned int reu_page;
	static unsigned int end;

    ramlink_page = ramlink_page_;
    reu_page = reu_page_;
	command = REU_COMMAND_DEFAULT | mode;
	end = ramlink_page + num_pages;

	asm("sei");
	ramlink_activate();

    do {
        RAMLINK_PAGE = ramlink_page;
		ramlink_show_data();
        REU.c64_address = RAMLINK_DATA;
        REU.reu_address = reu_page & 0xff;
        REU.reu_bank = reu_page >> 8;
        REU.length = 256;
		REU.command = command;
		++ramlink_page;
        ++reu_page;
	} while (ramlink_page != end);

	ramlink_deactivate();
	asm("cli");
}
