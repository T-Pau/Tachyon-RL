#ifndef HAD_RAMLINK_H
#define HAD_RAMLINK_H

#include "../reu/reu.h"

#define RAMLINK_JOB_READ 0x80
#define RAMLINK_JOB_WRITE 0x90
#define RAMLINK_JOB_VERIFY 0xa0
#define RAMLINK_JOB_SWAP 0xb0

#define RAMLINK_ERROR_OK 0x00
#define RAMLINK_ERROR_VERIFY 0x02
#define RAMLINK_ERROR_ILLEGAL_BLOCK 0x04
#define RAMLINK_ERROR_ILLEGAL_PARTITION 0x0f

struct ramlink_block_registers {
	unsigned char job;
	unsigned char track;
	unsigned char sector;
	unsigned int c64_address;
	unsigned char partition;
	unsigned char c128_bank;
};

#define ramlink_reu_enable() (asm("jsr $e0a9"))
#define ramlink_reu_execute_and_disable() (asm("jsr $fe1e"))
#define ramlink_reu_execute_block() (asm("jsr $fe09"))
#define ramlink_reu_disable() (asm("jsr $fe0c"))

#define RAMLINK_REU (*(struct reu_registers *)0xde00)
#define RAMLINK_BLOCK (*(struct ramlink_block_registers *)0xde20)

void ramlink_reu_copy(unsigned long ramlink_address, void *c64_address, unsigned int length, unsigned char mode);
unsigned char ramlink_copy_block(unsigned char partition, unsigned char track, unsigned char sector, void *c64_address, unsigned char job);
unsigned char ramlink_detect(void);
unsigned long ramlink_get_size(void);

#endif /* HAD_RAMLINK_H */
