#include "arch/gdt.h"

gdt_entry_t gdt_entries[5];
gdt_ptr_t   gdtr;

void init_gdt(){
  gdtr.lim  = (sizeof(gdt_entry_t)*5)-1;
  gdtr.base = (uint32_t)&gdt_entries;

  gdt_set_desc(0,0,0,0);
  gdt_set_desc(1,0,LIMIT,0x9a);
  gdt_set_desc(2,0,LIMIT,0x92); 

  // user mode
  gdt_flush((uint32_t)&gdtr);
}

void gdt_set_desc(int num, uint32_t base,
                  uint32_t lim, uint8_t access){
  gdt_entries[num].low_base  = (base & 0xFFFF);
  gdt_entries[num].mid_base  = (base>>16)&0xFF;
  gdt_entries[num].high_base = (base>>24)&0xFF;
  
  gdt_entries[num].low_lim = (lim & 0xFFFF);
  gdt_entries[num].granularity = (lim >> 16) & 0x0F;

  gdt_entries[num].granularity |= GRANULARITY & 0xF0;
  gdt_entries[num].access = access;
}