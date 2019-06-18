#include <avr/io.h>
#include <avr/interrupt.h>
#include "Timer.h"
#define PRESCALER 1024
#define TICKS(f) ((16000000)/(PRESCALER))/(f)

uint8_t cambio_Nota = 0;
uint8_t Volumen = 0;
uint16_t n_Nota = 0;
uint16_t delay_Nota = 0;
uint16_t Cancion_Longitud;
uint16_t milisegundos = 0;
const struct note *Pointer;

void Timer0_Ini(void) {
	TCCR0A = 0x02;
	TCCR0B = 0x03;
	OCR0A = 249;
	TCNT0 = 0x00;
	TIMSK0 = 0x02;
	sei();
}

ISR(TIMER0_COMPA_vect) {
	milisegundos++;

	if(milisegundos >= delay_Nota) {
		milisegundos = 0;
		if((cambio_Nota == 1) && (n_Nota != Cancion_Longitud)) {
			if(Pointer[n_Nota].freq)
				Timer2_Freq_Gen(TICKS(Pointer[n_Nota].freq));
			else 
				Timer2_Freq_Gen(0);
			delay_Nota = Pointer[n_Nota].delay;
			cambio_Nota = 0;
			n_Nota++;
		} else {
			cambio_Nota = 1;
			Timer2_Freq_Gen(0);
			delay_Nota = SILENCE;
		}
	}
}

void Timer2_Freq_Gen(uint8_t ticks) {
	if(ticks) {
		TCCR2A = (2 << COM2B0)|(3 << WGM20);
		TCCR2B = (7 << CS20)|(1 << WGM22);
		OCR2A = ticks - 1;
		OCR2B = (OCR2A * Volumen)/(100);
	} else {
		TCCR2B = 0;
	}
}

void Timer2_Play(const struct note song[], unsigned int len) {
	Pointer = song;
	n_Nota = 0;
	Cancion_Longitud = len;
	DDRH = (1 << PH6);
	Volumen = 50;
}

void Timer2_Volume(int8_t direction) {
	if(direction) {
		if(Volumen <= 95)
			Volumen += 5;
	} else {
		if(Volumen > 5)
			Volumen -= 5;
	}
}
