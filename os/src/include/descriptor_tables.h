#ifndef DESCRIPTOR_TABLES_H
#define DESCRIPTOR_TABLES_H

void init_descriptor_tables (void);

struct gdt_entry_struct
{
  unsigned short limit_low;
  unsigned short base_low;
  unsigned char base_middle;
  unsigned char access;
  unsigned char granularity;
  unsigned char base_high;
} __attribute__((packed));

struct gdt_ptr_struct
{
  unsigned short limit;
  unsigned int base;
} __attribute__((packed));

struct idt_entry_struct
{
  unsigned short base_low;
  unsigned short selector;
  unsigned char reserved;
  unsigned char flags;
  unsigned short base_hight;
} __attribute__((packed));

struct idt_ptr_struct
{
  unsigned short limit;
  unsigned int base;
} __attribute__((packed));

typedef struct gdt_entry_struct gdt_entry_t;
typedef struct gdt_ptr_struct gdt_ptr_t;
typedef struct idt_entry_struct idt_entry_t;
typedef struct idt_ptr_struct idt_ptr_t;

// Interrupt Service Routines
extern void isr0 (void);
extern void isr1 (void);
extern void isr2 (void);
extern void isr3 (void);
extern void isr4 (void);
extern void isr5 (void);
extern void isr6 (void);
extern void isr7 (void);
extern void isr8 (void);
extern void isr9 (void);
extern void isr10 (void);
extern void isr11 (void);
extern void isr12 (void);
extern void isr13 (void);
extern void isr14 (void);
extern void isr15 (void);
extern void isr16 (void);
extern void isr17 (void);
extern void isr18 (void);
extern void isr19 (void);
extern void isr20 (void);
extern void isr21 (void);
extern void isr22 (void);
extern void isr23 (void);
extern void isr24 (void);
extern void isr25 (void);
extern void isr26 (void);
extern void isr27 (void);
extern void isr28 (void);
extern void isr29 (void);
extern void isr30 (void);
extern void isr31 (void);

#endif  // DESCRIPTOR_TABLES_H

