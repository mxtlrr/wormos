#include "libc/stdio.h"
#include "arch/idt/idt.h"

#include "arch/irq/irq0.h"

void kmain(void){
  init();
  
  printf("GDT is up.\n");
  idt_init();
  printf("IDT Enabled.\n");

  // we are free do thing.
  puts("Hello, World!\n");

  init_pit(50);
  for(;;){
    asm("hlt");
  }
}