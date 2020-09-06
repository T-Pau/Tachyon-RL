#include "ramlink.h"

unsigned char ramlink_detect(void) {
	if (*(unsigned char *)0xe0a9 == 0x78) {
		return 1;
	}
	return 0;
}
