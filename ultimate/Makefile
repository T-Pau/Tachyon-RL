LIB=ultimate.lib

SOURCES=\
	ci-ascii2pet.c \
	ci-detect.c \
	ci-done.c \
	ci-execute.c \
	ci-read.c \
	ci-status.c \
	ci-write.c \
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
	dos-identify.c \
	dos-open-file.c \
	dos-read-data.c \
	dos-rename-file.c \
	dos-write-data.c

all: ${LIB}

.SUFFIXES: .c .s .o

.c.o:
	cl65 -t c64 -c -O -g -o $@ $<

.s.o:
	cl65 -t c64 -c -g -o $@ $<

${LIB}: ${SOURCES:.c=.o}
	ar65 r ${LIB} ${SOURCES:.c=.o}
