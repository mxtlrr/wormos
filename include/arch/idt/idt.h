#pragma once

#include <stdint.h>
#include <stddef.h>
#include "libc/string.h"

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

extern void idt_flush(uint32_t);

void idt_set_descriptor(uint8_t num, uint32_t base, uint8_t flags);
void idt_init(void);

extern void isr0 ();
extern void isr1 ();
extern void isr2 ();
extern void isr3 ();
extern void isr4 ();
extern void isr5 ();
extern void isr6 ();
extern void isr7 ();
extern void isr8 ();
extern void isr9 ();
extern void isr10();
extern void isr11();
extern void isr12();
extern void isr13();
extern void isr14();
extern void isr15();
extern void isr16();
extern void isr17();
extern void isr18();
extern void isr19();
extern void isr20();
extern void isr21();
extern void isr22();
extern void isr23();
extern void isr24();
extern void isr25();
extern void isr26();
extern void isr27();
extern void isr28();
extern void isr29();
extern void isr30();
extern void isr31();