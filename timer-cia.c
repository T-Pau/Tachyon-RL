#include "timer.h"

#include <cbm.h>

#include <conio.h>

static void output_bcd(unsigned char value);
static void output_bcd_single(unsigned char value);

void timer_start(void) {
	unsigned char x;
	CIA1.tod_hour = 0;
	CIA1.tod_10 = 0;
	CIA1.tod_min = 0;
	CIA1.tod_sec = 0;
	x = CIA1.tod_10;
}

void timer_stop(void) {
	unsigned char x;
	x = CIA1.tod_hour;
	CIA1.tod_hour = x;
}

void timer_output(void) {
	output_bcd(CIA1.tod_hour);
	cputc(':');
	output_bcd(CIA1.tod_min);
	cputc(':');
	output_bcd(CIA1.tod_sec);
	cputc('.');
	output_bcd_single(CIA1.tod_10);
}

static void output_bcd(unsigned char value) {
	cputc((value >> 4) | 0x30);
	cputc((value & 0xf) | 0x30);
}

static void output_bcd_single(unsigned char value) {
	cputc((value & 0xf) | 0x30);
}
