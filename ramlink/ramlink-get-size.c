/*
  ramlink-get-size.c -- Get size of RAMLink.
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

#include <string.h>

static unsigned char block[256];
static unsigned char signature[] = {
	0x01, 0x01, 0xff, 0x00, 0x00, 0x53, 0x59, 0x53, 0x54, 0x45, 0x4d, 0xa0
};

unsigned long ramlink_get_size(void) {
	unsigned char i = 0;
	unsigned long size;

	if (!ramlink_detect()) {
		return 0;
	}

	if (ramlink_copy_block(255, 1, 0, block, RAMLINK_JOB_READ) != 0) {
		return 0;
	}

	while (i < sizeof(signature)) {
		if (block[i] != signature[i]) {
			return 0;
		}
		++i;
	}

	size = (((unsigned long)block[22] << 16) | ((unsigned int)block[23] << 8) | block[24]) + 0x1000;

	return size;
}
