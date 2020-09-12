#include "timer.h"

#include <cbm.h>

#include <stdio.h>

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
	putchar(':');
	output_bcd(CIA1.tod_min);
	putchar(':');
	output_bcd(CIA1.tod_sec);
	putchar('.');
	output_bcd_single(CIA1.tod_10);
}

static void output_bcd(unsigned char value) {
	putchar((value >> 4) | 0x30);
	putchar((value & 0xf) | 0x30);
}

static void output_bcd_single(unsigned char value) {
	putchar((value & 0xf) | 0x30);
}
