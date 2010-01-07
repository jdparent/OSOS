#ifndef SYSTEM_H
#define SYSTEM_H

#define PANIC(msg) panic(msg, __FILE__, __LINE__)
#define ASSERT(b) ((b) ? (void)0 : panic_assert(__FILE__, __LINE__, #b))

extern void panic (const char *message, const char *file, unsigned int line);
extern void panic_assert (const char *file, unsigned int line, const char *d);

#endif  // SYSTEM_H

