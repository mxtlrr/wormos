#pragma once

#include <stdint.h>
#include <stddef.h>

#define DESCRIPTOR 0x08

typedef struct {
  uint16_t isr_low;
  uint16_t kernel_cs; // 0x08
  uint8_t  reserved;
  uint8_t  attributes;
  uint16_t isr_high;
}__attribute__((packed)) idt_entry_t;

typedef struct {
  uint16_t limit;
  uint32_t base;
}__attribute__((packed)) idtr_t;

extern void* isr_stub_table[];

void idt_set_descriptor(uint8_t vector, void* isr, uint8_t flags);
void idt_init(void);