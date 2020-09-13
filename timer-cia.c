/*
  timer-cia1.c -- Use realtime clock from CIA1 as timer.
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

#include "timer.h"

#include <cbm.h>

#include <stdio.h>

static void output_bcd(unsigned char value);
static void output_bcd_single(unsigned char value);

void timer_start(void) {
	unsigned char x;
	CIA1.tod_hour = 0;
	CIA1.tod_10 = 0;
	CIA1.tod_min = 0;
	CIA1.tod_sec = 0;
	x = CIA1.tod_10;
}

void timer_stop(void) {
	unsigned char x;
	x = CIA1.tod_hour;
	CIA1.tod_hour = x;
}

void timer_output(void) {
	output_bcd(CIA1.tod_hour);
	putchar(':');
	output_bcd(CIA1.tod_min);
	putchar(':');
	output_bcd(CIA1.tod_sec);
	putchar('.');
	output_bcd_single(CIA1.tod_10);
}

static void output_bcd(unsigned char value) {
	putchar((value >> 4) | 0x30);
	putchar((value & 0xf) | 0x30);
}

static void output_bcd_single(unsigned char value) {
	putchar((value & 0xf) | 0x30);
}
