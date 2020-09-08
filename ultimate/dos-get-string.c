#include "dos-internal.h"

#include <stddef.h>

unsigned char *ultimate_dos_get_string(unsigned char instance, unsigned char command) {
    unsigned int length; 

    ULTIMATE_CI.command = instance;
    ULTIMATE_CI.command = command;

    if (ultimate_ci_execute() != 0) {
        return NULL;
    }

    length = ultimate_ci_read(ultimate_dos_buffer, ULTIMATE_DOS_BUFFER_LENGTH);
    if (length == 0) {
        return NULL;
    }
    ultimate_ci_ascii2pet(ultimate_dos_buffer, length);
    ultimate_dos_buffer[length] = '\0';
    return ultimate_dos_buffer;
}
