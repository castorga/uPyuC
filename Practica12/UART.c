#include <avr/io.h>
#include <avr/interrupt.h>
#include "UART.h"

ring_buffer_t Rx;
ring_buffer_t Tx;

uint8_t* UCSRA;
uint8_t* UCSRB;
uint8_t* UCSRC;
uint8_t* UBBRL;
uint8_t* UBBRH;

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
	//*UCSRB |= (1<<RXCIE0)|(3<<3);  //Habilitar interrupciones y transmision/recepcion
	*UCSRB |= (1 << UDRIE0)|(1<<RXCIE0)|(0b11<<3);
	*UCSRB |= (4&(size));    //Bits de datos para el 9
	*UCSRC |= (2&(size)) << 1;   //Bits de datos normales
	*UCSRC |= ((3&parity) << 4);	//Paridad
	*UCSRC |= ((11&stop) << 3);	//Stop bits
	*UBBRH = (uint8_t)(UBBR >> 8);
	*UBBRL = (uint8_t)(UBBR);     
    
    Rx.in_idx = 0;
    Tx.in_idx = 0;
    Rx.out_idx = 0;
    Tx.out_idx = 0;

    sei();
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

ISR(USART0_RX_vect) {
	if(UART_Available()) {
		Rx.in_idx = MOD(Rx.in_idx + 1);
		Rx.Buffer[Rx.in_idx] = UDR0;
	}
}

uint8_t UART_Available(void) {
    if(!buffer_full(Rx))
		return 1;
	return 0;
}

void UART_putchar(char data) {
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

char UART_getchar(void) {
	char data = 0;
	while(buffer_empty(Rx));
	Rx.out_idx = MOD(Rx.out_idx + 1);
	data = Rx.Buffer[Rx.out_idx];
	//UART_putchar(data);
	return data;
}

void UART_puts(char *str) {
    while(*str) UART_putchar(*str++);
}

void UART_gets(char *str) {
    int i = 0;
    char data;
    data = UART_getchar();
    while(data != 13) {
        if(data == '\b') {
            if(i > 0) {
                UART_putchar('\b');
				UART_putchar(' ');
				UART_putchar('\b');
                str[i] = 0;
                i--;
            }
        } else {
                if(i > 20) {
                    UART_putchar(' ');
					UART_putchar('\b');
                } else if(data == 10) {
                    UART_putchar('\r');
                    break;
                } else {
					UART_putchar(data);
                    str[i] = data;
                    i++;
                }
            }
        data = UART_getchar();
    }
	UART_putchar('\r');
	UART_putchar('\n');
    str[i] = 0;
}

unsigned int atoi(char *str) {
    int i;
    unsigned int numero = 0;
    for(i = 0; str[i] != '\0'; i++) {
        if(str[i] < '0' || str[i] > '9') 
            break;
        numero = numero*10 + str[i] - '0';
    }
    return numero;
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
	UART_puts("\033[2J\033[H");
}

void gotoxy(int x, int y) {
	UART_putchar('\033');
	UART_putchar('[');
	UART_putchar(y/10 + '0');
	UART_putchar(y%10 + '0');
	UART_putchar(';');
	UART_putchar(x/10 + '0');
	UART_putchar(x%10 + '0');
	UART_putchar('H');
}

void setColor(uint8_t Color) {
	UART_puts("\033[0");
	UART_putchar(Color/10 + '0');
	UART_putchar(Color%10 + '0');
	UART_puts("m");
}
