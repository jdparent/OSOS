#include "string.h"

void *memcpy (void *s1, const void *s2, unsigned int n)
{
  unsigned int i;
  char *v1 = (char *)s1;
  char *v2 = (char *)s2;
  for (i = 0; i < n; i++)
  {
    v1[i] = v2[i];
  }

  return s1;
}

void *memset (void *b, int c, unsigned int n)
{
  unsigned char *a = (unsigned char *)b;
  while (n > 0)
  {
    a[n-1] = (unsigned char)c;
    n--;
  }

  return b;
}

void *memsetw (unsigned short *s1, unsigned short val, unsigned int count)
{
  unsigned short *tmpPtr = (unsigned short *)s1;

  while (count != 0)
  {
    *tmpPtr++ = val;
    count--;
  }

  return s1;
}

int strlen (const char *str)
{
  int count = 0;

  while (str[count] != '\0')
  {
    count++;
  }

  return count;
}

