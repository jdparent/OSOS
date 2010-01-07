#include "system.h"
#include "console.h"

int k_main(struct multiboot *mboot_ptr)
{
  k_clrscr();

  k_printf("Hello World\n");

  k_printf("1 + 2 = %d\n", 1+2);

  ASSERT(1 == 1);

  PANIC("Halting OS");

  return 0xDEADBABA;
}

