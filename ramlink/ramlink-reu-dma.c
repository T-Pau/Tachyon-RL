#include "ramlink.h"

#include "../reu/reu.h"

#define COPY_PAGE() \

void ramlink_reu_dma(unsigned char mode, unsigned int ramlink_page_, unsigned int reu_page_, unsigned int length) {
	static unsigned char command;
	static unsigned int ramlink_page;
	static unsigned int reu_page;
	static unsigned int ramlink_end;

	command = REU_COMMAND_DEFAULT | mode;
	ramlink_page = ramlink_page_;
	reu_page = reu_page_;
	ramlink_end = ramlink_page + length + 1;
	--ramlink_end;

	asm("sei");
	ramlink_activate();

	REU.c64_address = (unsigned int)RAMLINK_DATA;
	REU.length = 255;

	do {
		RAMLINK_PAGE = ramlink_page;
		ramlink_show_data();
		REU.reu_address = (reu_page & 0xff) << 8;
		REU.reu_bank = reu_page >> 8;
		REU.command = command;
		++ramlink_page;
		++reu_page;
	} while (ramlink_page != ramlink_end);

	ramlink_deactivate();
	asm("cli");
}
