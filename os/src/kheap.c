#include "kheap.h"

extern unsigned int end;  // Pulled from linker

unsigned int placement_address = (unsigned int)&end;

unsigned int kmalloc_base (unsigned int size, int align, unsigned int *addr)
{
  unsigned int temp_addr;

  if ((align == 1) && (placement_address & 0xFFFFF000))
  {
    placement_address &= 0xFFFFF000;
    placement_address += 0x1000;
  }
  
  if (addr)
  {
    *addr = placement_address;
  }

  temp_addr = placement_address;

  placement_address += size;

  return temp_addr;
}

unsigned int kmalloc (unsigned int size)
{
  return kmalloc_base(size, 0, 0);
}

unsigned int kmalloc_a (unsigned int size)
{
  return kmalloc_base(size, 1, 0);
}

unsigned int kmalloc_p (unsigned int size, unsigned int *physical)
{
  return kmalloc_base(size, 0, physical);
}

unsigned int kmalloc_ap (unsigned int size, unsigned int *physical)
{
  return kmalloc_base(size, 1, physical);
}
