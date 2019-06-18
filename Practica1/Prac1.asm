//Practica 1 para repasar conocimientos en ensamblador 8086
//Programa que encuentra el n-esimo numero feo, el valor de n es almacenado en el registro CX
.model small
    locals
.data
    indice      dw  1
    cantidad    dw  1

.code
                org 100h

    ;proceso principal
    Main        PROC
                mov sp, 0FFFh
            @@bucle: 
                call NesimoFeo
                call printDec
                mov dl, 10
                mov ah, 02h
                int 21h
                mov dl, 13
                int 21h
                jmp @@bucle
                ret
                ENDP
    ;procesos adicionales
    DivMaximo   PROC
                push bp                 
                mov bp, sp
            @@While:
                mov ax, [bp + 4]
                cwd
                idiv word ptr[bp + 6]
                mov ax, dx
                test ax, ax
                jne @@Fin
                mov ax, [bp + 4]
                cwd
                idiv word ptr[bp + 6]
                mov [bp + 4], ax
                jmp @@While
            @@Fin:
                mov ax, [bp + 4]
                pop bp
                ret
                ENDP

    EsFeo       PROC
                push bp
                mov bp, sp

                mov ax, 2
                push ax
                mov ax, [bp + 4]
                push ax
                call DivMaximo
                pop bx
                pop bx
                mov [bp + 4], ax

                mov ax, 3
                push ax
                mov ax, [bp + 4]
                push ax
                call DivMaximo
                pop bx
                pop bx
                mov [bp + 4], ax

                mov ax, 5
                push ax
                mov ax, [bp + 4]
                push ax
                call DivMaximo
                pop bx
                pop bx
                mov [bp + 4], ax

                cmp word ptr[bp + 4], 1
                jne @@Regresa0
                mov ax, 1
                jmp @@Final
            @@Regresa0:
                mov ax, 0
            @@Final:
                pop bp
                ret
                ENDP

    NesimoFeo   PROC
                push bp
                mov bp, sp
                mov [indice], 1
                mov [cantidad], 1
            @@While:
                cmp cx, [cantidad]
                jbe @@Final
                inc [indice]
                mov ax, [indice]
                push ax
                call EsFeo
                pop bx
                cmp ax, 1
                jne @@While
                inc [cantidad]
                jmp @@While
            @@Final:
                mov ax, [indice]
                pop bp
                ret
                ENDP

    printDec    PROC
                push ax
                push bx
                push cx
                push dx
                mov bx, 10
                mov cx, 0
            @@Loop1:  
                mov dx, 0
                div bx
                push dx
                inc cx
                cmp ax, 0
                jnz @@Loop1
            @@Loop2:  
                pop dx
                add dl, '0'
                mov ah, 02h
                int 21h
                loop @@Loop2
                pop dx
                pop cx
                pop bx
                pop ax
                ret
                ENDP

    END         Main
