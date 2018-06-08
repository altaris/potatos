bits 32         ;nasm directive - 32 bit

section .text   ;multiboot spec
    align 4
    dd 0x1BADB002            ;magic
    dd 0x00                  ;flags
    dd - (0x1BADB002 + 0x00) ;checksum. m+f+c should be zero

extern kernelMain

global start
start:
  cli                   ;block interrupts
  mov esp, stack_space  ;set stack pointer
  call kernelMain
  hlt                   ;halt the CPU

section .bss
resb 8192       ;8KB for stack
stack_space:
