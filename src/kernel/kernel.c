#include "libc/stdio.h"
#include "arch/idt/idt.h"

void kmain(void){
  init();
  
  printf("GDT is up.\n");
  idt_init();
  asm("sti");
  printf("IDT Enabled.\n");

  // we are free do thing.
  puts("Hello, World!\n");
  for(;;) asm("hlt");
}