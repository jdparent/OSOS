#include "console.h"
#include "descriptor_tables.h"
#include "timer.h"

int k_main(struct multiboot *mboot_ptr)
{
  init_descriptor_tables();

  k_clrscr();

    k_printf("Hello, world!\n");

  asm volatile ("int $0x3");
  asm volatile ("int $0x4");

    asm volatile("sti");
    init_timer(50);

    return 0;
}

