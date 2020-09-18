#ifndef HAD_DRIVE_H
#define HAD_DRIVE_H

#include <stdint.h>

#define DRIVE_TYPE_NONE 0
#define DRIVE_TYPE_1541 1
#define DRIVE_TYPE_1570 2
#define DRIVE_TYPE_1571 3
#define DRIVE_TYPE_1581 4
#define DRIVE_TYPE_CMD_FD 5
#define DRIVE_TYPE_CMD_HD 6
#define DRIVE_TYPE_RAMDRIVE 7
#define DRIVE_TYPE_RAMLINK 8
#define DRIVE_TYPE_SD2IEC 9
#define DRIVE_TYPE_IDE64 10
#define DRIVE_TYPE_UNKNOWN 127

extern uint8_t drive_types[32];

const char *drive_command(uint8_t id, const char *command);
void drive_detect(void);
const char *drive_identify(uint8_t id);

#endif /* HAD_DRIVE_H */
