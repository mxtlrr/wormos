#include "libc/stdio.h"
#include "libc/string.h"

uint8_t vga_entry_color(enum vga_color fg, enum vga_color bg) {
	return fg | bg << 4;
}
 
uint16_t vga_entry(unsigned char uc, uint8_t color) {
	return (uint16_t) uc | (uint16_t) color << 8;
}
 

size_t y;
size_t x;
uint8_t terminal_color;
uint16_t* terminal_buffer;
 
void init(void) {
	y = 0;
	x = 0;
	terminal_color = vga_entry_color(VGA_COLOR_WHITE, VGA_COLOR_BLACK);
	terminal_buffer = (uint16_t*) 0xB8000;
	for (size_t x = 0; x < VGA_HEIGHT; x++) {
		for (size_t y = 0; y < VGA_WIDTH; y++) {
			const size_t index = x * VGA_WIDTH + y;
			terminal_buffer[index] = vga_entry(' ', terminal_color);
		}
	}
}
 
void terminal_setcolor(uint8_t color) {
	terminal_color = color;
}
 
void _putc(char c, uint8_t color, size_t y, size_t x) 
{
	const size_t index = x * VGA_WIDTH + y;
	terminal_buffer[index] = vga_entry(c, color);
}

#define TAB_LEN 2
void putc(char c) {
	switch(c){
		case '\n':
			x = 0;
			y++;
			break;

		case '\t':
			x+=TAB_LEN;
			break;
		
		default:
			_putc(c, terminal_color, x, y);
			if (++x == VGA_WIDTH) {
				x = 0;
				if (++y == VGA_HEIGHT) y = 0;
			}
			break;
	}
  move_cursor(x,y);
	scroll();
}
 
void puts(char* fmt) {
	for (size_t i = 0; i < strlen(fmt); i++)
		putc(fmt[i]);
}


void printf(char* fmt, ...) {
	va_list ap;
	va_start(ap, fmt);

	char* ptr;

	for (ptr = fmt; *ptr != '\0'; ++ptr) {
		if (*ptr == '%') {
			++ptr;
			switch (*ptr) {
				case 's':	// string
					puts(va_arg(ap, char*));
					break;
				case 'd': // integer
					puts(itoa(va_arg(ap, int), 10));
					break;
				case 'x': // hexadecimal
					puts(itoa(va_arg(ap, uint32_t), 16));
					break;
				case 'c':
					putc(va_arg(ap, int));
					break;
				
				case 'o': // not octal, we need to change the Output cOlOr
					terminal_setcolor(va_arg(ap, int));
					break;
			}
		} else {
			char t[2] = { *ptr, 0 };
			puts(t);
		}
	}
}


#include "io.h"
void move_cursor(int x, int y){
  uint16_t pos = y * VGA_WIDTH + x;
 
	outb(0x3D4, 0x0F);
	outb(0x3D5, (uint8_t) (pos & 0xFF));
	outb(0x3D4, 0x0E);
	outb(0x3D5, (uint8_t) ((pos >> 8) & 0xFF));
}

void scroll(){
	uint8_t  attrib = (0<<4) | (15 & 0x0F);
	uint16_t blank = 0x20 | (attrib<<8);

	if(y >= 25){
		int i = 0;
		for(i=0;i<(24*80);i++) terminal_buffer[i] = terminal_buffer[i+80];
		for(i=(24*80);i<(25*80);i++) terminal_buffer[i] = blank; // clear!
		y = 24;
	}
}


void dc_putc(char c){
	outb(0xe9, c);
}

void dc_puts(char* fmt){
	for(int i = 0; i < strlen(fmt); i++)
		dc_putc(fmt[i]);
}
void dc_printf(char* fmt, ...){
	va_list ap;
	va_start(ap, fmt);

	char* ptr;

	for (ptr = fmt; *ptr != '\0'; ++ptr) {
		if (*ptr == '%') {
			++ptr;
			switch (*ptr) {
				case 's':	// string
					dc_puts(va_arg(ap, char*));
					break;
				case 'd': // integer
					dc_puts(itoa(va_arg(ap, int), 10));
					break;
				case 'x': // hexadecimal
					dc_puts(itoa(va_arg(ap, uint32_t), 16));
					break;
				case 'c':
					dc_putc(va_arg(ap, int));
					break;
			}
		} else {
			char t[2] = { *ptr, 0 };
			dc_puts(t);
		}
	}
}

void splash(){
	printf("\t\t\t\t\t\t                           (o)(o)   \n");
	printf("\t\t\t\t\t\t                          /     \\  \n");
	printf("\t\t\t\t\t\t                         /       |  \n");
	printf("\t\t\t\t\t\t                        /   \\  * | \n");
	printf("\t\t\t\t\t\t          ________     /    /\\__/  \n");
	printf("\t\t\t\t\t\t  _      /        \\   /    /       \n");
	printf("\t\t\t\t\t\t / \\    /  ____    \\_/    /	 	    \n");
	printf("\t\t\t\t\t\t//\\ \\  /  /    \\         /			  \n");
	printf("\t\t\t\t\t\tV  \\ \\/  /      \\       /		 	 	\n");
	printf("\t\t\t\t\t\t    \\___/        \\_____/			 	 	\n");
}