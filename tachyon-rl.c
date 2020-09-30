/*
  tachyon-rl.c -- Main program.
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

#include <stdio.h>
#include <string.h>
#include <conio.h>
#include <ctype.h>

#include "tachyon.h"
#include "timer.h"

unsigned char filename[256];

static void print_approximate_time(uint32_t ms);


int main(void) {
	const char *string;
	unsigned int ret;
    uint8_t speed_index;

    while (1) {
        bgcolor(COLOR_BLACK);
        bordercolor(COLOR_BLACK);
/*        bordercolor(COLOR_GRAY1); /* DEBUG */
        textcolor(COLOR_GRAY3);
        clrscr();
        textcolor(COLOR_WHITE);
        printf("Tachyon RL " VERSION " - RAMLink Backup\n");
        textcolor(COLOR_GRAY3);
        
        if (!detect()) {
            continue;
        }
        
        clear_lines(top_line, 25);
        gotoxy(0, top_line);
        
        switch (method) {
        case METHOD_ULTIMATE:
            printf("Copying directly to/from Ultimate.\n");
            break;
            
        case METHOD_ULTIMATE_REU:
            printf("Copying to/from Ultimate via REU.\n");
            break;
            
        case METHOD_SD2IEC:
            printf("Copying to/from SD2IEC via serial bus.\n");
            break;
        }
        
        if (cpu_speed == 20) {
            if (cpu == CPU_SUPERCPU_V1) {
                speed_index = 2;
            }
            else {
                speed_index = 3;
            }
        }
        else {
            speed_index = cpu_speed - 1;
        }
        speed_index += (method - 1) * 4;
        
        printf("It will take about ");
        print_approximate_time((ramlink_size >> 16) * speed_factor[speed_index]);
        printf(".\n");
        
        gotoxy(0, 24);
        printf("(B)ackup, (R)estore, or (H)elp.");
        do {
            ret = tolower(cgetc());
        } while (ret != 'b' && ret != 'r' && ret != 'h');
        
        if (ret == 'h') {
            help();
            continue;
        }
        
        clear_lines(top_line + 3, 25);
        gotoxy(0, top_line + 3);

        if (ret == 'b') {
            printf("Backing up RAMLink.\n");
        }
        else {
            printf("Restoring RAMLink.\n");
        }
        
        if (dos) {
            string = ultimate_dos_copy_home_path(1);
            printf("Current directory:\n  %s\n", string);
        }
        
        printf("Filename: ");
        fgets(filename, 256, stdin);
        filename[strlen(filename)-1] = '\0';
        
        printf("\n");
        
        if (ret == 'b') {
            timer_start();
            ret = backup();
            timer_stop();
            
            if (ret) {
                printf("Backup done in ");
                timer_output();
                printf("\n");
            }
            else {
                printf("Backup failed.\n");
            }
        }
        else {
            printf("You are about to restore RAMLink.\n");
            printf("This will erase its current contents.\n");
            printf("Are you sure (y/n)?\n");
            ret = tolower(cgetc());
            if (ret != 'y') {
                continue;
            }
            
            timer_start();
            ret = restore();
            timer_stop();
            
            if (ret) {
                printf("Restore done in ");
                timer_output();
                printf("\n");
            }
            else {
                printf("Restore failed.\n");
            }
        }
        
        gotoxy(0, 24);
        printf("Press any key to continue.");
        cgetc();
    }
    
    return 0;
}


static void print_approximate_time(uint32_t ms) {
    if (ms < 110000) {
        printf("%lu seconds", (ms + 500) / 1000);
    }
    else {
        printf("%lu minutes", (ms + 30000L) / 60000L);
    }
}
