#include "drive.h"

#include <string.h>

struct pattern {
    uint8_t type;
    uint8_t len;
    char str[6];
};

static struct pattern prefix[] = {
    { DRIVE_TYPE_CMD_FD, 6, "cmd fd" },
    { DRIVE_TYPE_CMD_HD, 6, "cmd hd" },
    { DRIVE_TYPE_RAMDRIVE, 6, "cmd rd" },
    { DRIVE_TYPE_RAMLINK, 6, "cmd rl" },
    { DRIVE_TYPE_SD2IEC, 6, "sd2iec" }
};

static struct pattern suffix[] = {
    { DRIVE_TYPE_1541, 5, " 1541" },
    { DRIVE_TYPE_1570, 5, " 1570" },
    { DRIVE_TYPE_1571, 5, " 1571" },
    { DRIVE_TYPE_1581, 5, " 1581" },
    { DRIVE_TYPE_IDE64, 6, " IDE64" },
};

uint8_t drive_types[32];

void drive_detect(void) {
    const char *identifier;
    uint8_t id = 0;
    uint8_t len, i, j, match;
    
    while (id < 32) {
        drive_types[id] = DRIVE_TYPE_NONE;
        ++id;
    }
    
    for (id = 8; id < 31; ++id) {
        if ((identifier = drive_identify(id)) != NULL) {
            len = strlen(identifier);

            match = 0;

            for (i = 0; match == 0 && i < sizeof(prefix) / sizeof(prefix[0]); ++i) {
                if (len < prefix[i].len) {
                    continue;
                }
                
                match = 1;
                for (j = 0; j < prefix[i].len; ++j) {
                    if (identifier[j] != prefix[i].str[j]) {
                        match = 0;
                        break;
                    }
                }
                if (match) {
                    drive_types[id] = prefix[i].type;
                }
            }

            for (i = 0; match == 0 && i < sizeof(suffix) / sizeof(suffix[0]); ++i) {
                if (len < suffix[i].len) {
                    continue;
                }
                
                match = 1;
                for (j = 0; j < suffix[i].len; ++j) {
                    if (identifier[len - suffix[i].len + j] != suffix[i].str[j]) {
                        match = 0;
                        break;
                    }
                }
                if (match) {
                    drive_types[id] = suffix[i].type;
                }
            }
            
            if (match == 0) {
                drive_types[id] = DRIVE_TYPE_UNKNOWN;
            }
        }
    }
}
