#include <stdio.h>
#include <stdlib.h>

#include "ramlink/ramlink.h"

int main(void) {
	unsigned long size;
	printf("%c", 0x8E);

	if (ramlink_detect() == 0) {
		printf("no ramlink found.\n");
		return 0;
	}

	if ((size = ramlink_get_size()) == 0) {
		printf("can't get ramlink size.\n");
	}
	printf("ramlink size: %lu\n", size);

	return 0;
}
