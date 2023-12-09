#include "mem/mm.h"


block_t blocks[256];

void add_mmap_entries_to_block(mmap_entry_t* block_arr){
	// we know  how many blocks there are
	for(int i = 0; i < 257; i++){
		block_t n_block = {
			.address = block_arr[i].where_is,
			.avail_st = block_arr[i].availability
		};

		blocks[i] = n_block;
	}
}
