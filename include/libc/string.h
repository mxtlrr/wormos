#pragma once

#include <stdint.h>
#include <stddef.h>

size_t strlen(const char* str);
char* itoa(uint32_t num, int base);
void *memset(void *s, int c, size_t n);