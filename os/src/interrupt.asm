; interrupt.asm - Contains ISR wrappers

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

; This macro creates a stub for an IRQ. Param 1 is IRQ number, param 2 is ISR number
%macro IRQ 2
[global irq%1]
irq%1:
  cli
  push  byte 0
  push  byte %2
  jmp irq_common_stub
%endmacro
        
; Interrupt Service Routines
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

; IRQs
IRQ   0,    32
IRQ   1,    33
IRQ   2,    34
IRQ   3,    35
IRQ   4,    36
IRQ   5,    37
IRQ   6,    38
IRQ   7,    39
IRQ   8,    40
IRQ   9,    41
IRQ  10,    42
IRQ  11,    43
IRQ  12,    44
IRQ  13,    45
IRQ  14,    46
IRQ  15,    47

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

[extern irq_handler]

irq_common_stub:
    pusha

    mov ax, ds
    push eax

    mov ax, 0x10 
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax

    call irq_handler

    pop ebx
    mov ds, bx
    mov es, bx
    mov fs, bx
    mov gs, bx

    popa
    add esp, 8
    sti
    iret
 
