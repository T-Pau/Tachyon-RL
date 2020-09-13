/*
  backup-reu-dma.c -- DMA to REU at RAM Port.
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

#include <stdio.h>

unsigned char backup_reu_dma(void) {
    static unsigned int page;
    static unsigned int length;
    
    unsigned long length_bytes = ramlink_size;
    
    page = 0;
    length = ramlink_pages;
    if (length > reu_pages) {
        length = reu_pages;
        length_bytes = reu_size;
    }
    
    do {
        printf("Copying to REU.\n");
#if ENABLE_RAMLINK && ENABLE_REU
        ramlink_reu_dma(REU_COMMAND_C64_TO_REU, page, 0, length);
#endif
        printf("Saving REU.\n");
#if ENABLE_DOS
        if (ultimate_dos_save_reu(1, 0, length_bytes) != 0) {
            printf("\ncan't save REU:\n  %s\n", filename, ultimate_ci_status);
            return 1;
        }
#endif
        page += length;
    } while (page != ramlink_pages);
    
    return 0;
}
