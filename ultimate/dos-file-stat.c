#include "dos-internal.h"

#include <stddef.h>

const ultimate_dos_file_info_t *ultimate_dos_file_stat(unsigned char instance, const unsigned char *filename) {
    unsigned int length;

    ULTIMATE_CI.command = instance;
    ULTIMATE_CI.command = ULTIMATE_DOS_CMD_FILE_STAT;
    ultimate_ci_write_string(filename);
    if (ultimate_ci_execute() != 0) {
        return NULL;
    }
    length = ultimate_ci_read(ultimate_dos_buffer, ULTIMATE_DOS_BUFFER_LENGTH);

    if (length < 12) {
        return NULL;
    }

    ultimate_dos_buffer[length] = '\0';
    ultimate_ci_ascii2pet(ultimate_dos_buffer + offsetof(ultimate_dos_file_info_t, filename), length - offsetof(ultimate_dos_file_info_t, filename));
    return (ultimate_dos_file_info_t *)ultimate_dos_buffer;
}
