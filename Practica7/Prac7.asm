.INCLUDE "m1280def.inc"

loop:
	call delay678ms
	jmp loop

delay123ns:
		ldi r16, 178
nxt11:	ldi r17, 2
nxt21:	dec r17
		nop
		brne nxt21
		dec r16
		brne nxt11
		ret


delay45ms:
		ldi r16, 10
nxt12:	ldi r17, 164
nxt22:	ldi r18, 145
		nop
nxt32:	dec r18
		brne nxt32
		dec r17
		brne nxt22
		dec r16
		brne nxt12
		ret

delay678ms:
		ldi r16, 10
nxt13:	ldi r17, 206
nxt23:	ldi r18, 173
		nop
		nop
		nop
		nop
nxt33:	dec r18
		brne nxt33
		dec r17
		brne nxt23
		dec r16
		brne nxt13
		ldi r16, 200
nxt43:	ldi r17, 1
nxt53:	dec r17
		brne nxt53
		dec r16
		brne nxt43
		ret
