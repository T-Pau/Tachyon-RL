/*
  ci-read.c -- Read response data.
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

unsigned int ultimate_ci_read(unsigned char *data, unsigned int length) {
    unsigned int i = 0;

    while (ULTIMATE_CI.control & ULTIMATE_CI_STATE_DATA_LAST) {
        while (ULTIMATE_CI.control & ULTIMATE_CI_DATA_AV) {
            data[i] = ULTIMATE_CI.response;
            i++;
            if (i == length) {
                return i;
            }
        }
        ULTIMATE_CI.control = ULTIMATE_CI_DATA_ACC;
        while ((ULTIMATE_CI.control & ULTIMATE_CI_STATE_MASK) == ULTIMATE_CI_STATE_BUSY) {
            ;
        }
    }

    return i;
}
