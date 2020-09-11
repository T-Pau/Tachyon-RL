#include "tachyon.h"

#include <stdio.h>

#include "ramlink/ramlink.h"
#include "reu/reu.h"
#include "ultimate/dos.h"

unsigned char dos;
unsigned long ramlink_size;
unsigned long reu_size;

unsigned char detect(void) {
    const char *string;
    unsigned char ok = 1;

	printf("RAMLink:  ");
	if ((ramlink_size = ramlink_get_size()) == 0) {
		printf("not found\n");
        ok = 0;
	}
    else {
    	printf("%lu bytes\n", ramlink_size);
    }

	printf("REU:      ");
	if ((reu_size = (unsigned long)reu_detect() << 16) == 0) {
		printf("not found\n");
	}
	else {
		printf("%lu bytes\n", reu_size);
	}

	printf("Ultimate: ");
	if ((string = ultimate_dos_identify(1)) == NULL) {
		printf("not found\n");
        ok = 0;
	}
    else {
    	printf("%s\n\n", string);
    }

    if (!ok) {
        return 1;
    }

    return 0;
}
