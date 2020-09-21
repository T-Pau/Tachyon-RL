LIB=ultimate.lib

CC = cl65
CFLAGS = -t c64 -O -g

SOURCES=\
	ci-ascii2pet.c \
	ci-detect.c \
	ci-done.c \
	ci-execute.c \
	ci-read.s \
	ci-status.c \
	ci-write.s \
	ci-write-string.c \
	dos-buffer.c \
	dos-change-dir.c \
	dos-close-file.c \
	dos-copy-file.c \
	dos-copy-home-path.c \
	dos-copy-ui-path.c \
	dos-create-dir.c \
	dos-delete-file.c \
	dos-file-info.c \
	dos-file-seek.c \
	dos-file-stat.c \
	dos-get-path.c \
	dos-get-string.c \
	dos-get-time.c \
	dos-identify.c \
	dos-load-reu.c \
	dos-open-file.c \
	dos-read-data.c \
	dos-rename-file.c \
	dos-save-reu.c \
	dos-write-data.c

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
