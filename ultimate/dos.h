#ifndef HAD_ULTIMATE_DOS_H
#define HAD_ULTIMATE_DOS_H

#define ULTIMATE_DOS_CMD_IDENTIFY 0x01
#define ULTIMATE_DOS_CMD_OPEN_FILE 0x02
#define ULTIMATE_DOS_CMD_CLOSE_FILE 0x03
#define ULTIMATE_DOS_CMD_READ_DATA 0x04
#define ULTIMATE_DOS_CMD_WRITE_DATA 0x05
#define ULTIMATE_DOS_CMD_FILE_SEEK 0x06
#define ULTIMATE_DOS_CMD_FILE_INFO 0x07
#define ULTIMATE_DOS_CMD_CHANGE_DIR 0x11
#define ULTIMATE_DOS_CMD_GET_PATH 0x12
#define ULTIMATE_DOS_CMD_OPEN_DIR 0x13
#define ULTIMATE_DOS_CMD_READ_DIR 0x14
#define ULTIMATE_DOS_CMD_COPY_UI_PATH 0x15
#define ULTIMATE_DOS_CMD_LOAD_REU 0x21
#define ULTIMATE_DOS_CMD_SAVE_REU 0x22
#define ULTIMATE_DOS_CMD_ECHO 0xF0

extern unsigned char ultimate_dos_cmd[];

unsigned char ultimate_dos_close_file(unsigned char instance);
unsigned int ultimate_dos_identify(unsigned char instance, unsigned char *buffer, unsigned int length);
unsigned char ultimate_dos_open_file(unsigned char instance, const unsigned char *name, unsigned char mode);
unsigned char ultimate_dos_read_data(unsigned char instance, unsigned char *buffer, unsigned int length);
unsigned char ultimate_dos_write_data(unsigned char instance, const unsigned char *buffer, unsigned int length);

#endif /* HAD_ULTIMATE_DOS_H */
