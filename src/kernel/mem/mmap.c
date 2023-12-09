#include "mem/mmap.h"

int get_mem_available(multiboot_info_t* mbd){
  int length_raw = 0;

	for(multiboot_uint32_t i = 0; i < mbd->mmap_length; i += sizeof(multiboot_memory_map_t)){
		multiboot_memory_map_t* mmmt = (multiboot_memory_map_t*)(mbd->mmap_addr + i);
		if(mmmt->type == MMAP_AVAILABLE) length_raw += mmmt->len_low;
	}

  return length_raw/MAGIC_NUM_CONV;
}


mmap_entry_t entries[BLOCKS];
void add_entries(multiboot_info_t* mbd){
  int _ent = 0;
  for(multiboot_uint32_t i = 0; i < mbd->mmap_length; i += sizeof(multiboot_memory_map_t)){
		multiboot_memory_map_t* mmmt = (multiboot_memory_map_t*)(mbd->mmap_addr + i);
    mmap_entry_t mmap_n = {
      .availability = mmmt->type,
      .length       = mmmt->len_low,
      .where_is     = mmmt->addr_low
    };
    entries[_ent] = mmap_n;
    _ent++;
  }
}

mmap_entry_t get_entry(int position){
  return entries[position];
}