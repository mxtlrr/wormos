#pragma once

#include <stdint.h>

/* important PIC stuff */
#define M_PIC_CMD  0x0020  // master PIC command
#define M_PIC_DATA 0x0021  // master PIC data
#define S_PIC_CMD  0x00a0
#define S_PIC_DATA 0x00a1


uint8_t inb(uint16_t port);
void outb(uint16_t port, uint8_t val);

#define iowait outb(0x80, 0x0);