#include "reu.h"

void reu_copy(unsigned long reu_address, void *c64_address, unsigned int length, unsigned char mode) {
	REU.c64_address = (unsigned int)c64_address;
	REU.reu_address = reu_address & 0xffff;
	REU.reu_bank = reu_address >> 16;
	REU.length = length;
	REU.command = REU_COMMAND_DEFAULT | mode;
}
