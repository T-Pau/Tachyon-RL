#include "reu.h"

unsigned int reu_detect(void) {
	static unsigned char backup[256];
	unsigned char buffer[1];
	unsigned char bank;
	unsigned char value;
	unsigned int size;

	REU.reu_address = 0;
	REU.length = 1;

	/* back up first byte of each bank */
	bank = 0;
	do {
		REU.c64_address = (unsigned int)(backup + bank);
		REU.command = REU_COMMAND_DEFAULT | REU_COMMAND_REU_TO_C64;
		++bank;
	} while (bank != 0);

	/* write bank number to first byte of each bank */
	REU.c64_address = (unsigned int)buffer;
	bank = 0;
	do {
		buffer[0] = bank;
		REU.reu_bank = bank;
		REU.command = REU_COMMAND_DEFAULT | REU_COMMAND_C64_TO_REU;
		++bank;
	} while (bank != 0);

	size = 256;
	/* read back bank number from first byte of each bank */
	bank = 0;
	do {
		REU.reu_bank = bank;
		REU.command = REU_COMMAND_DEFAULT | REU_COMMAND_REU_TO_C64;
		//printf("bank %02x read %02x\n", bank, buffer[0]);
		if (bank == 0) {
			value = buffer[0];
		}
		else if (buffer[0] != value) {
			size = bank;
			break;
		}
		++value;
		++bank;
	} while (bank != 0);

	/* restore first byte of each bank */
	bank = 0;
	do {
		REU.c64_address = (unsigned int)(backup + bank);
		REU.command = REU_COMMAND_DEFAULT | REU_COMMAND_C64_TO_REU;
		++bank;
	} while (bank != 0);

	return size;
}
