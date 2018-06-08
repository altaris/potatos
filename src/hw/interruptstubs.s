.set PIC_OFFSET, 0x20
.global PIC_OFFSET

.section .text

.extern handleInterrupt

# Macro to define the handle exception routines
.macro DefineHandleException num
.global handleException\num
handleException\num:
#    movb $\num, (interruptnumber)
    jmp int_bottom
.endm

DefineHandleException 0x00
DefineHandleException 0x01
DefineHandleException 0x02
DefineHandleException 0x03
DefineHandleException 0x04
DefineHandleException 0x05
DefineHandleException 0x06
DefineHandleException 0x07
DefineHandleException 0x08
DefineHandleException 0x09
DefineHandleException 0x0A
DefineHandleException 0x0B
DefineHandleException 0x0C
DefineHandleException 0x0D
DefineHandleException 0x0E
DefineHandleException 0x0F
DefineHandleException 0x10
DefineHandleException 0x11
DefineHandleException 0x12
DefineHandleException 0x13

# Macro to define the handle interrupt routines
.macro DefineHandleInterrupt num
.global handleInterrupt\num
handleInterrupt\num:
#    movb $\num + PIC_OFFSET, (interruptnumber)
#    #pushl $0
    jmp int_bottom
.endm

DefineHandleInterrupt 0x00
DefineHandleInterrupt 0x01
DefineHandleInterrupt 0x02
DefineHandleInterrupt 0x03
DefineHandleInterrupt 0x04
DefineHandleInterrupt 0x05
DefineHandleInterrupt 0x06
DefineHandleInterrupt 0x07
DefineHandleInterrupt 0x08
DefineHandleInterrupt 0x09
DefineHandleInterrupt 0x0A
DefineHandleInterrupt 0x0B
DefineHandleInterrupt 0x0C
DefineHandleInterrupt 0x0D
DefineHandleInterrupt 0x0E
DefineHandleInterrupt 0x0F
DefineHandleInterrupt 0x31
DefineHandleInterrupt 0x80

.global ignoreInterrupt
ignoreInterrupt:

    iret

int_bottom:

    iret

#    # save registers
#    pusha
#    pushl %ds
#    pushl %es
#    pushl %fs
#    pushl %gs
#
#    #pushl %ebp
#    #pushl %edi
#    #pushl %esi
#    #pushl %edx
#    #pushl %ecx
#    #pushl %ebx
#    #pushl %eax
#
#    # call C++ Handler
#    pushl %esp
#    push (interruptnumber)
#    call handleInterrupt
#
#    #add %esp, 6
#
#    # move return value to stack pointer
#    mov %eax, %esp
#
#    # restore registers
#    pop %gs
#    pop %fs
#    pop %es
#    pop %ds
#    popa
#
#    #popl %eax
#    #popl %ebx
#    #popl %ecx
#    #popl %edx
#    #popl %esi
#    #popl %edi
#    #popl %ebp

.data
    interruptnumber: .byte 0
