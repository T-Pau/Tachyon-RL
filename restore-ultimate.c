#include <stdio.h>
#include <string.h>

#include "ramlink/ramlink.h"
#include "ultimate/ci.h"
#include "ultimate/dos.h"

#include "timer.h"

/* disable operations for profiling */
#define ENABLE_DOS 1
#define ENABLE_RAMLINK 1
#define ENABLE_REU 1

#define BUFFER_SIZE (16*1024)

unsigned char buffer[BUFFER_SIZE];

static unsigned char restore(unsigned long size, const char *filename);
static unsigned char restore_reu(unsigned long size, const char *filename);

char filename[256];

int main(void) {
	const char *string;
	unsigned long size;
	unsigned long reu_size;
	unsigned ret;

	printf("%cRestore RAMLink\n\n", 147);
	printf("THIS WILL DELETE ALL DATA ON RAMLINK!\n\n");

	/* TODO: ask for confirmation */

	printf("Detecting RAMLink: ");
	if ((size = ramlink_get_size()) == 0) {
		printf("not found.\n");
		return 0;
	}
	printf("%lu bytes\n", size);

	printf("Detecting REU: ");
	if ((reu_size = (unsigned long)reu_detect() << 16) == 0) {
		printf("not found.\n");
	}
	printf("%lu bytes\n", reu_size);

	printf("Detecting Ultimate DOS: ");
	if ((string = ultimate_dos_identify(1)) == NULL) {
		printf("not found\n");
		return 0;
	}
	printf("%s\n", string);

	string = ultimate_dos_copy_home_path(1);
	printf("Current directory:\n  %s\n", string);

	printf("Filename: ");
	fgets(filename, 256, stdin);
	filename[strlen(filename)-1] = '\0';

	timer_start();
 	if (reu_size >= size) {
 		ret = restore_reu(size, filename);
 	}
 	else {
		ret = restore(size, filename);
	}
	timer_stop();

	if (ret == 0) {
		puts("restore done in ");
		timer_output();
		puts("\n");
	}
	else {
		puts("restore failed.\n");
	}
	return 0;
}

static unsigned char restore(unsigned long size, const char *filename) {
	unsigned long address;

#if ENABLE_DOS
	if (ultimate_dos_open_file(1, filename, ULTIMATE_DOS_OPEN_READ) != 0) {
		printf("can't open '%s':\n  %s\n", filename, ultimate_ci_status);
		return 1;
	}

	/* TODO: check file size */
#endif


	printf("%cCopied   0 of %3u\n", 147, (unsigned int)(size >> 16));
	for (address = 0; address < size; address += BUFFER_SIZE) {
		printf("%cCopied %3u", 19, (unsigned int)(address>>16));
#if ENABLE_DOS
		if (ultimate_dos_read_data(1, buffer, BUFFER_SIZE) != 0) {
			printf("\ncan't write to '%s':\n  %s\n", filename, ultimate_ci_status);
			ultimate_dos_close_file(1);
			return 1;
		}
#endif
	}
#if ENABLE_RAMLINK
		ramlink_reu_copy(address, buffer, BUFFER_SIZE, REU_COMMAND_C64_TO_REU);
#endif

	printf("%cCopied %3u\n", 19, (unsigned int)(address>>16));

#ifdef ENABLE_DOS
	ultimate_dos_close_file(1);
#endif

	return 0;
}


static unsigned char restore_reu(unsigned long size, const char *filename) {
	unsigned long address;

#if ENABLE_DOS
	if (ultimate_dos_open_file(1, filename, ULTIMATE_DOS_OPEN_READ) != 0) {
		printf("can't open '%s':\n  %s\n", filename, ultimate_ci_status);
		return 1;
	}

	/* TODO: check file size */
#endif

	printf("Loading REU\n");

#if ENABLE_DOS
	if (ultimate_dos_load_reu(1, 0, size) == NULL) {
		printf("can't load REU:\n  %s\n", filename, ultimate_ci_status);
		ultimate_dos_close_file(1);
		return 1;
	}
	ultimate_dos_close_file(1);
#endif

	printf("%cCopied   0 of %3u\n", 147, (unsigned int)(size >> 16));
	for (address = 0; address < size; address += BUFFER_SIZE) {
		printf("%cCopied %3u", 19, (unsigned int)(address>>16));
#if ENABLE_REU
		reu_copy(address, buffer, BUFFER_SIZE, REU_COMMAND_REU_TO_C64);
#endif
#if ENABLE_RAMLINK
		ramlink_reu_copy(address, buffer, BUFFER_SIZE, REU_COMMAND_C64_TO_REU);
#endif
	}
	printf("%cCopied %3u\n", 19, (unsigned int)(address>>16));

	return 0;
}
