#include "libc/string.h"

size_t strlen(const char* str) {
	size_t len = 0;
	while (str[len])
		len++;
	return len;
}

int strcmp(char* s1, char* s2){
  const unsigned char *p1 = (const unsigned char *) s1;
  const unsigned char *p2 = (const unsigned char *) s2;
  unsigned char c1, c2;
  do {
		c1 = (unsigned char) *p1++;
		c2 = (unsigned char) *p2++;
	  if (c1 == '\0') return c1 - c2;
  } while (c1 == c2);
  return c1 - c2;
}

char* itoa(uint32_t num, int base){
	static char repr[] = "0123456789ABCDEF";
	static char buffer[50];
	char* ptr;

	ptr  = &buffer[49];
	*ptr = '\0';

	do {
		*--ptr = repr[num%base];
		num /= base;
	} while(num != 0);

	return ptr;
}

void *memset(void *s, int c, size_t n) {
	uint8_t *p = (uint8_t *)s;

	for (size_t i = 0; i < n; i++)
		p[i] = (uint8_t)c;

	return s;
}
