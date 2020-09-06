DISK=ramlink-backup.d64
PROGRAMS=\
	backup-reu.prg \
	backup-ultimate.prg \
	detect-ramlink.prg \
	detect-reu.prg \
	detect-ultimate.prg

all: ${DISK}

${DISK}: ${PROGRAMS} mkd64 filelist
	./mkd64 ${DISK} "ramlink backup,00" filelist

.SUFFIXES: .c .s .o

.c.o:
	cl65 -t c64 -c -O -g -o $@ $<

.s.o:
	cl65 -t c64 -c -g -o $@ $<

backup-reu.prg: backup-reu.o ramlink/ramlink.lib reu/reu.lib
	cl65 -t c64 -o backup-reu.prg backup-reu.o ramlink/ramlink.lib reu/reu.lib

backup-ultimate.prg: backup-ultimate.o ramlink/ramlink.lib ultimate/ultimate.lib
	cl65 -t c64 -o backup-ultimate.prg backup-ultimate.o ramlink/ramlink.lib ultimate/ultimate.lib

detect-ramlink.prg: detect-ramlink.o ramlink/ramlink.lib
	cl65 -t c64 -o detect-ramlink.prg detect-ramlink.o ramlink/ramlink.lib

detect-reu.prg: detect-reu.o reu/reu.lib
	cl65 -t c64 -o detect-reu.prg detect-reu.o reu/reu.lib

detect-ultimate.prg: detect-ultimate.o ultimate/ultimate.lib
	cl65 -t c64 -o detect-ultimate.prg detect-ultimate.o ultimate/ultimate.lib
