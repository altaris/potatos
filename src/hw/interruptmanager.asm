global activateInterrupts
global loadIdt
global ignoreInterrupt

%macro DEFINE_INTERRUPT 1
extern handleInterrupt%1
global interrupt%1
interrupt%1:
	call handleInterrupt%1
	jmp endOfInterrupt
%endmacro

DEFINE_INTERRUPT 0x20
DEFINE_INTERRUPT 0x21
DEFINE_INTERRUPT 0x22
DEFINE_INTERRUPT 0x23
DEFINE_INTERRUPT 0x24
DEFINE_INTERRUPT 0x25
DEFINE_INTERRUPT 0x26
DEFINE_INTERRUPT 0x27
DEFINE_INTERRUPT 0x28
DEFINE_INTERRUPT 0x29
DEFINE_INTERRUPT 0x2A
DEFINE_INTERRUPT 0x2B
DEFINE_INTERRUPT 0x2C
DEFINE_INTERRUPT 0x2D
DEFINE_INTERRUPT 0x2E
DEFINE_INTERRUPT 0x2F
DEFINE_INTERRUPT 0x51
DEFINE_INTERRUPT 0xA0

activateInterrupts:
	sti
	ret

endOfInterrupt:
	mov al, 0x20
	mov edx, 0x20
	out dx, al		; Write EOI to master PIC
	mov edx, 0xA0
	out dx, al		; Write EOI to slave PIC
	iretd			; Return from interrupt

ignoreInterrupt:
	jmp endOfInterrupt

loadIdt:
	mov edx, [esp + 4]
	lidt [edx]
	ret

;restoreRegisters:
;	pop eax
;	pop ebx
;	pop ecx
;	pop edx
;	pop esi
;	pop edi
;	pop ebp
;
;saveRegisters:
;   push ebp
;   push edi
;   push esi
;   push edx
;   push ecx
;   push ebx
;   push eax
