#include "ramlink.h"


void ramlink_reu_copy(unsigned long reu_address, void *c64_address, unsigned int length, unsigned char mode) {
	ramlink_reu_enable();

	RAMLINK_REU.c64_address = c64_address;
	RAMLINK_REU.reu_address = reu_address & 0xffff;
	RAMLINK_REU.reu_bank = reu_address >> 16;
	RAMLINK_REU.length = length;
	RAMLINK_REU.address_control = 0;
	RAMLINK_REU.command = REU_COMMAND_EXECUTE | mode;

	ramlink_reu_execute_and_disable();
}
