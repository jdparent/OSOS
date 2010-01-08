; interrupt.as - Contains ISR wrappers

[bits 32]
; Macro creates a stub ISR which does not pass it's own error code.
%macro ISR_NOERRCODE 1
[global isr%1]
isr%1:
  cli                     ; Disable interrups
  push  byte 0            ; Push a dummy error code
  push  byte %1           ; Push the interrupt number
  jmp   isr_common_stub   ; Jump to handler
%endmacro

; Macro creates a stub ISR which passes its own error code.
%macro ISR_ERRCODE 1
[global isr%1]
isr%1:
  cli                     ; Disable interrupts
  push  byte %1           ; Push interrupt number
  jmp   isr_common_stub   ; Jump to handler
%endmacro

; Interrupt Service Rutines
ISR_NOERRCODE 0       ; Divide by Zero
ISR_NOERRCODE 1       ; Debug exception
ISR_NOERRCODE 2       ; Non maskable interrupt
ISR_NOERRCODE 3       ; Breakpoint exception
ISR_NOERRCODE 4       ; 'Into detected overflow'
ISR_NOERRCODE 5       ; Out of bounds exception
ISR_NOERRCODE 6       ; Invalid Opcode Exception
ISR_NOERRCODE 7       ; No coprocessor exception
ISR_ERRCODE   8       ; Double fault
ISR_NOERRCODE 9       ; Coprocessor segment overrun
ISR_ERRCODE   10      ; Bad TSS
ISR_ERRCODE   11      ; Segment not present
ISR_ERRCODE   12      ; Stack fault
ISR_ERRCODE   13      ; General Protection Fault
ISR_ERRCODE   14      ; Page Fault
ISR_NOERRCODE 15      ; Unknown Interrupt Exception
ISR_NOERRCODE 16      ; Coprocessor Fault
ISR_NOERRCODE 17      ; Alignment check exception
ISR_NOERRCODE 18      ; Machine check exception
ISR_NOERRCODE 19      ; Reserved: 19 - 31
ISR_NOERRCODE 20
ISR_NOERRCODE 21
ISR_NOERRCODE 22
ISR_NOERRCODE 23
ISR_NOERRCODE 24
ISR_NOERRCODE 25
ISR_NOERRCODE 26
ISR_NOERRCODE 27
ISR_NOERRCODE 28
ISR_NOERRCODE 29
ISR_NOERRCODE 30
ISR_NOERRCODE 31

[extern isr_handler]

isr_common_stub:
  pusha
  
  mov   ax, ds
  push  eax

  mov   ax, 0x10
  mov   ds, ax
  mov   es, ax
  mov   fs, ax
  mov   gs, ax

  call  isr_handler

  pop   ebx
  mov   ds, bx
  mov   es, bx
  mov   fs, bx
  mov   gs, bx

  popa
  add   esp, 8
  sti
  iret 

