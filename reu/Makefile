LIB=reu.lib

CC = cl65
CFLAGS = -t c64 -O -g

SOURCES=\
	reu-copy.c \
	reu-detect.c

all: ${LIB}

TMP=${SOURCES:.c=.o}
OBJECTS = ${TMP:.s=.o}
DEPFILES = ${OBJECTS:.o=.d}

clean:
	rm -f ${OBJECTS} ${DEPFILES} ${LIB}

.PHONY: all clean

.SUFFIXES: .c .s .o

.c.o:
	@echo Compiling $<
	@${CC} ${CFLAGS} --create-dep $(<:.c=.d) -c -o $@ $<

.s.o:
	@echo Compiling $<
	@${CC} ${CFLAGS} -c -o $@ $<

${LIB}: ${OBJECTS}
	@echo Linking $@
	@ar65 r ${LIB} ${OBJECTS}

-include ${DEPFILES}
