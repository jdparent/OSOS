#include "timer.h"
#include "isr.h"
#include "console.h"

unsigned int tick = 0;

static void timer_callback (registers_t regs)
{
  k_printf("Tick: %u\n", tick++);
}

void init_timer(unsigned int freq)
{
  register_interrupt_handler(IRQ0, &timer_callback);

  unsigned int divisor = 1193180 / freq;

  outb(0x43, 0x36);

  unsigned char low = (unsigned char)(divisor & 0xFF);
  unsigned char high = (unsigned char)((divisor >> 8) & 0xFF);

  outb(0x40, low);
  outb(0x40, high);
}

