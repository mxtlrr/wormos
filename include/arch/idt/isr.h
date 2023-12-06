#pragma once

#include "libc/stdio.h"
#include "io.h"

typedef struct {
  uint32_t ds;
  uint32_t edi, esi, ebp, useless, ebx, edx, ecx, eax;
  uint32_t irq_n, ec;
  uint32_t ip, cs, eflags, esp, ss;
} registers_t;

__attribute__((noreturn))
void exception_handler(registers_t regs);


typedef void (*isr_t)(registers_t);

void irq_hdlr(registers_t regs);