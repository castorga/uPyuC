;Practica 6 Voltear un numero de 32 bits almacenado en los registros del microcontrolador
;Primer practica donde se utiliza directamente el microcontrolador atMEGA1280/2560
;Para familiarizarse con el ensamblador del AVR
.INCLUDE "m1280def.inc"
.equ VALUE1 = 0xAA
.equ VALUE2 = 0xC0
.equ VALUE3 = 0x01
.equ VALUE4 = 0x00
.equ VALUE5 = 0x80
.equ VALUE6 = 0x02
.equ VALUEinit = 8

bucle_infinito:
	;ldi r24, 1
	ldi r26, VALUE1
	ldi r27, VALUE2
	ldi r28, VALUE3
	ldi r29, VALUE4
	ldi r30, VALUE5
	ldi r31, VALUE6
	cpi r24, 1
	breq swapR24_1
	cpi r24, 0
	breq swapR24_0
	jmp bucle_infinito

swapR24_1:
	ldi R16, VALUEinit
swapR24_1_parte1:
	ror R28
	rol R31
	dec R16
	brne swapR24_1_parte1
	ror R28
	clc
	ldi R16, VALUEinit
swapR24_1_parte2:
	ror R29
	rol R30
	dec R16
	brne swapR24_1_parte2
	ror R29
	clc
	;ldi r24, 0
	jmp bucle_infinito

swapR24_0:
	ldi R16, VALUEinit
swapR24_0_parte1:
	ror R26
	rol R29
	dec R16
	brne swapR24_0_parte1
	ror R26
	clc
	ldi R16, VALUEinit
swapR24_0_parte2:
	ror R27
	rol R28
	dec R16
	brne swapR24_0_parte2
	ror R27
	clc
	;ldi r24, 1
	jmp bucle_infinito
