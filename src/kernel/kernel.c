#include "multiboot.h"
#include "libc/stdio.h"

#include "arch/gdt.h"
#include "arch/idt/idt.h"

/* irqs */
#include "arch/irq/irq0.h"
#include "arch/irq/irq1.h"

/* memory */
#include "mem/mmap.h"

void kmain(multiboot_info_t* mbd, uint32_t magic){
  if(magic != 0x2badb002){
    while(1); // don't boot
  }
  init();

  init_gdt();  
  printf("GDT is up.\n");
  idt_init();
  asm volatile("sti");
  printf("IDT Enabled.\n");

  // we are free do thing.
  dc_printf("Hello from debugcon!\n");

  
  /* start up*/
  printf("Starting up interrupts.\n");
  init_pit(50);
  register_kbd();  

  splash();


  if(!(mbd->flags >> 6 & 0x1)){ // is bit 6 not set?
    printf("No mmap provided!\n");
    for(;;) asm("cli\nhlt");
  }

  // mmap is provided!
  printf("\nDetected %o%d%o MB of RAM!\n", VGA_COLOR_LIGHT_GREEN,
                                         get_mem_available(mbd),
                                         VGA_COLOR_WHITE);

  // needed for irqs
  for(;;) asm("hlt");
}