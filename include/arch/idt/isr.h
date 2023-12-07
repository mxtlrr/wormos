#pragma once

#include "libc/stdio.h"
#include "io.h"

#define IRQ0  32
#define IRQ1  33
#define IRQ2  34
#define IRQ3  35
#define IRQ4  36
#define IRQ5  37
#define IRQ6  38
#define IRQ7  39
#define IRQ8  40
#define IRQ9  41
#define IRQ10 42
#define IRQ11 43
#define IRQ12 44
#define IRQ13 45
#define IRQ14 46
#define IRQ15 47

typedef struct {
  uint32_t ds;
  uint32_t edi, esi, ebp, useless, ebx, edx, ecx, eax;
  uint32_t irq_n, ec;
  uint32_t ip, cs, eflags, esp, ss;
} registers_t;

__attribute__((noreturn))
void exception_handler(registers_t regs);


typedef void (*isr_t)(registers_t);
void register_irq(uint8_t irq, isr_t hdlr);

void irq_hdlr(registers_t regs);