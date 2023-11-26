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
}
 
void puts(char* fmt) {
	for (size_t i = 0; i < strlen(fmt); i++)
		putc(fmt[i]);
}
