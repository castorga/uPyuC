#include <avr/interrupt.h>
#include <inttypes.h>
#include "Timer0.h"

volatile uint32_t ms = 0;

void Timer0_Ini (void) {
	DDRB |= (1 << PB7);
	OCR0A = 249;
	TCNT0 = 0x00;
	TCCR0A = (2<<WGM00);
	TCCR0B = 0x03;
	TIMSK0 = 0x02;
	sei();
}

ISR(TIMER0_COMPA_vect) {
	ms++;
}

uint32_t millis(void) {
	return ms;
}


