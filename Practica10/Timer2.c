#include <avr/interrupt.h>
#include <avr/io.h>
#include <inttypes.h>

static uint8_t Flag; 

void Timer2_Ini(uint8_t baseT) {
	if(baseT < 1) baseT = 1;
	if(baseT > 8) baseT = 8;
	ASSR |= (1<<AS2);
	OCR2A = (uint8_t)((32 * baseT) - 1);
	TCNT2 = 0;
	TCCR2A = 2;
	TCCR2B = 7;
	TIMSK2 = 2;
	sei();
}

uint8_t Timer2_Flag (void) {
	if(Flag) {
		Flag = 0;
		return 1;
	} else return 0;
}

ISR(TIMER2_COMPA_vect) {
	Flag = 1;
}
