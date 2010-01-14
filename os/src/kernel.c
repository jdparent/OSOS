#include "console.h"
#include "descriptor_tables.h"
#include "timer.h"
#include "paging.h"

int k_main(struct multiboot *mboot_ptr)
{
  // Initialization
  init_descriptor_tables();
  k_clrscr();
  initialize_paging();

  k_printf("Hello, world!\n");

  unsigned int *ptr = (unsigned int *)0xA0000000;

  unsigned int do_page_fault = *ptr;

  return 0;
}

