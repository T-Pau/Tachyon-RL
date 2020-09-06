#include <stdio.h>
#include <stdlib.h>

#include "ramlink.h"
#include "ultimate-dos.h"

#define BUFFER_SIZE (16*1024)

unsigned char buffer[BUFFER_SIZE];

static void backup(unsigned long size);
static void restore(unsigned long size);

int main(void) {
	printf("%c", 0x8E);

	if (ramlink_detect() == 0) {
		printf("no ramlink found.\n");
		return 0;
	}
	if (ultimate_dos_identify(buffer, sizeof(buffer)) == 0) {
		printf("no ultimate command interface.\n");
		return 0;
	}

	/* TODO: detect size */
	/* TODO: backup */

	return 0;
}
