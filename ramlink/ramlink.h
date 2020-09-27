#ifndef HAD_RAMLINK_H
#define HAD_RAMLINK_H

/*
  ramlink.h -- Public header file.
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

#include <stdbool.h>
#include <stdint.h>

#include "../reu/reu.h"

#define RAMLINK_JOB_READ 0x80
#define RAMLINK_JOB_WRITE 0x90
#define RAMLINK_JOB_VERIFY 0xa0
#define RAMLINK_JOB_SWAP 0xb0

#define RAMLINK_ERROR_OK 0x00
#define RAMLINK_ERROR_VERIFY 0x02
#define RAMLINK_ERROR_ILLEGAL_BLOCK 0x04
#define RAMLINK_ERROR_ILLEGAL_PARTITION 0x0f

struct ramlink_block_registers {
	unsigned char job;
	unsigned char track;
	unsigned char sector;
	unsigned int c64_address;
	unsigned char partition;
	unsigned char c128_bank;
};

#define RAMLINK_PARTITION_UNUSED 0x00
#define RAMLINK_PARTITION_NATIVE 0x01
#define RAMLINK_PARTITION_D64 0x02
#define RAMLINK_PARTITOIN_D71 0x03
#define RAMLINK_PARTITOIN_D81 0x04
#define RAMLINK_PARTITOIN_SYSTEM 0xff

struct ramlink_partition_entry {
    unsigned char next_track;
    unsigned char next_sector;
    unsigned char type;
    unsigned char reserved[2];
    unsigned char name[16];
    unsigned char reserved1;
    unsigned int offset; /* 256 byte blocks, big endian! */
    unsigned char reserved2[6];
    unsigned int size; /* 256 byte blocks, big endain! */
};

typedef struct ramlink_partition_entry ramlink_partition_entry_t;

#define ramlink_reu_enable() (asm("jsr $e0a9"))
#define ramlink_reu_execute_and_disable() (asm("jsr $fe1e"))
#define ramlink_reu_execute_block() (asm("jsr $fe09"))
#define ramlink_reu_disable() (asm("jsr $fe0c"))

#define RAMLINK_REU (*(struct reu_registers *)0xde00)
#define RAMLINK_BLOCK (*(struct ramlink_block_registers *)0xde20)

/* Where RAMLink maps in a page of its RAM. */
#define RAMLINK_DATA ((unsigned char *)0xde00)

/* Which page to map in */
#define RAMLINK_PAGE (*(unsigned int *)0xdfa0)

#define ramlink_activate() (asm("sta $df7e"))
#define ramlink_deactivate() (asm("sta $df7f"))
#define ramlink_show_registers() (asm("sta $dfc0"))
#define ramlink_show_data() (asm("sta $dfc1"))

void ramlink_reu_dma(unsigned char mode, unsigned int ramlink_page, unsigned int reu_page, unsigned int length);
void ramlink_reu_copy(unsigned long ramlink_address, void *c64_address, unsigned int length, unsigned char mode);
unsigned char ramlink_copy_block(unsigned char partition, unsigned char track, unsigned char sector, void *c64_address, unsigned char job);
bool ramlink_detect(void);
unsigned long ramlink_get_size(uint8_t device_id);
struct tm *ramlink_get_time(unsigned char device);

#endif /* HAD_RAMLINK_H */
