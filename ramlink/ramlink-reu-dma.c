#include "ramlink.h"

#include "../reu/reu.h"

#define REU_PAGE (*(unsigned int *)0xdf05)

void ramlink_reu_dma(unsigned char mode, unsigned int ramlink_page, unsigned int reu_page, unsigned int length) {
	static unsigned char command;
	static unsigned int ramlink_end;

	command = REU_COMMAND_DEFAULT | mode;
	ramlink_end = ramlink_page + length;
	--ramlink_end;

	asm("sei");
	ramlink_activate();
	RAMLINK_PAGE = ramlink_page;

	REU.c64_address = (unsigned int)RAMLINK_DATA;
	REU.length = 255;
	REU_PAGE = reu_page;

	do {
		ramlink_show_data();
		REU.command = command;
		++RAMLINK_PAGE;
		++REU_PAGE;
	} while (RAMLINK_PAGE != ramlink_end);

	ramlink_deactivate();
	asm("cli");
}
