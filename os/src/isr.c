#include "isr.h"
#include "console.h"
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
  k_printf("received interrupt: %u\n", regs.int_no);

  if (interrupt_handlers[regs.int_no] != 0)
  {
    isr_t handler = interrupt_handlers[regs.int_no];

    handler(regs);
  }
}

void irq_handler(registers_t regs)
{
  if (regs.int_no >= 40)
  {
    outb(0xA0, 0x20);
  }

  outb(0x20, 0x20);

  if (interrupt_handlers[regs.int_no] != 0)
  {
    isr_t handler = interrupt_handlers[regs.int_no];

    handler(regs);
  }
}
