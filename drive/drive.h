#ifndef HAD_DRIVE_H
#define HAD_DRIVE_H

/*
 drive.h -- Accessing (serial) drives.
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

#include <stdbool.h>
#include <stdint.h>

#define DRIVE_TYPE_NONE 0
#define DRIVE_TYPE_1541 1
#define DRIVE_TYPE_1570 2
#define DRIVE_TYPE_1571 3
#define DRIVE_TYPE_1581 4
#define DRIVE_TYPE_CMD_FD 5
#define DRIVE_TYPE_CMD_HD 6
#define DRIVE_TYPE_RAMDRIVE 7
#define DRIVE_TYPE_RAMLINK 8
#define DRIVE_TYPE_SD2IEC 9
#define DRIVE_TYPE_IDE64 10
#define DRIVE_TYPE_IDESERV 11
#define DRIVE_TYPE_UNKNOWN 127

extern uint8_t drive_types[32];

const char *drive_command(uint8_t id, const char *command);
void drive_detect(void);
const char *drive_identify(uint8_t id);
uint16_t drive_read(uint8_t id, uint8_t *buffer, uint32_t length);
uint16_t drive_write (uint8_t file, const uint8_t *data, uint16_t length);

#endif /* HAD_DRIVE_H */
