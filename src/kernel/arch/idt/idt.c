#include "arch/idt/idt.h"

__attribute__((aligned(0x10)))
idt_entry_t idt[256];
idtr_t idtr;

void idt_set_descriptor(uint8_t vector, void* isr, uint8_t flags){
  idt_entry_t* descriptor = &idt[vector];

  descriptor->isr_low    = (uint32_t)isr & 0xFFFF;
  descriptor->kernel_cs  = DESCRIPTOR;
  descriptor->attributes = flags;
  descriptor->isr_high   = (uint32_t)isr >> 16;
  descriptor->reserved   = 0;
}

void idt_init(){
  idtr.base  = (uintptr_t)&idt[0];
  idtr.limit = (uint16_t)sizeof(idt_entry_t) * 256 - 1;

  // past 31 is IRQs
  for(uint8_t vector = 0; vector < 32; vector++){
    idt_set_descriptor(vector, isr_stub_table[vector], 0x8e);
    // idt[vector] = 1;
  }

  __asm__ volatile("lidt %0" :: "m"(idtr));
  __asm__("sti");
}