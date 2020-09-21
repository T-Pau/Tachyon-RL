SUBDIRS = drive ramlink reu ultimate

DISK=Tachyon-RL.d64

VERSION=1.0.1

CC = cl65
CFLAGS = -t c64 -O -g

PROGRAMS=\
	tachyon-rl.prg

LIBS = \
	tachyon.lib \
	drive/drive.lib \
	ramlink/ramlink.lib \
	reu/reu.lib \
	ultimate/ultimate.lib

lib_SOURCES = \
	backup.c \
	backup-dos.c \
	backup-reu.c \
	backup-reu-dma.c \
	backup-sd2iec.c \
	buffer.c \
	clear-lines.c \
	detect.c \
	detect_cpu.c \
	help.c \
	help_screen.s \
	restore.c \
	restore-dos.c \
	restore-reu.c \
	restore-reu-dma.c \
	restore-sd2iec.c \
	speed-factor.c \
	timer-cia.c

prg_SOURCES = \
	tachyon-rl.c \
	drives.c \
	read-test.c \
	sd2iec-write.c \
	write-test.c

TMP=${lib_SOURCES:.c=.o}
lib_OBJECTS = ${TMP:.s=.o}

DEPFILES = ${lib_OBJECTS:.o=.d} ${prg_SOURCES:.c=.d}

.PHONY: all clean dist subdirs

all: subdirs ${DISK}

dist: all
	zip -9rq Tachyon-RL-${VERSION}.zip README.md Tachyon-RL.d64 tachyon-rl.prg

clean:
	rm -f ${lib_OBJECTS} ${prg_SOURCES:.c=.prg} ${prg_SOURCES:.c=.o} ${DEPFILES}
	@for dir in ${SUBDIRS}; \
	do \
		(cd $$dir && make clean) || exit 1; \
	done

subdirs:
	@for dir in ${SUBDIRS}; \
	do \
		(cd $$dir && make) || exit 1; \
	done

${DISK}: ${PROGRAMS} mkd64 filelist
	./mkd64 ${DISK} "tachyon rl,00" filelist

.SUFFIXES: .c .s .o .prg .d64

.c.o:
	@echo Compiling $<
	@${CC} ${CFLAGS} --create-dep $(<:.c=.d) -c -o $@ $<

.s.o:
	@echo Compiling $<
	@${CC} ${CFLAGS} -c -o $@ $<
	
.o.prg:
	@echo Linking $@
	@${CC} ${CFLAGS} -o $@ $< ${LIBS}

.prg.d64:
	prg2d64 $<

tachyon.lib: ${lib_OBJECTS}
	@echo Linking $@
	@ar65 r $@ ${lib_OBJECTS}

tachyon-rl.prg: tachyon-rl.o ${LIBS}

read-test.prg: read-test.o ${LIBS}
write-test.prg: write-test.o ${LIBS}
rl-reu.prg: rl-reu.o ${LIBS}
drives.prg: drives.o ${LIBS}

sd2iec-write.prg: sd2iec-write.o ${LIBS}
	@echo Linking $@
	@${CC} ${CFLAGS} -Ln sym -o $@ $< ${LIBS}

sd2iec-read.prg: sd2iec-read.o ${LIBS}
	@echo Linking $@
	@${CC} ${CFLAGS} -Ln sym -o $@ $< ${LIBS}

-include ${DEPFILES}
