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
        
        string = ultimate_dos_copy_home_path(1);
        printf("Current directory:\n  %s\n", string);
        
        printf("(B)ackup, (R)estore, or (H)elp.\n");
        do {
            ret = tolower(cgetc());
        } while (ret != 'b' && ret != 'r' && ret != 'h');
        
        if (ret == 'h') {
            help();
            continue;
        }
        
        printf("Filename: ");
        fgets(filename, 256, stdin);
        filename[strlen(filename)-1] = '\0';
        
        if (ret == 'B' || ret == 'b') {
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
            if (ret != 'Y') {
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
