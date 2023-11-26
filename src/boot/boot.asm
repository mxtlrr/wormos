;; Boot stub.

;;; Multiboot header things
MBALIGN  equ 1<<0
MEMINFO  equ 1<<1
MBFLAGS  equ MBALIGN | MEMINFO
MAGIC    equ 0x1badb002
CHECKSUM equ -(MAGIC + MBFLAGS)

section .multiboot
align 4
  dd MAGIC
  dd MBFLAGS
  dd CHECKSUM
  ;; TODO: Set up a FB here.

section .bss
align 16
stack_bottom:
  resb 16834    ;; 16KB of stack
stack_top:

section .text
global _start:function (_start.end - _start)
_start:
  ;; Set up stack here
  mov esp, stack_top

  ;; TODO: load stuff like the GDT here
  extern kmain
  call kmain

  ;; Somehow got out of kmain?
  cli   ;; Disable interrupts
.hang: hlt
  jmp .hang
.end: