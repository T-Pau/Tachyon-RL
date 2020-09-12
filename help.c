#include "tachyon.h"

#include <conio.h>
#include <c64.h>

#define SCREEN ((unsigned char *)0x400)

void help(void) {
	static unsigned int i;

	for (i = 0; i < 1000; i++) {
		SCREEN[i] = help_screen[i];
        if (i > 40) {
            COLOR_RAM[i] = COLOR_GRAY3;
        }
	}

	cgetc();
}
