#include "system.h"
#include "console.h"
#include "descriptor_tables.h"

int k_main(struct multiboot *mboot_ptr)
{
  init_descriptor_tables();

  k_clrscr();

  k_printf("Hello World\n");

  k_printf("1 + 2 = %d\n", 1+2);

  asm volatile ("int $0x3");
  asm volatile ("int $0x4");

  PANIC("Halting OS");

  return 0xDEADBABA;
}

