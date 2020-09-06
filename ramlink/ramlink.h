#ifndef HAD_RAMLINK_H
#define HAD_RAMLINK_H

#include "../reu/reu.h"

#define ramlink_reu_enable() (asm("jsr $e0a9"))
#define ramlink_reu_execute_and_disable() (asm("jsr $fe1e"))

#define RAMLINK_REU (*(struct reu_registers *)0xde00)

void ramlink_reu_copy(unsigned long ramlink_address, void *c64_address, unsigned int length, unsigned char mode);
unsigned char ramlink_detect(void);

#endif /* HAD_RAMLINK_H */
