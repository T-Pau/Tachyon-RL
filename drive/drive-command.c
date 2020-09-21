/*
 drive-command.c -- Send command to drive and read response (text only).
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

#include "drive.h"

#include <cbm.h>
#include <errno.h>

const char *drive_command(uint8_t id, const char *command) {
    static char buffer[256];
    static uint8_t i;
    
    if (cbm_open(15, id, 15, command) != 0) {
        i = _oserror;
        cbm_close(15);
        _oserror = i;
        return NULL;
    }
    
    if ((i = cbm_k_chkin(15)) != 0) {
        cbm_close(15);
        _oserror = i;
        return NULL;
    }
    
    i = 0;
    while (i < 254) {
        buffer[i] = cbm_k_basin();
        if (buffer[i] == 0x0d) {
            break;
        }
        ++i;
    }
        
    buffer[i] = '\0';
        
    cbm_k_clrch();
    cbm_close(15);
    
    return buffer;
}
