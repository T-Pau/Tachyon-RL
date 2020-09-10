SUBDIRS = ramlink reu ultimate

DISK=ramlink-backup.d64
PROGRAMS=\
	backup-ultimate.prg \
	restore-ultimate.prg \
	write-test.prg

LIBS = \
	backup.lib \
	ramlink/ramlink.lib \
	reu/reu.lib \
	ultimate/ultimate.lib

backup_SOURCES = \
	detect.c \
	timer-cia.c

all: ${DISK}

${DISK}: ${PROGRAMS} mkd64 filelist
	./mkd64 ${DISK} "ramlink backup,00" filelist

.SUFFIXES: .c .s .o

.c.o:
	cl65 -t c64 -c -O -g -o $@ $<

.s.o:
	cl65 -t c64 -c -g -o $@ $<

backup.lib: ${backup_SOURCES:.c=.o}
	ar65 r backup.lib ${backup_SOURCES:.c=.o}

backup-ultimate.prg: backup-ultimate.o ${LIBS}
	cl65 -t c64 -o backup-ultimate.prg backup-ultimate.o ${LIBS}

restore-ultimate.prg: restore-ultimate.o ${LIBS}
	cl65 -t c64 -o restore-ultimate.prg restore-ultimate.o ${LIBS}

write-test.prg: write-test.o ${LIBS}
	cl65 -t c64 -o write-test.prg write-test.o ${LIBS}
