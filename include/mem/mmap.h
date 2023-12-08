#pragma once

#include <stdint.h>
#include <stddef.h>

#include "libc/stdio.h"
#include "multiboot.h"

#define MAGIC_NUM_CONV 1000000

int get_mem_available(multiboot_info_t* mbd);