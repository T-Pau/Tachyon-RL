#ifndef HAD_RAMLINK_BACKUP_H
#define HAD_RAMLINK_BACKUP_H

#include "ramlink/ramlink.h"
#include "reu/reu.h"
#include "ultimate/ci.h"
#include "ultimate/dos.h"

/* disable operations for profiling */
#define ENABLE_DOS 1
#define ENABLE_RAMLINK 1
#define ENABLE_REU 1

extern unsigned char dos;
extern unsigned long ramlink_size;
extern unsigned long reu_size;

#define BUFFER_SIZE (16*1024)

extern unsigned char buffer[BUFFER_SIZE];

#define ramlink_pages (*(unsigned int *)((unsigned char *)ramlink_size + 1))
#define reu_pages (*(unsigned int *)((unsigned char *)reu_size + 1))

unsigned char backup_dos(const char *filename);
unsigned char backup_reu(const char *filename);
unsigned char backup_reu_dma(const char *filename);
unsigned char detect(void);

#endif /* HAD_RAMLINK_BACKUP_H */
