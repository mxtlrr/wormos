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
 
void putc(char c) {
  if(c == '\n'){
    x=0;
    y++;
  } else {
    _putc(c, terminal_color, x, y);
    if (++x == VGA_WIDTH) {
      x = 0;
      if (++y == VGA_HEIGHT)
        y = 0;
    }
  }
  move_cursor(x,y);
}
 
void puts(char* fmt) {
	for (size_t i = 0; i < strlen(fmt); i++)
		putc(fmt[i]);
}

#define STR  's'
#define INT  'd'
#define HEX  'x'
#define CHAR 'c'

void printf(char* fmt, ...) {
	va_list ap;
	va_start(ap, fmt);

	char* ptr;

	for (ptr = fmt; *ptr != '\0'; ++ptr) {
		if (*ptr == '%') {
			++ptr;
			switch (*ptr) {
				case STR:	// string
					puts(va_arg(ap, char*));
					break;
				case INT: // integer
					puts(itoa(va_arg(ap, int), 10));
					break;
				case HEX: // hexadecimal
					puts(itoa(va_arg(ap, uint32_t), 16));
					break;
				case CHAR:
					// GCC complains that you can't have 'char'
					// as a type for va_arg, so it must be int
					// char r[2] = { va_arg(ap, int), 0 }; // null terminate it
					putc(va_arg(ap, int));
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