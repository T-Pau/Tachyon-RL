/*
 drive-detect.c -- Detect type of all connected drives.
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

#include <string.h>

struct pattern {
    uint8_t type;
    uint8_t len;
    char str[6];
};

static struct pattern prefix[] = {
    { DRIVE_TYPE_CMD_FD, 6, "cmd fd" },
    { DRIVE_TYPE_CMD_HD, 6, "cmd hd" },
    { DRIVE_TYPE_RAMDRIVE, 6, "cmd rd" },
    { DRIVE_TYPE_RAMLINK, 6, "cmd rl" },
    { DRIVE_TYPE_SD2IEC, 6, "sd2iec" },
    { DRIVE_TYPE_IDESERV, 6, " idese" },
    { DRIVE_TYPE_NLQ_HD, 5, "nlqhd" }
};

static struct pattern suffix[] = {
    { DRIVE_TYPE_1541, 5, " 1541" },
    { DRIVE_TYPE_1570, 5, " 1570" },
    { DRIVE_TYPE_1571, 5, " 1571" },
    { DRIVE_TYPE_1581, 5, " 1581" },
    { DRIVE_TYPE_IDE64, 6, " ide64" }
};

uint8_t drive_types[32];

void drive_detect(void) {
    const char *identifier;
    uint8_t id = 0;
    uint8_t len, i, j, match;
    
    while (id < 32) {
        drive_types[id] = DRIVE_TYPE_NONE;
        ++id;
    }
    
    for (id = 8; id < 17; ++id) {
        if ((identifier = drive_identify(id)) != NULL) {
            len = strlen(identifier);

            match = 0;

            for (i = 0; match == 0 && i < sizeof(prefix) / sizeof(prefix[0]); ++i) {
                if (len < prefix[i].len) {
                    continue;
                }
                
                match = 1;
                for (j = 0; j < prefix[i].len; ++j) {
                    if (identifier[j] != prefix[i].str[j]) {
                        match = 0;
                        break;
                    }
                }
                if (match) {
                    drive_types[id] = prefix[i].type;
                }
            }

            for (i = 0; match == 0 && i < sizeof(suffix) / sizeof(suffix[0]); ++i) {
                if (len < suffix[i].len) {
                    continue;
                }
                
                match = 1;
                for (j = 0; j < suffix[i].len; ++j) {
                    if (identifier[len - suffix[i].len + j] != suffix[i].str[j]) {
                        match = 0;
                        break;
                    }
                }
                if (match) {
                    drive_types[id] = suffix[i].type;
                }
            }
            
            if (match == 0) {
                drive_types[id] = DRIVE_TYPE_UNKNOWN;
            }
        }
    }
}
