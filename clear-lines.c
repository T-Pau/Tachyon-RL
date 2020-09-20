#include <stdint.h>

void clear_lines(uint8_t start, uint8_t end) {
    static uint8_t *ptr;
    static uint8_t *end_ptr;
    
    ptr = (uint8_t *)0x400 + start * 40;
    end_ptr = (uint8_t *)0x400 + end * 40;
    
    while (ptr < end_ptr) {
        *ptr = ' ';
        ++ptr;
    }
}
