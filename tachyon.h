#ifndef HAD_TACHYON_H
#define HAD_TACHYON_H

/*
  tachyon-rl.h -- Main header file.
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

#include <c64.h>

#include "drive/drive.h"
#include "ramlink/ramlink.h"
#include "reu/reu.h"
#include "ultimate/ci.h"
#include "ultimate/dos.h"

/* disable operations for profiling */
#define ENABLE_DOS 1
#define ENABLE_RAMLINK 1
#define ENABLE_REU 1

#define VERSION "1.1"

enum {
    CPU_C64,
    CPU_C128,
    CPU_SUPERCPU_V1,
    CPU_SUPERCPU_V2
};

enum {
    METHOD_NONE,
    METHOD_ULTIMATE,
    METHOD_ULTIMATE_REU,
    METHOD_SD2IEC
};

extern bool dos;
extern uint32_t ramlink_size;
extern uint8_t ramsize_device;
extern uint32_t reu_size;
extern uint8_t sd2iec_device;
extern uint8_t method;
extern uint8_t cpu;
extern uint8_t cpu_speed;

#define BUFFER_SIZE (16*1024)

extern uint8_t buffer[BUFFER_SIZE];
extern unsigned char filename[];

extern const char *help_screen;

#define ramlink_pages (*(unsigned int *)((unsigned char *)&ramlink_size + 1))
#define reu_pages (*(unsigned int *)((unsigned char *)&reu_size + 1))

#define c128_1mhz() \
    (*(uint8_t *)0xd030 = 0x0, \
     VIC.ctrl1 = VIC.ctrl1 | 0x10)

#define c128_2mhz() \
    (VIC.ctrl1 = VIC.ctrl1 & 0xef, \
     *(uint8_t *)0xd030 = 0x1)

bool backup(void);
bool backup_dos(void);
bool backup_reu(void);
bool backup_reu_dma(void);
bool backup_sd2iec(void);
bool detect(void);
void detect_cpu(void);
void help(void);
bool restore(void);
bool restore_dos(void);
bool restore_reu(void);
bool restore_reu_dma(void);
bool restore_sd2iec(void);

#endif /* HAD_TACHYON_H */
