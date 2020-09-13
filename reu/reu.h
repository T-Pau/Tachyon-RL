#ifndef HAD_REU_H
#define HAD_REU_H

/*
  reu.h -- Public header.
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

#define C64_TO_REU 0
#define REU_TO_C64 1

#define REU_COMMAND_EXECUTE 0x80
#define REU_COMMAND_AUTOLOAD 0x20
#define REU_COMMAND_FF00 0x10
#define REU_COMMAND_C64_TO_REU 0x0
#define REU_COMMAND_REU_TO_C64 0x1
#define REU_COMMAND_SWAP 0x2
#define REU_COMMAND_VERIFY 0x3

#define REU_COMMAND_DEFAULT (REU_COMMAND_EXECUTE | REU_COMMAND_AUTOLOAD | REU_COMMAND_FF00)

struct reu_registers {
	unsigned char status;
	unsigned char command;
	void *c64_address;
	unsigned int reu_address;
	unsigned char reu_bank;
	unsigned int length;
	unsigned char irq_mask;
	unsigned char address_control;
};

#define REU (*(struct reu_registers *)0xdf00)

void reu_copy(unsigned long reu_address, void *c64_address, unsigned int length, unsigned char mode);
unsigned int reu_detect(void);

#endif /* HAD_REU_H */
