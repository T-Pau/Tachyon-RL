LIB=drive.lib

SOURCES=\
	drive-command.c \
	drive-detect.c \
	drive-identify.c

TMP=${SOURCES:.c=.o}
OBJECTS = ${TMP:.s=.o}

all: ${LIB}

.SUFFIXES: .c .s .o

.c.o:
	cl65 -t c64 -c -O -g -o $@ $<

.s.o:
	cl65 -t c64 -c -g -o $@ $<

${LIB}: ${OBJECTS}
	ar65 r ${LIB} ${OBJECTS}
