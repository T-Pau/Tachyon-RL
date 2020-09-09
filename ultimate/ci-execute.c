/*
  ci-execute.c -- Execute command and read status.
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

#include "ci.h"

unsigned char ultimate_ci_execute(void) {
    /* push command */
    ULTIMATE_CI.control = ULTIMATE_CI_PUSH_CMD;

    /* wait for command to finish */
    while ((ULTIMATE_CI.control & ULTIMATE_CI_STATE_MASK) == ULTIMATE_CI_STATE_BUSY) {
        ;
    }

    /* read status */
    ultimate_ci_status_length = 0;
    while (ULTIMATE_CI.control & ULTIMATE_CI_STAT_AV) {
        ultimate_ci_status[ultimate_ci_status_length] = ULTIMATE_CI.status;
        ++ultimate_ci_status_length;
    }
    ultimate_ci_status[ultimate_ci_status_length] = '\0';

    if (ultimate_ci_status_length < 2) {
        return 0;
    }
    ultimate_ci_status_code = (ultimate_ci_status[0] - '0') * 10 + (ultimate_ci_status[1] - '0');
    return ultimate_ci_status_code;
}
