#include <stdio.h>
#include <string.h>
#include <conio.h>

#include "tachyon.h"
#include "timer.h"

unsigned char filename[256];

int main(void) {
	const char *string;
	unsigned int ret;

    clrscr();
    printf("Tachyon RL - Back Up Your RAMLink\n\n");

	if (detect() != 0) {
		return 0;
	}

	string = ultimate_dos_copy_home_path(1);
	printf("Current directory:\n  %s\n", string);

    do {
        gotox(0);
        printf("B)ackup or R)estore? ");
        ret = getchar();
    } while (ret != 'B' && ret != 'b' && ret != 'R' && ret != 'r');
    
	printf("Filename: ");
	fgets(filename, 256, stdin);
	filename[strlen(filename)-1] = '\0';
    
    if (ret == 'B' || ret == 'b') {
        timer_start();
        backup();
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
        ret = getchar();
        if (ret != 'Y' && ret != 'y') {
            return 0;
        }
        
        timer_start();
        restore();
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
