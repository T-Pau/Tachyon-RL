SUBDIRS = ramlink reu ultimate

DISK=ramlink-backup.d64
PROGRAMS=\
	backup-ultimate.prg \
	restore-ultimate.prg \
	write-test.prg

LIBS = \
	ramlink/ramlink.lib \
	reu/reu.lib \
	ultimate/ultimate.lib

all: ${DISK}

${DISK}: ${PROGRAMS} mkd64 filelist
	./mkd64 ${DISK} "ramlink backup,00" filelist

.SUFFIXES: .c .s .o

.c.o:
	cl65 -t c64 -c -O -g -o $@ $<

.s.o:
	cl65 -t c64 -c -g -o $@ $<

backup-ultimate.prg: backup-ultimate.o timer-cia.o ${LIBS}
	cl65 -t c64 -o backup-ultimate.prg backup-ultimate.o timer-cia.o ${LIBS}

restore-ultimate.prg: restore-ultimate.o timer-cia.o ${LIBS}
	cl65 -t c64 -o restore-ultimate.prg restore-ultimate.o timer-cia.o ${LIBS}

write-test.prg: write-test.o timer-cia.o ${LIBS}
	cl65 -t c64 -o write-test.prg write-test.o timer-cia.o ${LIBS}
