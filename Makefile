SUBDIRS = ramlink reu ultimate

DISK=ramlink-backup.d64
PROGRAMS=\
	tachyon-rl.prg \
	rl-reu.prg \
	write-test.prg

LIBS = \
	tachyon.lib \
	ramlink/ramlink.lib \
	reu/reu.lib \
	ultimate/ultimate.lib

backup_SOURCES = \
	backup.c \
	backup-dos.c \
	backup-reu.c \
	backup-reu-dma.c \
	buffer.c \
	detect.c \
	restore.c \
	restore-dos.c \
	restore-reu.c \
	restore-reu-dma.c \
	timer-cia.c

all: ${DISK}

${DISK}: ${PROGRAMS} mkd64 filelist
	./mkd64 ${DISK} "tachyon rl,00" filelist

.SUFFIXES: .c .s .o

.c.o:
	cl65 -t c64 -c -O -g -o $@ $<

.s.o:
	cl65 -t c64 -c -g -o $@ $<

tachyon.lib: ${backup_SOURCES:.c=.o}
	ar65 r $@ ${backup_SOURCES:.c=.o}

tachyon-rl.prg: main.o ${LIBS}
	cl65 -t c64 -o $@ main.o ${LIBS}

write-test.prg: write-test.o ${LIBS}
	cl65 -t c64 -o $@ write-test.o ${LIBS}

rl-reu.prg: rl-reu.o ${LIBS}
	cl65 -t c64 -o $@ rl-reu.o ${LIBS}
