.model tiny
.code
public _outportb, _inportb, _getchar, _putchar
_outportb       PROC
                push bp
                mov bp, sp

                mov dx, [bp + 4]
                mov al, [bp + 6]
                out dx, al

                pop bp
                ret
_outportb       ENDP

_inportb        PROC
                push bp
                mov bp, sp

                mov dx, [bp + 4]
                in al, dx

                pop bp
                ret
_inportb        ENDP

_getchar        PROC
                push bp
                mov bp, sp

                mov ah, 01h
                int 21h

                pop bp
                ret
_getchar        ENDP

_putchar        PROC
                push bp
                mov bp, sp

                mov ah, 02h
                mov dl, [bp + 4]
                int 21h

                pop bp
                ret
_putchar        ENDP
END