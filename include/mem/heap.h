#pragma once

#include <stdint.h>
#include "libc/string.h"

#define FREE  0xFF
#define ALLOC 0x00

struct m_seg {
	uint32_t mem_len; 			// length of memory
	struct m_seg* next_b;   // next block (free or not)
	struct m_seg* prev_b;	  // previous block
	struct m_seg* next_fb;  // next free block
	struct m_seg* prev_fb;  // previous free block
	int free;								// is the block free or not?
};

// Initialize the heap at heap_addr, it goes to heap_len
void init_heap(uint32_t heap_addr, uint32_t heap_len);
void* malloc(uint32_t size);
void free(void* addr);
