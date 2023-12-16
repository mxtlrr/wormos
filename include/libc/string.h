#pragma once

#include <stdint.h>
#include <stddef.h>

size_t strlen(const char* str);
char* itoa(uint32_t num, int base);
void *memset(void *s, int c, size_t n);


/* Check if s1 is equal to s2, if so,
 * return 0. Else, return 1 */
int strcmp(char* s1, char* s2);
