#include "ramlink.h"

#include "../reu/reu.h"

#define REU_PAGE (*(unsigned int *)0xdf05)

void ramlink_reu_dma(unsigned char mode, unsigned int ramlink_page_, unsigned int reu_page_, unsigned int num_pages) {
	static unsigned char command;
    static unsigned int ramlink_page;
    static unsigned int reu_page;
	static unsigned int end;

    ramlink_page = ramlink_page_;
    reu_page = reu_page_;
	command = REU_COMMAND_DEFAULT | mode;
	end = ramlink_page + num_pages;

	asm("sei");
	ramlink_activate();

    do {
        RAMLINK_PAGE = ramlink_page;
		ramlink_show_data();
        REU.c64_address = RAMLINK_DATA;
        REU.reu_address = reu_page & 0xff;
        REU.reu_bank = reu_page >> 8;
        REU.length = 256;
		REU.command = command;
		++ramlink_page;
        ++reu_page;
	} while (ramlink_page != end);

	ramlink_deactivate();
	asm("cli");
}
