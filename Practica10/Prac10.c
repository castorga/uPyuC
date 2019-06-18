#include <avr/io.h>
#include "Timer0.h"
#include "Timer2.h"
#include "UART.h"

void Clock_Update(void);
void Clock_Ini(uint8_t Hora, uint8_t Minutos, uint8_t Segundos);
void Clock_Display(void);
void PrintDec2d(uint8_t dato);

static uint8_t seg = 0;
static uint8_t min = 0;
static uint8_t hrs = 0;
static uint8_t base = 7;

int main(void) {
	char str[20];
	UART0_Ini();
	UART0_AutoBaudRate();
	clrscr();
	gotoxy(5, 1);
	UART0_puts("Autobauding done. UBBR0=");
	itoa(str, UBRR0, 10);
	UART0_puts(str);
	UART0_puts("\n\r");
	Timer0_Ini();
	Timer2_Ini(base);
	Clock_Ini(23, 59, 50);

	while(1) {
		if(Timer2_Flag()) {
			Clock_Update();
			gotoxy(5, 2);
			Clock_Display();
			gotoxy(5, 3);
			UART0_puts("millis=");
			itoa(str, (uint16_t)millis(), 10);
			UART0_puts(str);
			UART0_puts("\r\n");
		}
	}
	return 0;
}

void Clock_Update(void) {
    seg = seg + base;
    if(seg > 59) {
        min = min + 1;
        if(min > 59) {
            hrs = hrs + 1;
            if(hrs > 23) {
                hrs = 0;
            }
            min = 0;
        }
        seg = seg - 60;
    }
}

void Clock_Ini(uint8_t Hora, uint8_t Minutos, uint8_t Segundos) {
    seg = Segundos;
    min = Minutos;
    hrs = Hora;
}

void Clock_Display(void) {
    PrintDec2d(hrs);
    UART0_putchar(':');
    PrintDec2d(min);
    UART0_putchar(':');
    PrintDec2d(seg);
}

void PrintDec2d(uint8_t dato) {
    UART0_putchar(dato/10 + '0');
    UART0_putchar(dato%10 + '0'); 
}
