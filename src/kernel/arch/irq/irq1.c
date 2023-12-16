#include "arch/irq/irq1.h"

#define PROMPT ">>"
void write_prompt(){
	puts(PROMPT);
}


char lookups[] = {
  0, 0, '1', '2',
	'3', '4', '5', '6',
	'7', '8', '9', '0',
	'-', '=', 0, 0,
	'q', 'w', 'e', 'r',
	't', 'y', 'u', 'i',
	'o', 'p', '[', ']',
	0, 0, 'a', 's',
	'd', 'f', 'g', 'h',
	'j', 'k', 'l', ';',
	'\'', '`', 0, '\\',
	'z', 'x', 'c', 'v',
	'b', 'n', 'm', ',',
	'.', '/', 0, '*',
	0, ' '
};
char shift_lookups[] = {
  0, 0, '!', '@',
	'#', '$', '%', '^',
	'&', '*', '(', ')',
	'_', '+', 0, 0,
	'Q', 'W', 'E', 'R',
	'T', 'Y', 'U', 'I',
	'O', 'P', '{', '}',
	0, 0, 'A', 'S',
	'D', 'F', 'G', 'H',
	'J', 'K', 'L', ':',
	'\'', '`', 0, '\\',
	'Z', 'X', 'C', 'v',
	'B', 'n', 'M', '<',
	'>', '?', 0, '*',
	0, ' ' 
};

int l_shift = 0;

char buf[256];
int buf_index = 0;

void kbd_call(){
  uint8_t c = inb(0x60);
  uint8_t nch = 0;
  uint8_t nch_CAP = 0;
  if(c < 0x3a) {
    nch     = lookups[c];
    nch_CAP = shift_lookups[c];
  }

  if(nch == 0){
		switch(c){
			case 0x2a: /* left shift pressed */
				l_shift = 1;
				break;
			case 0xaa: /* left shift released */
				l_shift = 0;
				break;

			case 0x9c: /* enter pressed */
				/* TODO: strcmp implementation */
				printf("\n\tbuf content: '%s'\n", buf);
				for(int i = 0; i != 256; i++) buf[i] = 0;
				buf_index = 0;

				write_prompt();
				break;


			case 0x0e: /* backspace pressed */
				buf[--buf_index] = 0x0; // remove from buffer
				size_t x = get_cur_x();
				_putc(0x00, 15, --x, get_cur_y());
				set_cur_x(x);
				move_cursor(get_cur_x(), get_cur_y());
				break;
		}
  } else {
    if(l_shift == 0) {
      putc(nch);
      buf[buf_index] = nch;
      buf_index++;
    }
    else {
      putc(nch_CAP);
      buf[buf_index] = nch_CAP;
      buf_index++;
    }
  }
}
void register_kbd(void){
  register_irq(IRQ1, &kbd_call);
  printf("\n"); // :3
}
