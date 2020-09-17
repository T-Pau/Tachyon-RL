#ifndef HAD_ULTIMATE_CONTROL_H
#define HAD_ULTIMATE_CONTROL_H

/*
 net.h -- Public header for Networking target.
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

#define ULTIMATE_CONTROL_IDENTIFY       0x01
#define ULTIMATE_CONTROL_READ_RTC       0x02
#define ULTIMATE_CONTROL_FINISH_CAPTURE 0x03
#define ULTIMATE_CONTROL_FREEZE         0x05
#define ULTIMATE_CONTROL_REBOOT         0x06
#define ULTIMATE_CONTROL_LOAD_REU       0x08
#define ULTIMATE_CONTROL_SAVE_REU       0x09
#define ULTIMATE_CONTROL_U64_SAVEMEM    0x0F
#define ULTIMATE_CONTROL_DECODE_TRACK   0x11
#define ULTIMATE_CONTROL_ENCODE_TRACK   0x12
#define ULTIMATE_CONTROL_EASYFLASH      0x20
#define ULTIMATE_CONTROL_GET_HWINFO     0x28
#define ULTIMATE_CONTROL_ENABLE_DISK_A  0x30
#define ULTIMATE_CONTROL_DISABLE_DISK_A 0x31
#define ULTIMATE_CONTROL_ENABLE_DISK_B  0x32
#define ULTIMATE_CONTROL_DISABLE_DISK_B 0x33
#define ULTIMATE_CONTROL_DISK_A_POWER   0x34
#define ULTIMATE_CONTROL_DISK_B_POWER   0x35

#endif /* HAD_ULTIMATE_CONTROL_H */
