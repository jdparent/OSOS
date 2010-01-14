#include "paging.h"
#include "system.h" // PANIC
#include "string.h" // memset
#include "console.h"
#include "kheap.h"

unsigned int *frames;
unsigned int num_frames;

extern unsigned int placement_address;

page_directory_t *kernel_directory = 0;
page_directory_t *current_directory = 0;

static void set_frame(unsigned int addr)
{
  unsigned int frame = addr / 0x1000;

  frames[frame / 32] |= (0x01 << (frame % 32));
}

static void clear_frame(unsigned int addr)
{
  unsigned int frame = addr / 0x1000;

  frames[frame / 32] &= ~(0x01 << (frame % 32));
}

static unsigned int check_frame (unsigned int addr)
{
  unsigned int frame = addr / 0x1000;

  return (frames[frame / 32] & (0x01 << (frame % 32)));
}

static unsigned int find_first_frame()
{
  unsigned int block, bit;

  for (block = 0; block < (num_frames / 32); block++)
  {
    if (frames[block] != 0xFFFFFFFF) // Block isnt full
    {
      for (bit = 0; bit < 32; bit++)  // Test each bit
      {
        unsigned int testBit = 0x01 << bit;

        if (!(frames[block] & testBit)) // Found empty bit
        {
          return block * 32 + bit;
        }
      }
    }
  }

  return 0xFFFFFFFF;  // Did not find any open frames
}

void alloc_frame (page_t *page, int is_kernel, int is_writeable)
{
  if (page->frame != 0)
  {
    return; // Frame already allocated
  }
  else
  {
    unsigned int index = find_first_frame();

    if (index == 0xFFFFFFFF)  // No Frames free.
    {
      PANIC("No free frames available!");
    }

    set_frame(index * 0x1000);          // Frame set to used
    page->present = 1;                  // Page is present
    page->rw = (is_writeable) ? 1 : 0;  // R/W or R/O
    page->user = (is_kernel) ? 0 : 1;   // User or Kernel page
    page->frame = index;                // Set frame address
  }
}

void free_frame (page_t *page)
{
  unsigned int frame;

  if (frame = page->frame)
  {
    clear_frame(frame); // Free'd frame
    page->frame = 0x0;  // No frame set for page
  }
}

void initialize_paging()
{
  int i = 0;
  unsigned int memory_page_end = 0x1000000; // 16MB memory

  num_frames = memory_page_end / 0x1000;
  frames = (unsigned int*)kmalloc(num_frames / 32);

  memset(frames, 0x00, num_frames / 32);

  kernel_directory = (page_directory_t*)kmalloc_a(sizeof(page_directory_t));

  memset(kernel_directory, 0x00, sizeof(page_directory_t));

  current_directory = kernel_directory;

  while (i < placement_address)
  {
    alloc_frame(get_page(i, 1, kernel_directory), 0, 0);  // R/O, User
    i += 0x1000;
  }

  register_interrupt_handler(14, page_fault);

  switch_page_directory(kernel_directory);
}

void switch_page_directory (page_directory_t *dir)
{
  unsigned int cr0;

  current_directory = dir;

  asm volatile ("mov %0, %%cr3" :: "r" (&dir->tablesPhysical));
  
  asm volatile ("mov %%cr0, %0" : "=r"(cr0));

  cr0 |= 0x80000000;  // Enable paging

  asm volatile ("mov %0, %%cr0" :: "r" (cr0));
}

page_t *get_page (unsigned int address, int make, page_directory_t *dir)
{
  unsigned int table_index;

  address /= 0x1000;  // Address is now an index.

  table_index = address / 1024;

  if (dir->tables[table_index]) // Table exists
  {
    return &dir->tables[table_index]->pages[address % 1024];
  }
  else if (make)  // Create page since one doesnt exist
  {
    unsigned int temp;

    dir->tables[table_index] = 
      (page_table_t*)kmalloc_ap(sizeof(page_table_t), &temp);

    memset(dir->tables[table_index], 0x00, 0x1000); // Zero out table

    dir->tablesPhysical[table_index] = temp | 0x07; // Present, RW, User

    return &dir->tables[table_index]->pages[address % 1024];
  }
  else  // No table found and do not make a new one
  {
    return 0;
  }
}

void page_fault (registers_t regs)
{
  unsigned int fault_address;
  int present, rw, user, reserved, id;

  asm volatile ("mov %%cr2, %0" : "=r" (fault_address));

  present = !(regs.err_code & 0x01);
  rw = regs.err_code & 0x02;
  user = regs.err_code & 0x04;
  reserved = regs.err_code & 0x08;
  id = regs.err_code & 0x10;

  k_printf("Page Fault! (");

  if (present)
    k_printf("present ");

  if (rw)
    k_printf("read-only ");

  if (user)
    k_printf("user-mode ");

  if (reserved)
    k_printf("reserved ");

  k_printf(") at 0x%x\n", fault_address);

  PANIC("Page Fault");
}
