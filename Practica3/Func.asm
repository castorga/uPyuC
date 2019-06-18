.model tiny
.code
public _peek, _poke, _putchar, _getch
_peek           PROC
                push bp
                mov bp, sp

                mov bx, [bp + 6]
                push ds
                mov ds, [bp + 4]
                mov al, [bx]
                pop ds

                pop bp
                ret
_peek           ENDP

_poke           PROC
                push bp
                mov bp, sp

                mov bx, [bp + 6]
                push ds
                mov ds, [bp + 4]
                mov dl, [bp + 8]
                mov [bx], dl
                pop ds

                pop bp
                ret
_poke           ENDP

_putchar        PROC
                push bp
                mov bp, sp

                mov ah, 2h
                mov dl, [bp + 4]
                int 21h

                pop bp
                ret
_putchar        ENDP

_getch          PROC
                push bp
                mov bp, sp

                mov ah, 8h
                int 21h

                pop bp
                ret
_getch          ENDP
END