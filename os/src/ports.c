#include "ports.h"

unsigned char inb(unsigned short port)
{
  // "=a" (result means: put AL register in variable result when finished
  // "d" (_port) means: load EDX with _port
  unsigned char result;

  asm volatile ("inb %1, %0" : "=a" (result) : "dN" (port));

  return result;
}

unsigned short inw(unsigned short port)
{
  unsigned short result;

  asm volatile ("inw %1, %0" : "=a" (result) : "dN" (port));

  return result;
}

void outb(unsigned short port, unsigned char data)
{
  // "a" (_data) means: load EAX with _data
  // "d" (_port) means: load EDX with _port
  asm volatile ("outb %1, %0" : : "dN" (port), "a" (data));
}

