LIB=ultimate.lib

SOURCES=\
	ci-detect.c \
	ci-done.c \
	ci-execute.c \
	ci-read.c \
	ci-status.c \
	ci-write.c \
	dos-close-file.c \
	dos-cmd.c \
	dos-identify.c \
	dos-open-file.c \
	dos-read-data.c \
	dos-write-data.c

all: ${LIB}

.SUFFIXES: .c .s .o

.c.o:
	cl65 -t c64 -c -O -g -o $@ $<

.s.o:
	cl65 -t c64 -c -g -o $@ $<

${LIB}: ${SOURCES:.c=.o}
	ar65 r ${LIB} ${SOURCES:.c=.o}
