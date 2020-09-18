/*
  ramlink-get-time.h -- Get date and time.
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

#include <cbm.h>

struct tm *ramlink_get_time(unsigned char device) {
    static struct tm tm;
    
    cbm_k_setlfs(15, device, 15);
    cbm_k_setnam("t-rd\r");
    cbm_k_open();
    cbm_k_chkin(15);

    tm.tm_wday = cbm_k_basin();
    tm.tm_year = cbm_k_basin();
    if (tm.tm_year < 70) {
        tm.tm_year += 100;
    }
    tm.tm_mon = cbm_k_basin() - 1;
    tm.tm_mday = cbm_k_basin();
    tm.tm_hour = cbm_k_basin();
    tm.tm_min = cbm_k_basin();
    tm.tm_sec = cbm_k_basin();
    if (cbm_k_basin()) {
        tm.tm_hour += 12;
    }
    
    cbm_k_clrch();
    cbm_k_close(15);

    return &tm;
}
