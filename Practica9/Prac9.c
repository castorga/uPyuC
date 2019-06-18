#include <avr/io.h>
#include "UART.h"

int main( void ){
    char cad[20];
    uint16_t num;
    UART_Ini(0, 12345, 8, 1, 2);
    while (1) {
        UART_getchar();
        clrscr();
        gotoxy(2, 2);
        setColor(YELLOW);
        UART_puts("Introduce un numero: ");
        gotoxy(22, 2);
        setColor(GREEN);
        UART_gets(cad);
        num = atoi(cad);
        itoa(cad, num, 16);
        gotoxy(5, 3);
        setColor(BLUE);
        UART_puts("Hex: ");
        UART_puts(cad);
        itoa(cad, num, 2);
        gotoxy(5, 4);
        UART_puts("Bin: ");
        UART_puts(cad);
    }
}
