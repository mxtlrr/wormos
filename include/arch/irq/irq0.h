#pragma once

#include "arch/idt/isr.h"
#include "libc/stdio.h"

void init_pit(uint32_t freq);