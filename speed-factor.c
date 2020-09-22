/*
 speed-factor.c -- Speed matrix for backup methods and CPUs.
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

uint16_t speed_factor[] = { /* ms/64k */
    /* Ultimate */
    3831, /* 1Mhz */
    0, /* 2Mhz */
    1488, /* SuperCPU V1 20Mhz */
    0, /* SuperCPU V2 20Mhz */

    /* Ultimate + REU */
    1756, /* 1Mhz */
    0, /* 2Mhz */
    0281, /* SuperCPU V1 20Mhz */
    0234, /* SuperCPU V2 20Mhz */

    /* SD2IEC */
    16963, /* 1Mhz */
    0, /* 2Mhz */
    14163, /* SuperCPU V1 20Mhz */
    0, /* SuperCPU V2 20Mhz */
};
