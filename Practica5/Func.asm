.model tiny
.code
public _poke, _pokeW, _putchar
_poke           PROC
                push bp
                mov bp, sp

                push ds
                mov bx, [bp + 6]
                mov ds, [bp + 4]
                mov dl, [bp + 8]
                mov [bx], dl
                pop ds

                pop bp
                ret
_poke           ENDP

_pokeW          PROC
                push bp
                mov bp, sp

                push ds
                mov bx, [bp + 6]
                mov ds, [bp + 4]
                mov dx, [bp + 8]
                mov [bx], dx
                pop ds

                pop bp
                ret
_pokeW          ENDP

_putchar        PROC
                push bp
                mov bp, sp
                mov ah, 2h
                mov dl, [bp + 4]
                int 21h
                pop bp
                ret
_putchar        ENDP
END