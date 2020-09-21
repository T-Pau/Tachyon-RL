/*
 detect_cpu.c -- Detect which CPU we're running on.
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

void detect_cpu(void) {
    if (((*(uint8_t *)0xd0bc) & 0x80) == 0) {
        if ((*(uint8_t *)0xd0b0) & 0x80) {
            cpu = CPU_SUPERCPU_V1;
        }
        else {
            cpu = CPU_SUPERCPU_V2;
        }
        
        if ((*(uint8_t *)0xd0b5) & 0x40) {
            cpu_speed = 1;
        }
        else {
            cpu_speed = 20;
        }
    }
    else if (*(uint8_t *)0xd030 == 0xfc) {
        cpu = CPU_C128;
        cpu_speed = 2;
    }
    else {
        cpu = CPU_C64;
        cpu_speed = 1;
    }
}
