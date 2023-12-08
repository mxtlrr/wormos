#include "mem/mmap.h"

int get_mem_available(multiboot_info_t* mbd){
  multiboot_uint32_t entry_no = 0;
  int length_raw = 0;

	for(int i = 0; i < mbd->mmap_length; i += sizeof(multiboot_memory_map_t)){
		multiboot_memory_map_t* mmmt = (multiboot_memory_map_t*)(mbd->mmap_addr + i);
		if(mmmt->type == 1) length_raw += mmmt->len_low;
	}

  return length_raw/MAGIC_NUM_CONV;
}