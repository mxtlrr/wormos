#include "mem/heap.h"

struct m_seg* ffms; // first free mem seg

void init_heap(uint32_t heap_addr, uint32_t heap_len){
	ffms = (struct m_seg*)heap_addr;
	ffms->mem_len = heap_len - sizeof(struct m_seg);
	ffms->next_b  = 0;
	ffms->prev_b  = 0;
	ffms->next_fb = 0;
	ffms->prev_fb = 0;
	ffms->free = FREE;
};

void* malloc(uint32_t size){
	uint32_t r = size%8; // get size in bits
	size -= r;
	if(r != 0) size += 8;

	struct m_seg* cm = ffms; // current memory segment
	
	for(;;){ // loop through until we get a match
		if(cm->mem_len >= size){ // yes!
			if(cm->mem_len > size + sizeof(struct m_seg)){
				struct m_seg* ns = (struct m_seg*)((uint32_t)cm + sizeof(struct m_seg) + size);

				ns->free 		= FREE;
				ns->mem_len = ((uint32_t)cm->mem_len) - (sizeof(struct m_seg) + size);
				ns->next_fb = cm->next_fb;
				ns->next_b  = cm->next_b;
				ns->prev_b  = cm;
				ns->prev_fb = cm->prev_fb;

				cm->next_fb = ns;
				cm->next_b  = ns;
				cm->mem_len = size;
			}

			if(cm == ffms) ffms = cm->next_fb;
			cm->free = ALLOC;

			if(cm->prev_fb != 0) cm->prev_fb->next_fb = cm->next_fb;
			if(cm->next_fb != 0) cm->next_fb->prev_fb = cm->prev_fb;
			if(cm->prev_b  != 0) cm->prev_b->next_b   = cm->next_fb;
			if(cm->next_b  != 0) cm->next_b->prev_fb  = cm->prev_fb;

			return cm + 1;
		}

		if(cm->next_fb == 0) return 0;
		cm = cm->next_fb;
	}
	return 0;
}

void add_free(struct m_seg* a, struct m_seg* b){
	if(a == 0 || b == 0) return;
	if(a<b){
		a->mem_len += b->mem_len + sizeof(struct m_seg);
		a->next_b  = b->next_b;
		a->next_fb = b->next_fb;
		b->next_b->prev_b  = a;
		b->next_b->prev_fb = a;
		b->next_fb->prev_fb = a;
	} else {
		b->mem_len += a->mem_len + sizeof(struct m_seg);
		b->next_b  = a->next_b;
		b->next_fb = a->next_fb;
		a->next_b->prev_b  = b;
		a->next_b->prev_fb = b;
		a->next_fb->prev_fb = b;
	}
}

void free(void* ptr){
	struct m_seg* cm = ((struct m_seg*)ptr) - 1;
	cm->free = FREE;

	if(cm < ffms) ffms = cm;
	if(cm->next_fb != 0)
		if(cm->next_fb->prev_fb < cm) cm->next_fb->prev_fb = cm;

	if(cm->prev_fb != 0)
		if(cm->prev_fb->next_fb > cm) cm->prev_fb->next_fb = cm;

	if(cm->next_b != 0){
		cm->next_b->prev_b = cm;
		if(cm->next_b->free == FREE) add_free(cm, cm->next_b);
	}

	if(cm->prev_b != 0){
		cm->prev_b->next_b = cm;
		if((cm->prev_b->free) == FREE) add_free(cm, cm->prev_b);
	}
}







