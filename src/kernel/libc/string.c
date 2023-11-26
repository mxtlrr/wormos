#include "libc/string.h"

size_t strlen(const char* str) {
	size_t len = 0;
	while (str[len])
		len++;
	return len;
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
