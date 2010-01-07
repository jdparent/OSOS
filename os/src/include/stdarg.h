#ifndef STDARG_H
#define STDARG_H

/* home-brew STDARG.H, also public-domain: */

/* Assume: width of stack == width of int. Don't use sizeof(char *) or
other pointer because sizeof(char *)==4 for LARGE-model 16-bit code.
Assume: width is a power of 2 */
#define STACK_WIDTH sizeof(int)

/* Round up object width so it's an even multiple of STACK_WIDTH.
Using & for division here, so STACK_WIDTH must be a power of 2. */
#define TYPE_WIDTH(TYPE)        \
  ((sizeof(TYPE) + STACK_WIDTH - 1) & ~(STACK_WIDTH - 1))

  /* point the va_list pointer to LASTARG,
  then advance beyond it to the first variable arg */
#define va_start(PTR, LASTARG)        \
    PTR = (va_list)((char *)&(LASTARG) + TYPE_WIDTH(LASTARG))

#define va_end(PTR) /* nothing */

/* Increment the va_list pointer, then return
(evaluate to, actually) the previous value of the pointer. */
#define va_arg(PTR, TYPE) (     \
  PTR = (char *)(PTR) + TYPE_WIDTH(TYPE)    \
          ,     \
            *((TYPE *)((char *)(PTR) - TYPE_WIDTH(TYPE))) \
                    )

typedef void *va_list;
#endif  // STDARG_H

