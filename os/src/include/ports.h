#ifndef PORTS_H
#define PORTS_H

unsigned char inb(unsigned short port);

unsigned short inw(unsigned short port);

void outb(unsigned short port, unsigned char data);

#endif  // PORTS_H

