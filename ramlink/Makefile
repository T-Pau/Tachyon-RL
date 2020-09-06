LIB=ramlink.lib

SOURCES=\
	ramlink-copy.c \
	ramlink-detect.c

all: ${LIB}

.SUFFIXES: .c .s .o

.c.o:
	cl65 -t c64 -c -O -g -o $@ $<

.s.o:
	cl65 -t c64 -c -g -o $@ $<

${LIB}: ${SOURCES:.c=.o}
	ar65 r ${LIB} ${SOURCES:.c=.o}
