#include "console.h"

int k_main(struct multiboot *mboot_ptr)
{
  k_clrscr();

  k_printf("Hello World\n");

  k_printf("1 + 2 = %d", 1+2);

  while(1)
  {
    ;
  }
  return 0xDEADBABA;
}

