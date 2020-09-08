#include <stdio.h>
#include <string.h>

#include "ramlink/ramlink.h"
#include "ultimate/ci.h"
#include "ultimate/dos.h"

#define BUFFER_SIZE (16*1024)

unsigned char buffer[BUFFER_SIZE];

static unsigned char backup(unsigned long size, const char *filename);
static unsigned char restore(unsigned long size, const char *filename);

char filename[256];

int main(void) {
	const char *string;
	unsigned int size;

	/* printf("%c", 0x8E); */

	if (ramlink_detect() == 0) {
		printf("No RAMLink found.\n");
		return 0;
	}
	if ((string = ultimate_dos_identify(1)) == NULL) {
		printf("Ultimate II command interface not\navailable.\n");
		return 0;
	}

	string = ultimate_dos_copy_home_path(1);
	printf("Current path:\n  %s\n", identifier);

	printf("Filename: ");
	fgets(filename, 256, stdin);
	filename[strlen(filename)-1] = '\0';
	printf("RAMLink size (in mb): ");
	scanf("%d", &size);
	getchar(); /* eat newline */

	if (backup(1024*1024*(unsigned long)size, filename) == 0) {
		puts("backup done.\n");
	}
	else {
		puts("backup failed.\n");
	}
	return 0;
}

static unsigned char backup(unsigned long size, const char *filename) {
	unsigned long address;

	if (ultimate_dos_open_file(1, filename, ULTIMATE_DOS_OPEN_CREATE_ALWAYS|ULTIMATE_DOS_OPEN_CREATE_NEW|ULTIMATE_DOS_OPEN_WRITE) != 0) {
		printf("can't open '%s':\n  %s\n", filename, ultimate_ci_status);
		return 1;
	}

	printf("%cCopied   0 of %3u\n", 147, (unsigned int)(size >> 16));
	for (address = 0; address < size; address += BUFFER_SIZE) {
		printf("%ccopied %3u", 19, (unsigned int)(address>>16));
		ramlink_reu_copy(address, buffer, BUFFER_SIZE, REU_COMMAND_REU_TO_C64);
		if (ultimate_dos_write_data(1, buffer, BUFFER_SIZE) != 0) {
			printf("\ncan't write to '%s':\n  %s\n", filename, ultimate_ci_status);
			return 1;
		}
	}

	printf("%ccopied %3u\n", 19, (unsigned int)(address>>16));

	ultimate_dos_close_file(1);
	
	return 0;
}
