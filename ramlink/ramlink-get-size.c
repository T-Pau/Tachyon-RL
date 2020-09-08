#include "ramlink.h"

#include <string.h>
static unsigned char block[256];

unsigned long ramlink_get_size(void) {
	unsigned char i = 0;

	if (!ramlink_detect()) {
		return 0;
	}

	if (ramlink_copy_block(255, 1, 0, block, RAMLINK_JOB_READ) != 0) {
		return 0;
	}

	if (strcmp(block + 5, "system") != 0) {
		return 0;
	}

	return *(unsigned long *)(block + 21) + 0x1000;
}
