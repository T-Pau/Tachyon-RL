/*
  restore.c -- Run restore.
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

bool restore(void) {
    const ultimate_dos_file_info_t *file_info;
    unsigned char ret;
    
#if ENABLE_DOS
    if (method == METHOD_ULTIMATE_REU || method == METHOD_ULTIMATE) {
        if (ultimate_dos_open_file(1, filename, ULTIMATE_DOS_OPEN_READ) != 0) {
            printf("Can't open '%s':\n  %s\n", filename, ultimate_ci_status);
            return false;
        }
    
        if ((file_info = ultimate_dos_file_info(1)) == NULL) {
            printf("Can't get file info: %s\n", ultimate_ci_status);
            return false;
        }
        
        if (file_info->size < ramlink_size) {
            printf("File is too short (%lud bytes)\n", file_info->size);
            return false;
        }
        else if (file_info->size > ramlink_size) {
            printf("File is too long (%lud bytes)\n", file_info->size);
            return false;
        }
    }
#endif
    
    switch (method) {
        case METHOD_ULTIMATE:
            ret = restore_dos();
            break;
            
        case METHOD_ULTIMATE_REU:
            ret = restore_reu();
            break;

        case METHOD_SD2IEC:
            ret = restore_sd2iec();
            break;
            
        default:
            printf("Internal error: unknown backup method.\n");
            ret = false;
    }
    
#if ENABLE_DOS
    if (method == METHOD_ULTIMATE_REU || method == METHOD_ULTIMATE) {
        ultimate_dos_close_file(1);
    }
#endif
    
    return ret;
}
