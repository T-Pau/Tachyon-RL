#include "ramlink.h"

#include <string.h>

static unsigned char block[256];
static unsigned char signature[] = {
	0x01, 0x01, 0xff, 0x00, 0x00, 0x53, 0x59, 0x53, 0x54, 0x45, 0x4d, 0xa0
};

unsigned long ramlink_get_size(void) {
	unsigned char i = 0;
	unsigned long size;

	if (!ramlink_detect()) {
		return 0;
	}

	if (ramlink_copy_block(255, 1, 0, block, RAMLINK_JOB_READ) != 0) {
		return 0;
	}

	while (i < sizeof(signature)) {
		if (block[i] != signature[i]) {
			return 0;
		}
		++i;
	}

	size = (((unsigned long)block[22] << 16) | ((unsigned int)block[23] << 8) | block[24]) + 0x1000;

	return size;
}
