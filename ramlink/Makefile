LIB=ramlink.lib

SOURCES=\
	ramlink-copy.c \
	ramlink-copy-block.c \
	ramlink-detect.c \
	ramlink-get-size.c \
	ramlink-get-time.c \
	ramlink-reu-dma.c

all: ${LIB}

.SUFFIXES: .c .s .o

.c.o:
	cl65 -t c64 -c -O -g -o $@ $<

.s.o:
	cl65 -t c64 -c -g -o $@ $<

${LIB}: ${SOURCES:.c=.o}
	ar65 r ${LIB} ${SOURCES:.c=.o}
