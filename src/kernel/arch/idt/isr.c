#include "arch/idt/isr.h"

char* exceptions[] = {
  "Division Err",
  "Debug",
  "NMI",
  "Breakpoint",
  "Overflow"
  "Bound Range Exceeded",
  "Invalid Opcode",
  "Device Not Available",
  "Double Fault",
  "Reserved",
  "Invalid TSS",
  "Segment Not Present",
  "Stack-Segment Fault",
  "GPF",
  "Page Fault",
  "Reserved",
  "x87 Floating-Point Exception",
  "Alignment Check",
  "Machine Check",
  "SIMD Floating-Point",
  "Virtualization Exception",
  "Control Protection Exception"
  "Reserved",
  "Reserved",
  "Reserved",
  "Reserved",
  "Reserved",
  "Reserved",
  "Hypervisor Injection Exception",
  "VMM Communication Exception",
  "Security Exception"
};

void exception_handler(registers_t regs){
  terminal_setcolor(VGA_COLOR_RED);
  puts("\n\nInterrupt recieved! System halted.");
  printf("\nINT_NO=0x%x [%s]\nRegisters:\n", regs.irq_n, exceptions[regs.irq_n]);
  printf("\tEAX=0x%x (%d)\n\tEBX=0x%x (%d)\n\tECX=0x%x (%d)\n", regs.eax,
  regs.eax, regs.ebx, regs.ebx, regs.ecx, regs.ecx);

  if(regs.ec == 0) printf("No error code provided.");
  else printf("EC=%d", regs.ec);
  for(;;){
    __asm__("cli");
    __asm__("hlt");
  }
}

isr_t hdlrs[256];
void register_irq(uint8_t irq, isr_t hdlr){
  printf("[IRQs] registered irq %d\n", irq);
  hdlrs[irq]=hdlr;
}

void irq_hdlr(registers_t regs){
  if (regs.irq_n >= 40){
    // Send reset signal to slave.
    outb(0xA0, 0x20);
  }
  // Send reset signal to master. (As well as slave, if necessary).
  outb(0x20, 0x20);

  if (hdlrs[regs.irq_n] != 0){
    isr_t handler = hdlrs[regs.irq_n];
    handler(regs);
  }
}