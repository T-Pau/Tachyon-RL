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

bool dos;
bool ramlink;
uint32_t ramlink_size;
uint8_t ramlink_device;
uint32_t reu_size;
uint8_t sd2iec_device;
uint8_t cpu;
uint8_t cpu_speed;
uint8_t method;

uint8_t top_line;

enum {
    OK,
    WARNING,
    ERROR
};

static void print_size(unsigned long size);

bool detect(void) {
    const char *string;
    unsigned char state = OK;
    unsigned char key;
    unsigned char i;

    ramlink_device = 0;
    sd2iec_device = 0;
    method = METHOD_NONE;

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
    
    printf("\n");

    printf("RAMLink:  ");
    ramlink = ramlink_detect();
    if (!ramlink) {
        textcolor(COLOR_LIGHTRED);
        printf("not found\n");
        state = ERROR;
    }
    else if (ramlink_device == 0) {
        textcolor(COLOR_LIGHTRED);
        printf("device id not found\n");
        state = ERROR;
    }
    else {
        textcolor(COLOR_LIGHTGREEN);
        printf("Drive %u, ", ramlink_device);
        
        if ((ramlink_size = ramlink_get_size(ramlink_device)) == 0) {
            textcolor(COLOR_LIGHTRED);
            printf("missing system partition\n");
            state = ERROR;
        }
        else {
            textcolor(COLOR_LIGHTGREEN);
            print_size(ramlink_size);
            printf("\n");
        }
    }
    textcolor(COLOR_GRAY3);
    
    detect_cpu();
    printf("Computer: ");
    textcolor(COLOR_LIGHTGREEN);
    switch (cpu) {
    case CPU_C64:
        printf("C64");
        break;
        
    case CPU_C128:
        printf("C128");
        break;
        
    case CPU_SUPERCPU_V1:
    case CPU_SUPERCPU_V2:
        if (cpu_speed == 1) {
            textcolor(COLOR_YELLOW);
            state = WARNING;
        }
        printf("SuperCPU V%c", cpu == CPU_SUPERCPU_V1 ? '1' : '2');
        break;
    }
    printf(", %uMHz\n", cpu_speed);
    textcolor(COLOR_GRAY3);

	printf("Ultimate: ");
	if ((string = ultimate_dos_identify(1)) == NULL) {
        if (sd2iec_device == 0) {
            textcolor(COLOR_LIGHTRED);
            state = ERROR;
        }
        else {
            textcolor(COLOR_YELLOW);
            if (state == OK) {
                state = WARNING;
            }
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
            printf("Drive %u\n", sd2iec_device);
            method = METHOD_SD2IEC;
        }
        textcolor(COLOR_GRAY3);
	}
    else {
        textcolor(COLOR_LIGHTGREEN);
    	printf("%s\n", string);
        textcolor(COLOR_GRAY3);
        dos = 1;
        
        printf("REU:      ");
        if ((reu_size = (unsigned long)reu_detect() << 16) == 0) {
            textcolor(COLOR_YELLOW);
            printf("not found\n");
            if (state == OK) {
                state = WARNING;
            }
            method = METHOD_ULTIMATE;
        }
        else {
            textcolor(COLOR_LIGHTGREEN);
            print_size(reu_size);
            printf("\n");
            method = METHOD_ULTIMATE_REU;
        }
        textcolor(COLOR_GRAY3);
    }
    
    printf("\n");
    
    top_line = wherey();

    if (!ramlink) {
        /*      0123456789012345678901234567890123456789 */
        printf("Please make sure your RAMLink is\n");
        printf("connected and enabled.\n\n");
    }
    else if (ramlink_size == 0) {
        /*      0123456789012345678901234567890123456789 */
        printf("Your RAMLink seems to be corrupted. Turn");
        printf("off your computer and unplug RAMLink.\n\n");
    }

    if (cpu_speed == 1 && (cpu == CPU_SUPERCPU_V1 || cpu == CPU_SUPERCPU_V2)) {
        /*      0123456789012345678901234567890123456789 */
        printf("Set the speed of your SpuerCPU to Turbo.\n");
    }
    
    if (dos == 0) {
        /*      0123456789012345678901234567890123456789 */
        printf("If you have an Ultimate, connect it to\n");
        printf("RAMLink's Pass-Thru Port, set the lower\n");
        printf("switch to \05normal\x9b, and enable the\n");
        printf("\05Command Interface\x9b in Menu -> F2 ->\n");
        /*      0123456789012345678901234567890123456789 */
        printf("\"C64 and Cartridge Settings\".\n\n");
               
        if (sd2iec_device == 0) {
            /*      0123456789012345678901234567890123456789 */
            printf("If you have an SD2IEC, make sure it is\n");
            printf("connected.\n\n");
        }
        else {
            printf("\n\n");
        }
    }
    
    if (!ramlink) {
        textcolor(COLOR_LIGHTRED);
        printf("No RAMLink found.\n\n");
        textcolor(COLOR_GRAY3);
    }
    else if (ramlink_size == 0) {
        textcolor(COLOR_LIGHTRED);
        printf("RAMLink not accessible.\n\n");
        textcolor(COLOR_GRAY3);
    }
    else if (method == METHOD_NONE) {
        textcolor(COLOR_LIGHTRED);
        printf("No suitable backup device found.\n\n");
        textcolor(COLOR_GRAY3);
    }
    
    if (dos == 1 && reu_size == 0) {
        /*      0123456789012345678901234567890123456789 */
        printf("For faster backup enable \05RAM Expansion");
        printf("Unit\x9b in Menu -> F2 -> \"C64 and\n");
        printf("Cartridge Settings\". Set \05REU Size\x9b\n");
        /*      0123456789012345678901234567890123456789 */
        printf("to 16 MB.\n\n");
    }

    gotoy(24);
    
    switch (state) {
    case OK:
        return true;
        
    case WARNING:
        printf("(C)ontinue, (R)echeck, or (H)elp.");
        do {
            key = tolower(cgetc());
        } while (key != 'c' && key != 'r' && key != 'h');
        if (key == 'c') {
            return true;
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
    return false;
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
