.set MAGIC, 0x1badb002
.set FLAGS, (1<<0 | 1<<1)
.set CHECKSUM, -(MAGIC + FLAGS)

.section .multiboot
    .long MAGIC
    .long FLAGS
    .long CHECKSUM

.section .text
.global loader

.extern kernelMain

loader:
    mov $kernel_stack, %esp
    push %eax               # multibootStructure main argument
    push %ebx               # multibootMagic main argument
    call kernelMain

_stop:
    cli
    hlt

.section .bss
.space 2*1024*1024;         # 2 MiB stack space
kernel_stack:
