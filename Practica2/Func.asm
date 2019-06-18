dosseg
.model small
.code
public _putchar, _getchar
_putchar        PROC
                push bp
                mov bp, sp
                mov ah, 2h
                mov dl, [bp + 4]
                int 21h
                pop bp
                ret
_putchar        ENDP

_getchar        PROC
                push bp
                mov bp, sp
                mov ah, 1h
                int 21h
                pop bp
                ret
_getchar        ENDP
END
