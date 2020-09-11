#ifndef HAD_ULTIMATE_DOS_H
#define HAD_ULTIMATE_DOS_H

/*
  dos.h -- Public header for DOS target.
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

#define ULTIMATE_DOS_OPEN_READ 0x01
#define ULTIMATE_DOS_OPEN_WRITE 0x02
#define ULTIMATE_DOS_OPEN_CREATE_NEW 0x04
#define ULTIMATE_DOS_OPEN_CREATE_ALWAYS 0x08

#define ULTIMATE_DOS_STATUS_OK 0
#define ULTIMATE_DOS_SATTUS_DIRECTORY_EMPTY 1
#define ULTIMATE_DOS_SATTUS_REQUEST_TRUNCATED 2
#define ULTIMATE_DOS_SATTUS_NO_SUCH_DIRECTORY 83
#define ULTIMATE_DOS_SATTUS_NO_FILE_TO_CLOSE 84
#define ULTIMATE_DOS_SATTUS_NO_FILE_OPEN 85
#define ULTIMATE_DOS_SATTUS_CANNOT_READ_DIRECTORY 86

struct ultimate_dos_file_info {
    unsigned long size;
    unsigned int date;
    unsigned int time;
    unsigned char extension[3];
    unsigned char attributes;
    unsigned char filename[1];
};
typedef struct ultimate_dos_file_info ultimate_dos_file_info_t;

/*
    TODO: missing commands:
    - unsigend char ultimate_dos_open_dir(unsigned char instance);
    - XXX ultimate_dos_read_dir(unsigned char instance);
*/


/*
  Change to directory.
  Returns status.
*/
unsigned char ultimate_dos_change_dir(unsigned char instance, const unsigned char *name);

/*
  Closes currently open file.
  Returns status.
*/
unsigned char ultimate_dos_close_file(unsigned char instance);

unsigned char ultimate_dos_copy_file(unsigned char instance, const unsigned char *old_name, const unsigned char *new_name);

/*
  Change to home directory.
  Returns current directory, NULL on error.
*/
const unsigned char *ultimate_dos_copy_home_path(unsigned char instance);

/*
  Change to directory currently selected in UI.
  This function is deprecated.
  Returns current directory, NULL on error.
*/
const unsigned char *ultimate_dos_copy_ui_path(unsigned char instance);

unsigned char ultimate_dos_create_dir(unsigned char instance, const unsigned char *name);

unsigned char ultimate_dos_delete_file(unsigned char instance, const unsigned char *name);

const ultimate_dos_file_info_t *ultimate_dos_file_info(unsigned char instance);

const ultimate_dos_file_info_t *ultimate_dos_file_stat(unsigned char instance, const unsigned char *filename);

/*
  Seeks currently open file to position.
  Returns status.
*/
unsigned char ultimate_dos_file_seek(unsigned char instance, unsigned long position);

/*
  Get current directory.
  Returns current directory, NULL on error.
*/
const unsigned char *ultimate_dos_get_path(unsigned char instance);

/*
  Get DOS identification string.
  Returns NUL-terminated string, NULL if DOS target is not present.
*/
const unsigned char *ultimate_dos_identify(unsigned char instance);


unsigned char ultimate_dos_load_reu(unsigned char instance, unsigned long address, unsigned long length);

/*
  Opens file. See ULTIMATE_DOS_OPEN_* for mode bits.
  Returns status.
*/
unsigned char ultimate_dos_open_file(unsigned char instance, const unsigned char *name, unsigned char mode);

/*
  Read data from open file into buffer.
  Returs the number of bytes read.
*/
unsigned int ultimate_dos_read_data(unsigned char instance, unsigned char *buffer, unsigned int length);

unsigned char ultimate_dos_rename_file(unsigned char instance, const unsigned char *old_name, const unsigned char *new_name);

unsigned char ultimate_dos_save_reu(unsigned char instance, unsigned long address, unsigned long length);

/*
  Writes data from buffer into open file.
  Returns status.
*/
unsigned char ultimate_dos_write_data(unsigned char instance, const unsigned char *buffer, unsigned int length);

#endif /* HAD_ULTIMATE_DOS_H */
