#pragma once

#include "arch/idt/isr.h"
#include "libc/stdio.h"
#include "io.h"

void register_kbd(void); // not much else to say
void write_prompt();
