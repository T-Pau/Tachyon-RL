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

    bgcolor(COLOR_BLACK);
    bordercolor(COLOR_BLACK);
    textcolor(COLOR_GRAY3);
    clrscr();
    textcolor(COLOR_WHITE);
    printf("Tachyon RL - Back Up Your RAMLink\n\n");
    textcolor(COLOR_GRAY3);

#if 0
	if (detect() != 0) {
		return 0;
	}
#endif

	string = ultimate_dos_copy_home_path(1);
	printf("Current directory:\n  %s\n", string);

    do {
        gotox(0);
        printf("B)ackup, R)estore, or H)elp");
        ret = tolower(cgetc());
    } while (ret != 'b' && ret != 'r' && ret != 'h');
    printf("\n");
    
    if (ret == 'h') {
        help();
        /* TODO: back to beginning */
        return 1;
    }
    
	printf("Filename: ");
	fgets(filename, 256, stdin);
	filename[strlen(filename)-1] = '\0';
    
    if (ret == 'B' || ret == 'b') {
        timer_start();
        ret = backup();
        timer_stop();
        
        if (ret == 0) {
            puts("Backup done in ");
            timer_output();
            puts("\n");
        }
        else {
            puts("Backup failed.\n");
        }
    }
    else {
        printf("You are about to restore RAMLink.\n");
        printf("This will erase its current contents.\n");
        printf("Are you sure? ");
        ret = cgetc();
        printf("%c\n", ret);
        if (ret != 'Y' && ret != 'y') {
            return 0;
        }
        
        timer_start();
        ret = restore();
        timer_stop();
        
        if (ret == 0) {
            puts("Restore done in ");
            timer_output();
            puts("\n");
            /* TODO: re-init RAMLink? power cycle? */
        }
        else {
            puts("Restore failed.\n");
        }
    }

    return 0;
}
