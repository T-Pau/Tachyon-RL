SUBDIRS = ramlink reu ultimate

DISK=ramlink-backup.d64
PROGRAMS=\
	tachyon-rl.prg \
	read-test.prg \
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
	help.c \
	help_screen.s \
	restore.c \
	restore-dos.c \
	restore-reu.c \
	restore-reu-dma.c \
	timer-cia.c

TMP=${backup_SOURCES:.c=.o}
backup_OBJECTS = ${TMP:.s=.o}

all: subdirs ${DISK}

.PHONY: subdirs

subdirs:
	@for dir in ${SUBDIRS}; \
	do \
		(cd $$dir && make) || exit 1; \
	done

${DISK}: ${PROGRAMS} mkd64 filelist
	./mkd64 ${DISK} "tachyon rl,00" filelist

.SUFFIXES: .c .s .o

.c.o:
	cl65 -t c64 -c -O -g -o $@ $<

.s.o:
	cl65 -t c64 -c -g -o $@ $<

tachyon.lib: ${backup_OBJECTS}
	ar65 r $@ ${backup_OBJECTS}

tachyon-rl.prg: main.o ${LIBS}
	cl65 -t c64 -o $@ main.o ${LIBS}

read-test.prg: read-test.o ${LIBS}
	cl65 -t c64 -o $@ read-test.o ${LIBS}

write-test.prg: write-test.o ${LIBS}
	cl65 -t c64 -o $@ write-test.o ${LIBS}

rl-reu.prg: rl-reu.o ${LIBS}
	cl65 -t c64 -o $@ rl-reu.o ${LIBS}
