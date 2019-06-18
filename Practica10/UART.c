#include <avr/io.h>
#include <avr/interrupt.h>
#include "UART.h"

void UART0_putchar(char Data) {
    while(!(UCSR0A & (1<<UDRE0)));
    UDR0 = Data;
}

void UART0_Ini(void) {
	UCSR0A |= 0b00000000;
	UCSR0B |= 0b00011000;
	UCSR0C |= 0b00111110;
	UBRR0 = 0x67;
	sei();
}


void UART0_AutoBaudRate( void ) {
    DDRE &= 0;
	PORTF |= (1<<PE0);
	TCCR0A = 0;
	TCCR0B = 2;
	while((PINE & (1<<PE0)));
	TCNT0 = 0;
	while((PINE & 1) == 0);
	TCCR0B = 0;
	UBRR0 = (TCNT0/2) - 1;
	TCNT0 = 0;
}

void UART0_puts(char *str) {
    while(*str) UART0_putchar(*str++);
}

void itoa(char *str, uint16_t number, uint8_t base) {
    uint16_t i = 0, j = 0, Digitos = 0;
    uint16_t residuo;
    uint8_t Caracter;
    do {
        residuo = number%base;
        number = number/base;
        if(residuo > 9) {
            *str++ = residuo + '0' + 7;
        } else {
			*str++ = residuo + '0';
		}
        Digitos++;
    } while(number != 0);
    *str = 0;
    str -= Digitos;
    j = --Digitos;
    while(i < j) {
        if(str[i] != str[j]) {
            Caracter = str[i];
            str[i] = str[j];
            str[j] = Caracter;
        }
        i++;
        j--;
    }
}

void clrscr() {
	UART0_puts("\033[2J\033[H");
}

void gotoxy(int x, int y) {
	UART0_putchar('\033');
	UART0_putchar('[');
	UART0_putchar(y/10 + '0');
	UART0_putchar(y%10 + '0');
	UART0_putchar(';');
	UART0_putchar(x/10 + '0');
	UART0_putchar(x%10 + '0');
	UART0_putchar('H');
}
