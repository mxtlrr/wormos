%macro isr_err_stub 1
isr_stub_%+%1:
  cli
  push byte %1
  jmp common_stub
%endmacro

%macro isr_noerr_stub 1
isr_stub_%+%1:
  cli
  jmp common_stub
%endmacro


extern exception_handler
isr_noerr_stub 0
isr_noerr_stub 1
isr_noerr_stub 2
isr_noerr_stub 3
isr_noerr_stub 4
isr_noerr_stub 5
isr_noerr_stub 6
isr_noerr_stub 7
isr_err_stub   8
isr_noerr_stub 9
isr_err_stub   10
isr_err_stub   11
isr_err_stub   12
isr_err_stub   13
isr_err_stub   14
isr_noerr_stub 15
isr_noerr_stub 16
isr_err_stub   17
isr_noerr_stub 18
isr_noerr_stub 19
isr_noerr_stub 20
isr_noerr_stub 21
isr_noerr_stub 22
isr_noerr_stub 23
isr_noerr_stub 24
isr_noerr_stub 25
isr_noerr_stub 26
isr_noerr_stub 27
isr_noerr_stub 28
isr_noerr_stub 29
isr_err_stub   30
isr_noerr_stub 31


global isr_stub_table
isr_stub_table:
%assign i 0 
%rep    32 
  dd isr_stub_%+i
%assign i i+1 
%endrep

[extern exception_handler]
common_stub:
  pusha      ;; push all our registers
  mov ax, ds
  push eax   ;; save data seg

  mov ax, 0x10
  mov ds, ax
  mov es, ax
  mov fs, ax
  mov gs, ax

  call exception_handler

  pop eax
  mov ds, ax
  mov es, ax
  mov fs, ax
  mov gs, ax
  popa
  add esp, 8    ;; clean up
  sti
  iret