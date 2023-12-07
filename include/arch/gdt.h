#pragma once

#include <stddef.h>
#include <stdint.h>

#define GRANULARITY 0xcf
#define LIMIT       0xFFFFFFFF

typedef struct {
  uint16_t low_lim;  // lower 16 bits of limit
  uint16_t low_base; // lower 16 bits of base
  uint8_t  mid_base; // next 8 bits of base
  uint8_t  access;   // access flags
  uint8_t  granularity;
  uint8_t  high_base;
}__attribute__((packed)) gdt_entry_t;

typedef struct {
  uint16_t lim;
  uint32_t base;
}__attribute__((packed)) gdt_ptr_t;

extern void gdt_flush(uint32_t);
void gdt_set_desc(int num, uint32_t base,
                  uint32_t lim, uint8_t access);

void init_gdt();