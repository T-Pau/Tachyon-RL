#ifndef HAD_DOS_INTERNAL_H
#define HAD_DOS_INTERNAL_H

/*
  dos-internal.h -- Internal header.
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
#include "dos.h"

#define ULTIMATE_DOS_CMD_IDENTIFY 0x01
#define ULTIMATE_DOS_CMD_OPEN_FILE 0x02
#define ULTIMATE_DOS_CMD_CLOSE_FILE 0x03
#define ULTIMATE_DOS_CMD_READ_DATA 0x04
#define ULTIMATE_DOS_CMD_WRITE_DATA 0x05
#define ULTIMATE_DOS_CMD_FILE_SEEK 0x06
#define ULTIMATE_DOS_CMD_FILE_INFO 0x07
#define ULTIMATE_DOS_CMD_FILE_STAT 0x08
#define ULTIMATE_DOS_CMD_DELETE_FILE 0x09
#define ULTIMATE_DOS_CMD_RENAME_FILE 0x0a
#define ULTIMATE_DOS_CMD_COPY_FILE 0x0b
#define ULTIMATE_DOS_CMD_CHANGE_DIR 0x11
#define ULTIMATE_DOS_CMD_GET_PATH 0x12
#define ULTIMATE_DOS_CMD_OPEN_DIR 0x13
#define ULTIMATE_DOS_CMD_READ_DIR 0x14
#define ULTIMATE_DOS_CMD_COPY_UI_PATH 0x15
#define ULTIMATE_DOS_CMD_CREATE_DIR 0x16
#define ULTIMATE_DOS_CMD_COPY_HOME_PATH 0x17
#define ULTIMATE_DOS_CMD_LOAD_REU 0x21
#define ULTIMATE_DOS_CMD_SAVE_REU 0x22
#define ULTIMATE_DOS_CMD_MOUNT_DISK 0x23
#define ULTIMATE_DOS_CMD_UMOUNT_DISK 0x24
#define ULTIMATE_DOS_CMD_SWAP_DISK 0x25
#define ULTIMATE_DOS_CMD_GET_TIME 0x26
#define ULTIMATE_DOS_CMD_SET_TIME 0x27
#define ULTIMATE_DOS_CMD_ECHO 0xF0

extern unsigned char ultimate_dos_buffer[];

#define ULTIMATE_DOS_BUFFER_LENGTH 896

unsigned char *ultimate_dos_get_string(unsigned char instance, unsigned char command);

#endif /* HAD_DOS_INTERNAL_H */
