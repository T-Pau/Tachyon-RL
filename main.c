#include <stdio.h>
#include <string.h>

#include "ramlink/ramlink.h"
#include "ultimate/ci.h"
#include "ultimate/dos.h"

#include "detect.h"
#include "timer.h"

/* disable operations for profiling */
#define ENABLE_DOS 1
#define ENABLE_RAMLINK 1
#define ENABLE_REU 1

#define BUFFER_SIZE (16*1024)

unsigned char buffer[BUFFER_SIZE];

static unsigned char backup(unsigned long size, const char *filename);
static unsigned char backup_reu(unsigned long size, const char *filename);

char filename[256];

int main(void) {
	const char *string;
	unsigned int ret;

	printf("%cBacking up RAMLink\n\n", 147);

	if (detect() != 0) {
		return 0;
	}

	string = ultimate_dos_copy_home_path(1);
	printf("Current directory:\n  %s\n", string);

	printf("Filename: ");
	fgets(filename, 256, stdin);
	filename[strlen(filename)-1] = '\0';

	timer_start();
 	if (use_reu) {
 		ret = backup_reu(ramlink_size, filename);
 	}
 	else {
		ret = backup(ramlink_size, filename);
	}
	timer_stop();

	if (ret == 0) {
		puts("backup done in ");
		timer_output();
		puts("\n");
	}
	else {
		puts("backup failed.\n");
	}
	return 0;
}

static unsigned char backup(unsigned long size, const char *filename) {
	unsigned long address;

#if ENABLE_DOS
	if (ultimate_dos_open_file(1, filename, ULTIMATE_DOS_OPEN_CREATE_ALWAYS|ULTIMATE_DOS_OPEN_CREATE_NEW|ULTIMATE_DOS_OPEN_WRITE) != 0) {
		printf("can't open '%s':\n  %s\n", filename, ultimate_ci_status);
		return 1;
	}
#endif

	printf("%cCopied   0 of %3u\n", 147, (unsigned int)(size >> 16));
	for (address = 0; address < size; address += BUFFER_SIZE) {
		printf("%cCopied %3u", 19, (unsigned int)(address>>16));
#if ENABLE_RAMLINK
		ramlink_reu_copy(address, buffer, BUFFER_SIZE, REU_COMMAND_REU_TO_C64);
#endif
#if ENABLE_DOS
		if (ultimate_dos_write_data(1, buffer, BUFFER_SIZE) != 0) {
			printf("\ncan't write to '%s':\n  %s\n", filename, ultimate_ci_status);
			ultimate_dos_close_file(1);
			return 1;
		}
#endif
	}

	printf("%cCopied %3u\n", 19, (unsigned int)(address>>16));

#ifdef ENABLE_DOS
	ultimate_dos_close_file(1);
#endif

	return 0;
}


static unsigned char backup_reu(unsigned long size, const char *filename) {
	unsigned long address;

#if ENABLE_DOS
	if (ultimate_dos_open_file(1, filename, ULTIMATE_DOS_OPEN_CREATE_ALWAYS|ULTIMATE_DOS_OPEN_CREATE_NEW|ULTIMATE_DOS_OPEN_WRITE) != 0) {
		printf("can't open '%s':\n  %s\n", filename, ultimate_ci_status);
		return 1;
	}
#endif

	printf("%cCopied   0 of %3u\n", 147, (unsigned int)(size >> 16));
	for (address = 0; address < size; address += BUFFER_SIZE) {
		printf("%cCopied %3u", 19, (unsigned int)(address>>16));
#if ENABLE_RAMLINK
		ramlink_reu_copy(address, buffer, BUFFER_SIZE, REU_COMMAND_REU_TO_C64);
#endif
#if ENABLE_REU
		reu_copy(address, buffer, BUFFER_SIZE, REU_COMMAND_C64_TO_REU);
#endif
	}
	printf("%cCopied %3u\n", 19, (unsigned int)(address>>16));

	printf("Saving REU\n");

#if ENABLE_DOS
	if (ultimate_dos_save_reu(1, 0, size) == NULL) {
		printf("can't save REU:\n  %s\n", filename, ultimate_ci_status);
		ultimate_dos_close_file(1);
		return 1;
	}
	ultimate_dos_close_file(1);
#endif

	return 0;
}
