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
  hdlrs[irq]=hdlr;
}

void irq_hdlr(registers_t regs){
  // send EOI
  if(regs.irq_n >= 40){
    // reset -> slave
    outb(S_PIC_CMD, 0x20);
  }
  // reset -> master
  outb(M_PIC_CMD, 0x20);

  printf("IRQ0x%x recv.\n");
}