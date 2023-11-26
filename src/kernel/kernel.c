#include "libc/stdio.h"
#include "arch/idt/idt.h"

void kmain(void){
  init();
  
  puts("Hello, World!\n");
  idt_init();
  printf("IDT Enabled.\n");

  for(;;) __asm__("hlt");
}