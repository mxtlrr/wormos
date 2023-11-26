#include "libc/stdio.h"
#include "arch/idt/idt.h"

void kmain(void){
  init();
  
  puts("Hello, World!\n");
  idt_init();
  puts("IDT Enabled.\n");
  asm("int $0x5");
}