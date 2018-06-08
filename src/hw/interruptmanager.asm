global activateInterrupts
global loadIdt
global ignoreInterrupt
global interrupt0x21

extern handleInterrupt0x21

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

interrupt0x21:
;	jmp saveRegisters
	call handleInterrupt0x21
;	jmp restoreRegisters
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
