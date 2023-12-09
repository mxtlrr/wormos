#pragma once

#include "mem/mmap.h"
#include "libc/stdio.h"

#include <stddef.h>
#include <stdint.h>


#define BLOCK_TAKEN 0x41		// We cannot use this block!
#define BLOCK_AVAIL 0x00		// We can use this block

typedef struct {
	uint32_t address;	// address pointing to the beginning of
										// the block
	uint8_t avail_st; // is the block available for us to use?
} block_t;

// Add entries to a block
void add_mmap_entries_to_block(mmap_entry_t* block_arr);

/* Outline of malloc:
 * 1. First we look through the memory map, and see if there
 * are any blocks that are equal to the "size" varialble.
 * 2. If there are none, return NULL.
 * 3. If there are, we will split the block into two:
 * 	-> The unused one, and
 * 	-> The used one.
 * 4. Return the address of the used one. */
uint32_t kmalloc(uint32_t size);

// Run malloc but format the allocated space to zeros
void calloc(uint32_t block);

/* Set the block to free. */
void kfree(uint32_t addr);
