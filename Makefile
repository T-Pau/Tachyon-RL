DISK=ramlink-backup.d64
PROGRAMS=detect-ultimate.prg detect-reu.prg backup.prg

all: ${DISK}

${DISK}: ${PROGRAMS} mkd64 filelist
	./mkd64 ${DISK} "ramlink backup,00" filelist

.SUFFIXES: .c .s .o

.c.o:
	cl65 -t c64 -c -O -g -o $@ $<

.s.o:
	cl65 -t c64 -c -g -o $@ $<

detect-ultimate.prg: detect-ultimate.o ultimate-cli.o ultimate-dos.o
	cl65 -t c64 -o detect-ultimate.prg detect-ultimate.o ultimate-cli.o ultimate-dos.o

detect-reu.prg: detect.o reu.o
	cl65 -t c64 -o detect-reu.prg detect.o reu.o

backup.prg: backup.o ramlink.o ultimate-dos.o ultimate-cli.o
	cl65 -t c64 -o backup.prg backup.o ramlink.o ultimate-dos.o ultimate-cli.o

backup-reu.prg: backup-reu.o reu.o ramlink.o
	cl65 -t c64 -o backup-reu.prg backup-reu.o reu.o ramlink.o

test.prg: test.s
	cl65 -o test.prg -u __EXEHDR__ -t c64 -C c64-asm.cfg test.s
