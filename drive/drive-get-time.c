/*
  drive-get-time.h -- Get date and time.
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

struct tm *drive_get_time(uint8_t device) {
    static struct tm tm;
    static uint8_t i;

    if (drive_command(device, "tr-d") == NULL) {
        return NULL;
    }

    if (drive_response_length != 9 || drive_response[0] >= 7 || drive_response[2] >= 12) {
        return NULL;
    }
    
    tm.tm_wday = drive_response[0];
    tm.tm_year = drive_response[1];
    if (tm.tm_year < 70) {
        tm.tm_year += 100;
    }
    tm.tm_mon = drive_response[2] - 1;
    tm.tm_mday = drive_response[3];
    tm.tm_hour = drive_response[4];
    tm.tm_min = drive_response[5];
    tm.tm_sec = drive_response[6];
    if (drive_response[7]) {
        tm.tm_hour += 12;
    }
    
    return &tm;
}
