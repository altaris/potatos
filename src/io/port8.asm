global read_port8
global write_port8

read_port8:
	mov edx, [esp + 4]
	in al, dx
	ret

write_port8:
	mov   edx, [esp + 4]
	mov   al, [esp + 4 + 4]
	out   dx, al
	ret
