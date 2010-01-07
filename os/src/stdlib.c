#include "stdlib.h"

void reverse (char *s, int size)
{
  int c, i, j;

  for (i = 0, j = size - 1; i < j; i++, j--)
  {
    c = s[i];
    s[i] = s[j];
    s[j] = c;
  }
}

void itoa (int n, char *s)
{
  int i, sign;

  if ((sign = n) < 0)
    n = -n;

  i = 0;

  do
  {
    s[i++] = n % 10 + '0';
  }while ((n /= 10) > 0);

  if (sign < 0)
    s[i++] = '-';
  
  s[i] = '\0';

  reverse(s, i);
}

void uitoa (unsigned int n, char *s)
{
  int i = 0;

  do
  {
    s[i++] = n % 10 + '0';
  }while  ((n /= 10) > 0);

  s[i] = '\0';

  reverse(s, i);
}
