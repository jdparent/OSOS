MBOOT_PAGE_ALIGN    equ 1<<0  ; Load kernel and modules on a page boundary
MBOOT_MEM_INFO      equ 1<<1  ; Provide mem info
MBOOT_HEADER_MAGIC  equ 0x1BADB002  ; Multiboot magic value
MBOOT_HEADER_FLAGS  equ MBOOT_PAGE_ALIGN | MBOOT_MEM_INFO
MBOOT_CHECKSUM      equ -(MBOOT_HEADER_MAGIC + MBOOT_HEADER_FLAGS)

[BITS 32]

[global mboot]
[extern code]
[extern bss]
[extern end]
[global _start]
[extern k_main]

[section .text]

mboot:
  dd  MBOOT_HEADER_MAGIC 
  dd  MBOOT_HEADER_FLAGS
  dd  MBOOT_CHECKSUM

  dd  mboot
  dd  code
  dd  bss
  dd  end
  dd  _start

_start:
  call    k_main
  hlt

