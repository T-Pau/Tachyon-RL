/*
  dos-file-stat.c -- Get information for file.
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

#include "dos-internal.h"

#include <stddef.h>

const ultimate_dos_file_info_t *ultimate_dos_file_stat(unsigned char instance, const unsigned char *filename) {
    unsigned int length;

    ULTIMATE_CI.command = instance;
    ULTIMATE_CI.command = ULTIMATE_DOS_CMD_FILE_STAT;
    ultimate_ci_write_string(filename);
    if (ultimate_ci_execute() != 0) {
        return NULL;
    }
    length = ultimate_ci_read(ultimate_dos_buffer, ULTIMATE_DOS_BUFFER_LENGTH);

    if (length < 12) {
        return NULL;
    }

    ultimate_dos_buffer[length] = '\0';
    ultimate_ci_ascii2pet(ultimate_dos_buffer + offsetof(ultimate_dos_file_info_t, filename), length - offsetof(ultimate_dos_file_info_t, filename));
    return (ultimate_dos_file_info_t *)ultimate_dos_buffer;
}
