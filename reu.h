#ifndef HAD_REU_H
#define HAD_REU_H

#define C64_TO_REU 0
#define REU_TO_C64 1

#define REU_COMMAND_EXECUTE 0x80
#define REU_COMMAND_AUTOLOAD 0x20
#define REU_COMMAND_FF00 0x10
#define REU_COMMAND_C64_TO_REU 0x0
#define REU_COMMAND_REU_TO_C64 0x1
#define REU_COMMAND_SWAP 0x2
#define REU_COMMAND_VERIFY 0x3

struct reu_registers {
	unsigned char status;
	unsigned char command;
	unsigned int c64_address;
	unsigned int reu_address;
	unsigned char reu_bank;
	unsigned int length;
	unsigned char irq_mask;
	unsigned char address_control;
};

#define REU (*(struct reu_registers *)0xdf00)

void reu_copy(unsigned long reu_address, void *c64_address, unsigned int length, unsigned char mode);
unsigned int reu_detect(void);
/* void reu_execute(unsigend char command); */

#endif /* HAD_REU_H */
