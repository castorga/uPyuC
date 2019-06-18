#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>
#include "Timer.h"
#define PRESCALER 1024
#define TICKS(f) ((16000000)/(PRESCALER))/(f)

char strong[20];
uint8_t cambio_Nota = 0;
uint8_t Volumen = 0;
//uint8_t Log = 0x128;
uint16_t n_Nota = 0;
uint16_t delay_Nota = 0;
uint16_t milisegundos = 0;
volatile uint16_t ms = 0;
PGM_P Pointer;
struct note Nota;

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
	ms++;
	if(milisegundos >= delay_Nota) {
		milisegundos = 0;
		if((cambio_Nota == 1) && Nota.freq != END) {
			Nota.freq = pgm_read_word(Pointer + n_Nota);
			Nota.delay = pgm_read_word(Pointer + n_Nota + 2);
			if(Nota.freq > END) {
				Timer2_Freq_Gen(TICKS(Nota.freq));
			}
			else  {
				Timer2_Freq_Gen(0);
			}
			delay_Nota = Nota.delay;
			cambio_Nota = 0;
			n_Nota += 4;
		} else {
			cambio_Nota = 1;
			Timer2_Freq_Gen(0);
			delay_Nota = SILENCE;
		}
	}
}

void Timer2_Freq_Gen(uint8_t ticks) {
	if((ticks) && (Volumen != 0)) {
		TCCR2A = (2 << COM2B0)|(3 << WGM20);
		TCCR2B = (7 << CS20)|(1 << WGM22);
		OCR2A = ticks - 1;
		OCR2B = (OCR2A * Volumen)/(129);
	} else {
		TCCR2B = 0;
	}
}

void Timer2_Play(PGM_P song) {
	Pointer = song;
	Nota.freq = pgm_read_word(Pointer);
	Nota.delay = pgm_read_word(Pointer + 1);
	n_Nota = 0;
	DDRH = (1 << PH6);
	Volumen = 32;
}

void Timer2_Volume(int8_t direction) {
    if(direction == 1) {
        if(Volumen == 0)
            Volumen = 1;
        else if(Volumen < 128)
            Volumen <<= 1;
    } else if(direction == -1) {
        if(Volumen >= 1)
            Volumen >>= 1;
    }
}
