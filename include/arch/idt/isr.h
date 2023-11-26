#pragma once

#include "libc/stdio.h"

typedef struct {
  uint32_t ds;
  uint32_t edi, esi, ebp, esp, ebx, edx, ecx, eax;
  uint32_t irq_n, ec;
  uint32_t ip, cs, eflags, useless, ss;
} registers_t;

__attribute__((noreturn))
void exception_handler(registers_t regs);