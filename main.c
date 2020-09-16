/*
  main.c -- Main program.
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

int main(void) {
	const char *string;
	unsigned int ret;

    while (1) {
        bgcolor(COLOR_BLACK);
        bordercolor(COLOR_BLACK);
        textcolor(COLOR_GRAY3);
        clrscr();
        textcolor(COLOR_WHITE);
        printf("Tachyon RL - Back up RAMLink to Ultimate\n");
        textcolor(COLOR_GRAY3);
        
        if (detect() != 0) {
            continue;
        }
        
        printf("(B)ackup, (R)estore, or (H)elp.\n");
        do {
            ret = tolower(cgetc());
        } while (ret != 'b' && ret != 'r' && ret != 'h');
        
        if (ret == 'h') {
            help();
            continue;
        }
        printf("\n");

        if (ret == 'b') {
            printf("Backing up RAMLink.\n");
        }
        else {
            printf("Restoring RAMLink.\n");
        }
        string = ultimate_dos_copy_home_path(1);
        printf("Current directory:\n  %s\n", string);
        
        printf("Filename: ");
        fgets(filename, 256, stdin);
        filename[strlen(filename)-1] = '\0';
        
        printf("\n");
        
        if (ret == 'b') {
            timer_start();
            ret = backup();
            timer_stop();
            
            if (ret == 0) {
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
            
            if (ret == 0) {
                printf("Restore done in ");
                timer_output();
                printf("\n");
                /* TODO: re-init RAMLink? power cycle? */
            }
            else {
                printf("Restore failed.\n");
            }
        }
        
        printf("Press any key to continue.\n");
        cgetc();
    }
    
    return 0;
}
