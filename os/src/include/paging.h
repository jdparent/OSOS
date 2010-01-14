#ifndef PAGING_H
#define PAGING_H

#include "isr.h"

typedef struct page
{
  unsigned int present  : 1;  // Is page present in memory.
  unsigned int rw       : 1;  // 0: R/O, 1: R/W
  unsigned int user     : 1;  // 0: Supervisor level, 1: User level
  unsigned int accessed : 1;  // 0: OK, 1: Accessed
  unsigned int dirty    : 1;  // 0: OK, 1: Has been written
  unsigned int unused   : 7;  // Misc
  unsigned int frame    : 20; // Frame Address
} page_t;

typedef struct page_table
{
  page_t pages[1024];
} page_table_t;

typedef struct page_directory
{
  page_table_t *tables[1024]; // Page Tables
  unsigned int tablesPhysical[1024];  // Physical location of page tables.
  unsigned int physicalAddress;
} page_directory_t;

void initialize_paging (void);
void switch_page_directory (page_directory_t *new);
page_t *get_page (unsigned int address, int make, page_directory_t *dir);

void page_fault (registers_t regs);

#endif  // PAGING_H

