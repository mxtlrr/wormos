#include "arch/idt/idt.h"

__attribute__((aligned(0x10)))
idt_entry_t idt_entries[256];
idtr_t idt_ptr;

void idt_set_descriptor(uint8_t num, uint32_t base, uint8_t flags){
  idt_entries[num].isr_low = base & 0xFFFF;
  idt_entries[num].isr_high = (base >> 16) & 0xFFFF;

  idt_entries[num].kernel_cs = 0x08;
  idt_entries[num].reserved = 0;
  idt_entries[num].attributes = flags;
}

void idt_init(){
  idt_ptr.limit = sizeof(idt_entry_t) * 256 -1;
  idt_ptr.base  = (uint32_t)&idt_entries;

  memset(&idt_entries, 0, sizeof(idt_entry_t)*256);

  idt_set_descriptor(0, (uint32_t)isr0, 0x8E);
  idt_set_descriptor(1, (uint32_t)isr1, 0x8E);
  idt_set_descriptor(2, (uint32_t)isr2, 0x8E);
  idt_set_descriptor(3, (uint32_t)isr3, 0x8E);
  idt_set_descriptor(4, (uint32_t)isr4, 0x8E);
  idt_set_descriptor(5, (uint32_t)isr5, 0x8E);
  idt_set_descriptor(6, (uint32_t)isr6, 0x8E);
  idt_set_descriptor(7, (uint32_t)isr7, 0x8E);
  idt_set_descriptor(8, (uint32_t)isr8, 0x8E);
  idt_set_descriptor(9, (uint32_t)isr9, 0x8E);
  idt_set_descriptor(10, (uint32_t)isr10, 0x8E);
  idt_set_descriptor(11, (uint32_t)isr11, 0x8E);
  idt_set_descriptor(12, (uint32_t)isr12, 0x8E);
  idt_set_descriptor(13, (uint32_t)isr13, 0x8E);
  idt_set_descriptor(14, (uint32_t)isr14, 0x8E);
  idt_set_descriptor(15, (uint32_t)isr15, 0x8E);
  idt_set_descriptor(16, (uint32_t)isr16, 0x8E);
  idt_set_descriptor(17, (uint32_t)isr17, 0x8E);
  idt_set_descriptor(18, (uint32_t)isr18, 0x8E);
  idt_set_descriptor(19, (uint32_t)isr19, 0x8E);
  idt_set_descriptor(20, (uint32_t)isr20, 0x8E);
  idt_set_descriptor(21, (uint32_t)isr21, 0x8E);
  idt_set_descriptor(22, (uint32_t)isr22, 0x8E);
  idt_set_descriptor(23, (uint32_t)isr23, 0x8E);
  idt_set_descriptor(24, (uint32_t)isr24, 0x8E);
  idt_set_descriptor(25, (uint32_t)isr25, 0x8E);
  idt_set_descriptor(26, (uint32_t)isr26, 0x8E);
  idt_set_descriptor(27, (uint32_t)isr27, 0x8E);
  idt_set_descriptor(28, (uint32_t)isr28, 0x8E);
  idt_set_descriptor(29, (uint32_t)isr29, 0x8E);
  idt_set_descriptor(30, (uint32_t)isr30, 0x8E);
  idt_set_descriptor(31, (uint32_t)isr31, 0x8E);

  /* irq time! 
   * first we need to tell the PIC we're gonna
   * do some funky stuff */
  outb(0x20, 0x11);
  outb(0xA0, 0x11);
  outb(0x21, 0x20);
  outb(0xA1, 0x28);
  outb(0x21, 0x04);
  outb(0xA1, 0x02);
  outb(0x21, 0x01);
  outb(0xA1, 0x01);
  outb(0x21, 0x0);
  outb(0xA1, 0x0);

  /* badabing bada boom! part 1/2 of the C code is done!
   * now we need to set the IRQ descriptors for 32-47 */
  idt_set_descriptor(32, (uint32_t)irq0, 0x8e);
  idt_set_descriptor(33, (uint32_t)irq1, 0x8e);
  idt_set_descriptor(34, (uint32_t)irq2, 0x8e);
  idt_set_descriptor(35, (uint32_t)irq3, 0x8e);
  idt_set_descriptor(36, (uint32_t)irq4, 0x8e);
  idt_set_descriptor(37, (uint32_t)irq5, 0x8e);
  idt_set_descriptor(38, (uint32_t)irq6, 0x8e);
  idt_set_descriptor(39, (uint32_t)irq7, 0x8e);
  idt_set_descriptor(40, (uint32_t)irq8, 0x8e);
  idt_set_descriptor(41, (uint32_t)irq9, 0x8e);
  idt_set_descriptor(42, (uint32_t)irq10, 0x8e);
  idt_set_descriptor(43, (uint32_t)irq11, 0x8e);
  idt_set_descriptor(44, (uint32_t)irq12, 0x8e);
  idt_set_descriptor(45, (uint32_t)irq13, 0x8e);
  idt_set_descriptor(46, (uint32_t)irq14, 0x8e);
  idt_set_descriptor(47, (uint32_t)irq15, 0x8e);
  
  /* part 2/2 done! now its up to our assembly to do thing */
  idt_flush((uint32_t)&idt_ptr);
}