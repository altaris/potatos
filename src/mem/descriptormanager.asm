global loadGdt

loadGdt:
	mov edx, [esp + 4]
	lgdt [edx]
	ret
