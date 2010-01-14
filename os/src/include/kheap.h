#ifndef KHEAP_H
#define KHEAP_H

unsigned int kmalloc (unsigned int size);
unsigned int kmalloc_a (unsigned int size);
unsigned int kmalloc_p (unsigned int size, unsigned int  *physical);
unsigned int kmalloc_ap (unsigned int size, unsigned int *physical);

#endif  // KHEAP_H

