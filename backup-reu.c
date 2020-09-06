#include <stdio.h>
#include <stdlib.h>

#include "ramlink.h"
#include "reu.h"

#define BUFFER_SIZE (16*1024)

unsigned char buffer[BUFFER_SIZE];

static void backup(unsigned long size);
static void restore(unsigned long size);

int main(void) {
	printf("%c", 0x8E);
	/* TODO: detect REU, RAMLink sizes */
	/* TOOD: menu */
	backup(16*1024*1024);
	printf("backup done\n");
	return 0;
}

static void backup(unsigned long size) {
	unsigned long address;

	printf("%ccopied   0 of %3u\n", 147, (unsigned int)(size >> 16));
	for (address = 0; address < size; address += BUFFER_SIZE) {
		printf("%ccopied %3u", 19, (unsigned int)(address>>16));
		ramlink_reu_copy(address, buffer, BUFFER_SIZE, REU_COMMAND_REU_TO_C64);
		reu_copy(address, buffer, BUFFER_SIZE, REU_COMMAND_C64_TO_REU);
	}
		printf("%ccopied %3u\n", 19, (unsigned int)(address>>16));
}

static void restore(unsigned long size) {
	unsigned long address;

	for (address = 0; address < size; address += BUFFER_SIZE) {
		reu_copy(address, buffer, BUFFER_SIZE, REU_COMMAND_REU_TO_C64);
		ramlink_reu_copy(address, buffer, BUFFER_SIZE, REU_COMMAND_C64_TO_REU);
	}
}
