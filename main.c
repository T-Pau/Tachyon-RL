#include <stdio.h>
#include <string.h>

#include "ramlink-backup.h"
#include "timer.h"

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
 	if (reu_size > 0) {
 		ret = backup_reu_dma(filename);
 	}
 	else {
		ret = backup_dos(filename);
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
