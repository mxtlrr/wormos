#include "arch/idt/isr.h"

void exception_handler(registers_t regs){
  terminal_setcolor(VGA_COLOR_RED);
  puts("Interrupt recieved! System halted.");
  for(;;) __asm__("cli; hlt");
  
}