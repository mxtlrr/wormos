#pragma once

#include <stdint.h>
#include <stddef.h>

#include "libc/stdio.h"
#include "multiboot.h"

#define MAGIC_NUM_CONV 1047964
#define BLOCKS 256


enum MMAP_TYPE {
  MMAP_RESERVED  = 0,    // we cannot use this!
  MMAP_AVAILABLE = 1     // we can use this :)
  /* all we care about now. Fuck ACPI (for now) */
};

typedef struct {
  uint32_t where_is;      // where is the mmap entry?
  uint32_t length;        // length of the mmap entry
  uint32_t availability;
} mmap_entry_t;


int get_mem_available(multiboot_info_t* mbd);

void add_entries(multiboot_info_t* mbd);
mmap_entry_t get_entry(int position);