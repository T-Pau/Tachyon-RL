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

#include "ramlink/ramlink.h"
#include "reu/reu.h"
#include "ultimate/ci.h"
#include "ultimate/dos.h"

/* disable operations for profiling */
#define ENABLE_DOS 1
#define ENABLE_RAMLINK 1
#define ENABLE_REU 1

extern unsigned char dos;
extern unsigned long ramlink_size;
extern unsigned long reu_size;

#define BUFFER_SIZE (16*1024)

extern unsigned char buffer[BUFFER_SIZE];
extern unsigned char filename[];

extern const char *help_screen;

#define ramlink_pages (*(unsigned int *)((unsigned char *)&ramlink_size + 1))
#define reu_pages (*(unsigned int *)((unsigned char *)&reu_size + 1))

unsigned char backup(void);
unsigned char backup_dos(void);
unsigned char backup_reu(void);
unsigned char backup_reu_dma(void);
unsigned char detect(void);
void help(void);
unsigned char restore(void);
unsigned char restore_dos(void);
unsigned char restore_reu(void);
unsigned char restore_reu_dma(void);

#endif /* HAD_TACHYON_H */
