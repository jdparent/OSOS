#ifndef ISR_H
#define ISR_H

#define ISR0    0
#define ISR1    1
#define ISR2    2
#define ISR3    3
#define ISR4    4
#define ISR5    5
#define ISR6    6
#define ISR7    7
#define ISR8    8
#define ISR9    9
#define ISR10   10
#define ISR11   11
#define ISR12   12
#define ISR13   13
#define ISR14   14
#define ISR15   15
#define ISR16   16
#define ISR17   17
#define ISR18   18
#define ISR19   19
#define ISR20   20
#define ISR21   21
#define ISR22   22
#define ISR23   23
#define ISR24   24
#define ISR25   25
#define ISR26   26
#define ISR27   27
#define ISR28   28
#define ISR29   29
#define ISR30   30
#define ISR31   31

typedef struct 
{
  unsigned int ds;
  unsigned int edi, esi, ebp, esp, ebx, edx, ecx, eax;
  unsigned int int_no, err_code;
  unsigned int eip, cs, eflags, useresp, ss;
} registers_t;

typedef void (*isr_t)(registers_t);

void register_interrupt_handler(unsigned char n, isr_t handler);
void unregister_interrupt_handler(unsigned char n);

#endif  // ISR_H

