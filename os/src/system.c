#include "system.h"
#include "console.h"

extern void panic (const char *msg, const char *file, unsigned int line)
{
  asm volatile ("cli"); // Disable Interrupts

  k_printf("PANIC(%s) at %s:%d\n", msg, file, line);

  for (;;);
}

extern void panic_assert (const char *file, unsigned int line, const char *desc)
{
  asm volatile ("cli"); // Disable interrupts

  k_printf("ASSERTION-FAILED(%s) at %s:%d\n", desc, file, line);

  for(;;);
}

