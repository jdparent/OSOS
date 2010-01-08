#include "isr.h"
#include "system.h"
#include "console.h"
#include "stdlib.h"
#include "ports.h"

isr_t interrupt_handlers[256];

void register_interrupt_handler (unsigned char n, isr_t handler)
{
  interrupt_handlers[n] = handler;
}

void unregister_interrupt_handler (unsigned char n)
{
  register_interrupt_handler(n, 0);
}

void isr_handler (registers_t regs)
{
  k_printf("Received Interrupt: %d\n", regs.int_no);
}

