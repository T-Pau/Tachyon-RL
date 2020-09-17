/*
  dos-get-time.c -- Get date and time.
  Copyright (C) 2020 Dieter Baron

  This file is part of ultimate, a cc65 implementation of the
  Ultimate II command interface.
  The authors can be contacted at <ultimate@tpau.group>.

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

#include "dos-internal.h"

#include <stdlib.h>

struct tm *ultimate_dos_get_time(void) {
    static struct tm tm;
    
    const unsigned char *timestr;
    
    ULTIMATE_CI.command = 1;
    ULTIMATE_CI.command = ULTIMATE_DOS_CMD_GET_TIME;
    ULTIMATE_CI.command = 1;

    if ((timestr = ultimate_dos_get_string()) == NULL) {
        return NULL;
    }
    
    switch (timestr[1]) {
        case 'U':
            if (timestr[0] == 'S') {
                tm.tm_wday = 0;
            }
            else {
                tm.tm_wday = 2;
            }
            break;
            
        case 'O':
            tm.tm_wday = 1;
            break;
            
        case 'E':
            tm.tm_wday = 3;
            break;
            
        case 'H':
            tm.tm_wday = 4;
            break;
            
        case 'R':
            tm.tm_wday = 5;
            break;
            
        case 'A':
            tm.tm_wday = 6;
            break;
            
        default:
            return NULL;
            
    }
    
    tm.tm_year = atoi(timestr + 4) - 1900;
    tm.tm_mon = atoi(timestr + 9) - 1;
    tm.tm_mday = atoi(timestr + 12);
    tm.tm_hour = atoi(timestr + 15);
    tm.tm_min = atoi(timestr + 18);
    tm.tm_sec = atoi(timestr + 21);
    
    return &tm;
}
