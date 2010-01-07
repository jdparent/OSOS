#include "ports.h"

unsigned char inb(unsigned short port)
{
  // "=a" (result means: put AL register in variable result when finished
  // "d" (_port) means: load EDX with _port
  unsigned char result;

#if 0
  __asm__ ("in %%dx, $$al" : "=a" (result) : "d" (port));
#else
  asm volatile ("inb %1, %0" : "=a" (result) : "dN" (port));
#endif
  return result;
}

void outb(unsigned short port, unsigned char data)
{
  // "a" (_data) means: load EAX with _data
  // "d" (_port) means: load EDX with _port
#if 0
  __asm__ ("out %%al, %%dx" : : "a" (data), "d" (port));
#else
  asm volatile ("outb %1, %0" : : "dN" (port), "a" (data));
#endif
}

