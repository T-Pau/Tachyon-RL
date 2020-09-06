#include <stdio.h>
#include <stdlib.h>

#include "ramlink/ramlink.h"

int main(void) {
	printf("%c", 0x8E);

	if (ramlink_detect() == 0) {
		printf("no ramlink found.\n");
		return 0;
	}
	
	printf("ramlink found.\n");

	return 0;
}
