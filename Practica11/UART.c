#include <avr/io.h>
#include <avr/interrupt.h>
#include "UART.h"
/*
ring_buffer_t Tx;

uint8_t* UCSRA;
uint8_t* UCSRB;
uint8_t* UCSRC;
uint8_t* UBBRL;
uint8_t* UBBRH;

*/
void UART0_putchar(char Data) {
    while(!(UCSR0A & (1<<UDRE0)));
    UDR0 = Data;
}

char UART0_getchar() {
	char Data;
    while(!(UCSR0A & (1<<RXC0)));
	Data = UDR0;
    return Data;
}

uint8_t UART0_available() {
	return 1;
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

/*
void UART_Ini(uint8_t com, uint16_t baudrate, uint8_t size, uint8_t parity, uint8_t stop) {
    UCSRA = (uint8_t*)(0xC0 + (com * 8));
	UCSRB = (uint8_t*)(0xC1 + (com * 8));
	UCSRC = (uint8_t*)(0xC2 + (com * 8));
	UBBRL = (uint8_t*)(0xC4 + (com * 8));
	UBBRH = (uint8_t*)(0xC5 + (com * 8));

	if(parity == 1) parity = 0b11;
	if(parity == 2) parity = 0b10;
	stop -= 1;

    uint16_t UBBR = (((uint32_t)(Frecuencia) / (uint32_t)(16 * (uint32_t)baudrate)) - 1);
	*UCSRB |= (1 << UDRIE0)|(1<<RXCIE0)|(0b11<<3);
	*UCSRB |= (4&(size));    //Bits de datos para el 9
	*UCSRC |= (2&(size)) << 1;   //Bits de datos normales
	*UCSRC |= ((3&parity) << 4);	//Paridad
	*UCSRC |= ((11&stop) << 3);	//Stop bits
	*UBBRH = (uint8_t)(UBBR >> 8);
	*UBBRL = (uint8_t)(UBBR);     
    
    Tx.in_idx = 0;
    Tx.out_idx = 0;

    sei();
}

void UART0_Ini(uint8_t size, uint8_t parity, uint8_t stop, uint8_t u2x) {
	UCSR0A = 0|((u2x & 1)<<U2X0);

}

void UART0_AutoBaudRate(void) {
    uint16_t tmp;
    DDRE = 0;
	PORTF = 1;
	TCCR0A = 0;
	TCCR0B = 2;
	while((PINE & (1<<PE0)));
	TCNT0 = 0;
	while((PINE & 1) == 0);
	TCCR0B = 0;
    tmp = (TCNT0/2);
	UBRR0 = tmp;
    TCCR0B = 0;
}

ISR(USART0_UDRE_vect) {
    if(!buffer_empty(Tx)) {
		Tx.out_idx = MOD(Tx.out_idx + 1);
		UDR0 = Tx.Buffer[Tx.out_idx];
    } else {
        UCSR0B &= (~(1<<UDRIE0));
		UCSR0A &= (~(1<<TXC0));
    }
}


void UART0_putchar(char data) {
    while(buffer_full(Tx));
	if(buffer_empty(Tx)) {
		Tx.in_idx = MOD(Tx.in_idx + 1);
	    Tx.Buffer[Tx.in_idx] = data;
	    *UCSRB |= (1<<UDRIE0);
	} else { 
		Tx.in_idx = MOD(Tx.in_idx + 1);
    	Tx.Buffer[Tx.in_idx] = data;
	}
}
*/
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
