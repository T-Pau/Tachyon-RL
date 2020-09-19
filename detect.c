/*
  detect.c -- Detect hardware.
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

#include <c64.h>
#include <conio.h>
#include <ctype.h>
#include <stdio.h>

#include "ramlink/ramlink.h"
#include "reu/reu.h"
#include "ultimate/dos.h"

unsigned char dos;
unsigned long ramlink_size;
unsigned char ramlink_device;
unsigned long reu_size;
unsigned char sd2iec_device;

#define OK 0
#define WARNING 1
#define ERROR 2

static void print_size(unsigned long size);

unsigned char detect(void) {
    const char *string;
    unsigned char state = OK;
    unsigned char key;
    unsigned char i;

    ramlink_device = 0;
    sd2iec_device = 0;

    drive_detect();

    for (i = 8; i < 32; ++i) {
        if (drive_types[i] == DRIVE_TYPE_RAMLINK) {
            ramlink_device = i;
            break;
        }
        else if (drive_types[i] == DRIVE_TYPE_SD2IEC) {
            sd2iec_device = i;
        }
    }

    printf("RAMLink:  ");
	if ((ramlink_size = ramlink_get_size()) == 0) {
        textcolor(COLOR_LIGHTRED);
		printf("not found\n");
        state = ERROR;
	}
    else {
        if (ramlink_device == 0) {
            textcolor(COLOR_YELLOW);
            printf("device not found, ");
        }
        else {
            textcolor(COLOR_LIGHTGREEN);
            printf("#%u, ", ramlink_device);
        }
        textcolor(COLOR_LIGHTGREEN);
        print_size(ramlink_size);
        printf("\n");
    }
    textcolor(COLOR_GRAY3);

	printf("Ultimate: ");
	if ((string = ultimate_dos_identify(1)) == NULL) {
        if (sd2iec_device == 0) {
            textcolor(COLOR_LIGHTRED);
            state = ERROR;
        }
        else {
            textcolor(COLOR_YELLOW);
            state = WARNING;
        }
		printf("not found\n");
        dos = 0;
        reu_size = 0;
        
        textcolor(COLOR_GRAY3);
        printf("SD2IEC:   ");
        if (sd2iec_device == 0) {
            textcolor(COLOR_LIGHTRED);
            printf("not found\n");
        }
        else {
            textcolor(COLOR_LIGHTGREEN);
            printf("#%u\n", sd2iec_device);
        }
        textcolor(COLOR_GRAY3);
        printf("\n");
	}
    else {
        textcolor(COLOR_LIGHTGREEN);
    	printf("%s\n", string);
        dos = 1;
        
        printf("REU:      ");
        if ((reu_size = (unsigned long)reu_detect() << 16) == 0) {
            textcolor(COLOR_YELLOW);
            printf("not found\n");
            if (state == OK) {
                state = WARNING;
            }
        }
        else {
            textcolor(COLOR_LIGHTGREEN);
            print_size(reu_size);
            printf("\n");
        }
        textcolor(COLOR_GRAY3);
    }

    printf("\n");
#if ENABLE_RAMLINK
    if (ramlink_size == 0) {
        /*      0123456789012345678901234567890123456789 */
        printf("Please make sure your RAMLink is\n");
        printf("connected and enabled.\n\n");
    }
#endif
    
#if ENABLE_DOS
    if (dos == 0) {
        if (sd2iec_device == 0) {
            /*      0123456789012345678901234567890123456789 */
            printf("If you have an Ultimate, make sure it is");
        }
        else {
            printf("Please make sure your Ultimate is\n");
        }
        printf("connected to the Pass-Thru Port of your\n");
        printf("RAMLink and that the Command Interface\n");
        /*      0123456789012345678901234567890123456789 */
        printf("is enabled: Press the Menu button then\n");
        printf("press F2. Select \"C64 and Cartridge\n");
        printf("Settings\" and enable \"Command\n");
        printf("Interface\".");
        /*      0123456789012345678901234567890123456789 */
        
        if (sd2iec_device == 0) {
            printf(" Backing up to Ultimate is\n");
            printf("much faster than to SD2IEC.\n\n");
            /*      0123456789012345678901234567890123456789 */
            printf("If you have an SD2IEC, make sure it is\n");
            printf("connected.\n\n");
            
            textcolor(COLOR_WHITE);
            printf("No suitable backup device found.\n\n");
            textcolor(COLOR_GRAY3);
        }
        else {
            printf("\n\n");
        }
    }
#endif
#if ENABLE_REU
    if (dos == 1 && reu_size == 0) {
        /*      0123456789012345678901234567890123456789 */
        printf("Tachyon RL is much faster if it can\n");
        printf("use the Ultimate's RAM Expansion Unit.\n");
        printf("Press the Menu button, then F2. Select\n");
        /*      0123456789012345678901234567890123456789 */
        printf("\"C64 and Cartridge Settings\" and\n");
        printf("enable \"RAM Expansion Unit\". A REU\n");
        printf("Size of 16 MB is best.\n\n");
        /*      0123456789012345678901234567890123456789 */
    }
#endif

    switch (state) {
    case OK:
        return 0;
        
    case WARNING:
        printf("(C)ontinue, (R)echeck, or (H)elp.\n");
        do {
            key = tolower(cgetc());
        } while (key != 'c' && key != 'r' && key != 'h');
        if (key == 'c') {
            return 0;
        }
        break;
        
    case ERROR:
        printf("(H)elp or any other key to recheck.");
        key = tolower(cgetc());
        break;
    }
    
    if (key == 'h') {
        help();
    }
    return 1;
}


static void print_size(unsigned long size) {
    if ((size & 0xfffff) == 0) {
        printf ("%lu MB", (size >> 20));
    }
    else if ((size & 0x3ff) == 0) {
        printf("%lu KB", (size >> 10));
    }
    else {
        printf("%lu bytes", size);
    }
}
