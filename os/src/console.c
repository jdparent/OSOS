#include "console.h"
#include "stdarg.h"
#include "ports.h"
#include "string.h"
#include "stdlib.h"

#define X_MAX     80
#define Y_MAX     25

#define LENGTH 64
static char buf[LENGTH];
static char const udigit[16] = "0123456789ABCDEF";
static char const ldigit[16] = "0123456789abcdef";
static const char *digits;

static int cx = 0;
static int cy = 0;
static attrib = (BLACK << 4) | (WHITE & 0x0F);

void scroll (void)
{
  unsigned short *vidmem = (unsigned short *)0xB8000;
  unsigned int temp, blank;

  blank = ' ' | (attrib << 8);

  if (cy >= 25)
  {
    int i;

    for (i = 0; i < 24 * 80; i++)
    {
      vidmem[i] = vidmem[i+80];
    }


    for (i = 24 * 80; i < 25 * 80; i++)
    {
      vidmem[i] = blank;
    }

    cy = 24;
  }
}

void update_cursor (int x, int y)
{
  unsigned short i = (y * 80) + x;

  outb(0x3D4, 0x0E);
  outb(0x3D5, (unsigned char)(i >> 8));
  outb(0x3D4, 0x0F);
  outb(0x3D5, (unsigned char)(i));
}

void k_clrscr (void)
{
  char *vidmem = (char *)0xB8000;
  unsigned int i = 0;

  while (i < (80 * 25 * 2))
  {
    vidmem[i] = ' ';
    i++;
    vidmem[i] = attrib;
    i++;
  }
  cx = 0;
  cy = 0;

  update_cursor(cx, cy);
}


void k_putch (char c)
{
  char *vidmem = (char *)0xB8000; 
  unsigned int i = 0;

  i = ((cy * 80) + cx) * 2;

  if (c == 0x08)  // Backspace
  {
    if (cx != 0)
      cx--;
  }
  else if (c == 0x09)  // Tab
  {
    cx = (cx + 8) & ~(8 - 1);
  }
  else if (c == '\r')
  {
    cx = 0;
  }
  else if (c == '\n')
  {
    cy++;
    cx = 0;
  }
  else
  {
    vidmem[i] = c;
    i++;
    vidmem[i] = attrib;
    i++;

    cx++;

    if (cx == X_MAX)
    {
      cx = 0;
      cy++;
    }
  }


  scroll();
  update_cursor(cx, cy);
}

void k_printf(const char *fmt, ...)
{
  int c;
  int i;
  va_list ap;

  va_start(ap, fmt);

loop:
  for(; *fmt && *fmt != '%'; fmt++)
  {
    k_putch(*fmt);
  }

  if (! *fmt)
    goto end;

  if (*fmt++ == '%')
  {
    c = *fmt++;
    switch (c)
    {
      case 'c': // Character
      case 'C':
      {
        k_putch(va_arg(ap, char));
        break;
      }
      case 'i': // Integer
      case 'd':
      {
        i = 0;
        itoa(va_arg(ap, int), buf);

        while (buf[i] != '\0')
          k_putch(buf[i++]);
        break;
      }
      case 'u': // Unsigned integer
      {
        i = 0;
        uitoa(va_arg(ap, unsigned int), buf);

        while (buf[i] != '\0')
          k_putch(buf[i++]);
        break;
      }
      case 'x': // Hex
      {
        int num = va_arg(ap, int);
        char found = 0;
        i = 8;

        while (i > 0)
        {
          k_putch(udigit[(num >> ((i - 1) * 4)) & 0x0F]);
          i--;
        }
        break;
      }
      case 's': // String
      {
        char *tmp = va_arg(ap, char *);
        while (*tmp != '\0')
          k_putch(*tmp++);
        break;
      }
      case '%': // % sign
      {
        k_putch('%');
        break;
      }
      default:
      {
        k_putch(c);
        break;
      }
    }
  }
  goto loop;
end:
  i = 0;
}

void k_setattr(unsigned char forcolor, unsigned char backcolor)
{
  attrib = (backcolor << 4) | (forcolor & 0x0F);
}

