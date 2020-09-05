#include <stdio.h>
#include <stdlib.h>

#include "reu.h"

int main(void) {
	unsigned int banks;

	printf("%c", 0x8E);

	banks = reu_detect();

	if (banks == 0) {
		printf("no reu detected.\n");
	}
	else if (banks < 16) {
		printf("%dkb reu detected.\n", banks * 64);
	}
	else {
		printf("%dmb reu detected.\n", banks / 16);
	}

	exit(0);
}
