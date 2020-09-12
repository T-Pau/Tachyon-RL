#ifndef HAD_ULTIMATE_CI_H
#define HAD_ULTIMATE_CI_H

/*
  ci.h -- Public header for command interface.
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

#define ULTIMATE_CI_ciR_ERR 0x80
#define ULTIMATE_CI_ABORT 0x40
#define ULTIMATE_CI_DATA_ACC 0x2
#define ULTIMATE_CI_PUSH_CMD 0x1

#define ULTIMATE_CI_DATA_AV 0x80
#define ULTIMATE_CI_STAT_AV 0x40
#define ULTIMATE_CI_STATE_MASK 0x30
#define ULTIMATE_CI_STATE_IDLE 0x00
#define ULTIMATE_CI_STATE_BUSY 0x10
#define ULTIMATE_CI_STATE_DATA_LAST 0x20
#define ULTIMATE_CI_STATE_DATA_MORE 0x30
#define ULTIMATE_CI_ERROR 0x08
#define ULTIMATE_CI_CMD_BUSY 0x01

#define ULTIMATE_CI_STATUS_OK 0x00
#define ULTIMATE_CI_STATUS_ERROR 0xff /* error without numeric code */

struct ultimate_ci_registers {
    unsigned char control;
    unsigned char command;
    unsigned char response;
    unsigned char status;
};

#define ULTIMATE_CI (*(struct ultimate_ci_registers *)0xdf1c)

extern unsigned char ultimate_ci_status_code;
extern unsigned char ultimate_ci_status[];
extern unsigned char ultimate_ci_status_length;

#define ultimate_ci_write_char(c) \
	(ULTIMATE_CI.command = (c))

#define ultimate_ci_write_int(i) \
	(ULTIMATE_CI.command = (i) & 0xff, \
	 ULTIMATE_CI.command = (i) >> 8)

#define ultimate_ci_write_long(l) \
	(ULTIMATE_CI.command = (l) & 0xff, \
	 ULTIMATE_CI.command = ((l) >> 8) & 0xff, \
	 ULTIMATE_CI.command = ((l) >> 16) & 0xff, \
	 ULTIMATE_CI.command = (l) >> 24)

/*
 Detect wether Ultimate CI is available.
 Returns 1 if present, 0 if not.
*/
unsigned char ultimate_ci_detect(void);

/*
  End command.
  This discards all remaining data and puts CI in idle state.
*/
void ultimate_ci_done(void);

/*
  Execute command written.
  Reads status into ultimate_ci_status and NUL-terminates it.
  Returns 0 if status is empty or "00", 1 otherwise.
*/
unsigned char ultimate_ci_execute(void);

/*
  Read at most `length` bytes of response data into `data`.
  Returns the number of bytes read.
*/
unsigned int ultimate_ci_read(unsigned char *data, unsigned int length);

/*
  Write command data.
*/
void ultimate_ci_write(const unsigned char *data, unsigned int length);

/*
  Write NUL-terminated string to command data, converting to ASCII.
*/
void ultimate_ci_write_string(const unsigned char *data);

/*
  Convert from ASCII to PETSCII.
*/
void ultimate_ci_ascii2pet(unsigned char *s, unsigned int len);

#endif /* HAD_ULTIMATE_CI_H */
