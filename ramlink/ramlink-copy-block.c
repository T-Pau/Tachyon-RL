#include "ramlink.h"

unsigned char ramlink_copy_block(unsigned char partition, unsigned char track, unsigned char sector, void *c64_address, unsigned char job) {
	unsigned char status;

	ramlink_reu_enable();
	RAMLINK_BLOCK.job = job;
	RAMLINK_BLOCK.c64_address = (unsigned int)c64_address;
	RAMLINK_BLOCK.partition = partition;
	RAMLINK_BLOCK.track = track;
	RAMLINK_BLOCK.sector = sector;
	ramlink_reu_execute_block();
	status = RAMLINK_BLOCK.job;
	ramlink_reu_disable();
	return status;
}
