all: detect.prg

detect.prg: detect.c reu.c reu.h
	cl65 -o detect.prg -t c64 detect.c reu.c

test.prg: test.s
	cl65 -o test.prg -u __EXEHDR__ -t c64 -C c64-asm.cfg test.s
