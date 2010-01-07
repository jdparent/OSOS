#ifndef STRING_H
#define STRING_H

void *memcpy (void *s1, const void *s2, unsigned int n);
void *memset (void *b, int c, unsigned int n);

void *memsetw (unsigned short *s1, unsigned short val, unsigned int count);

int strlen (const char *str);

#endif  // STRING_H

