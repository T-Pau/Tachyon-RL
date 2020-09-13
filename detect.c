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
unsigned long reu_size;

#define OK 0
#define WARNING 1
#define ERROR 2

unsigned char detect(void) {
    const char *string;
    unsigned char state = OK;
    unsigned char key;

	printf("RAMLink:  ");
	if ((ramlink_size = ramlink_get_size()) == 0) {
        textcolor(COLOR_LIGHTRED);
		printf("not found\n");
        textcolor(COLOR_GRAY3);
        state = ERROR;
	}
    else {
        textcolor(COLOR_LIGHTGREEN);
    	printf("%lu bytes\n", ramlink_size);
        textcolor(COLOR_GRAY3);
    }

	printf("REU:      ");
	if ((reu_size = (unsigned long)reu_detect() << 16) == 0) {
        textcolor(COLOR_YELLOW);
		printf("not found\n");
        textcolor(COLOR_GRAY3);
        if (state == OK) {
            state = WARNING;
        }
	}
	else {
        textcolor(COLOR_LIGHTGREEN);
		printf("%lu bytes\n", reu_size);
        textcolor(COLOR_LIGHTGREEN);
	}

	printf("Ultimate: ");
	if ((string = ultimate_dos_identify(1)) == NULL) {
        textcolor(COLOR_LIGHTRED);
		printf("not found\n");
        textcolor(COLOR_GRAY3);
        state = ERROR;
	}
    else {
        textcolor(COLOR_LIGHTGREEN);
    	printf("%s\n", string);
        textcolor(COLOR_GRAY3);
    }
    printf("\n");

#if ENABLE_RAMLINK
    if (ramlink_size == 0) {
        printf("Please make sure your RAMLink\n");
        printf("is connected and enabled.\n\n");
    }
#endif
    
#if ENABLE_DOS
    if (dos == 0) {
        printf("Please make sure your Ultimate is\n");
        printf("connected to the Pass Through port of\n");
        printf("your RAMLink and that the Command\n");
        printf("Interface is enabled: Press the Menu\n");
        printf("button, then F2. Select \"C64 and\n");
        printf("Cartridge Settings\" and enable\n");
        printf("\"Command Interface\".\n\n");
    }
#endif
#if ENABLE_REU
    if (reu_size == 0) {
        printf("Tachyon RL is much faster if it can\n");
        printf("use the Ultimate's RAM Expansion Unit.\n");
        printf("Press the Menu button, then F2. Select\n");
        printf("\"C64 and Cartridge Settings\" and\n");
        printf("enable \"RAM Expansion Unit\". A REU\n");
        printf("Size of 16 MB is best.\n\n");
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
