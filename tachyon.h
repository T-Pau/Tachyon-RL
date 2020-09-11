#ifndef HAD_TACHYON_H
#define HAD_TACHYON_H

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
extern unsigned char filename[];

#define ramlink_pages (*(unsigned int *)((unsigned char *)&ramlink_size + 1))
#define reu_pages (*(unsigned int *)((unsigned char *)&reu_size + 1))

unsigned char backup(void);
unsigned char backup_dos(void);
unsigned char backup_reu(void);
unsigned char backup_reu_dma(void);
unsigned char detect(void);
unsigned char restore(void);
unsigned char restore_dos(void);
unsigned char restore_reu(void);
unsigned char restore_reu_dma(void);

#endif /* HAD_TACHYON_H */
