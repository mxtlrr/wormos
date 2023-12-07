#include "arch/irq/irq0.h"
uint32_t ticks=0;

void timer_loop(registers_t regs){
  // ticks++;
  printf("%d", regs.irq_n);
}

void init_pit(uint32_t freq){
  // this is NOW IRQ0!
  register_irq(IRQ0, &timer_loop);
  uint32_t div = 1193180/freq;

  outb(0x43, 0x36); // command byte to PIC

  uint8_t l = (uint8_t)(div&0xff);       // low
  uint8_t h = (uint8_t)((div>>8)&0xff);  // high

  outb(0x40, l);
  outb(0x40, h);
  printf("done initializing\n");
}