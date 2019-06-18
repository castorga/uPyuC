//No la entregue porque me falto corregir el offset del ADC R.I.P!!!!!!!!!!!!!!!
#include <avr/io.h>
#include "UART.h"

char Delimitadores[] =  "  . |                                                   | . \r\n";
uint8_t n_medicion = 1;

void ADC_Init() {
	ADMUX = (1<<REFS0)|(1<ADLAR);
	ADCSRA = (1<<ADEN)|(7<<ADPS0);
	ADCSRB = 0;
}


uint16_t ADC_Read(uint8_t channel) {
	if(channel > 0b111) {
		channel += 0b100000;
	}
	if(channel > 0b100111) {
		channel = 0b100111;
	}
	ADMUX |= (channel<<MUX0);
	ADCSRA |= 1<<ADSC;
	while(!(ADCSRA & (1<<ADIF)));
	ADCSRA &= ~(1<<ADIF);
	return ADC;
}

void print_ADC_Value(uint16_t value) {
	value = (value*5)/102;
	if(value < 25) {
		setColor(RED);
	} else {
		setColor(GREEN);
	}
	gotoxy((uint8_t)value + 6, n_medicion);
	UART_putchar('*');
	gotoxy(58, n_medicion);
	UART_putchar(value/10 + '0');
	UART_putchar('.');
    UART_putchar(value%10 + '0'); 
}

int main(void) {
	int i;
	//char str[10];
	UART_Ini(0, 9600, 8, 1, 2);
	uint16_t read = 0;
	clrscr();
	setColor(WHITE);
	for(i = 0; i < 20; i++) {
		UART_puts(Delimitadores);
	}
	gotoxy(1, 20);
	UART_puts("xxxx");
	gotoxy(58, 20);
	UART_puts("x.x");
	ADC_Init();

	while(1) {
		UART_getchar();
		read = ADC_Read(1);
		print_ADC_Value(read);
		n_medicion++;
	}
	return 0;
}
