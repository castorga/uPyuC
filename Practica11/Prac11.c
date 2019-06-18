#include <avr/io.h>
#include "UART.h"
#include "Timer.h"

void delay(uint16_t mseg);
uint8_t checkBtn(void);
//#include <avr/pgmspace.h>

//uint8_t checkBtn(void);
#define UNDEFINED 0
#define BtnNEXT 1
#define BtnPREV 2

const struct note AngelesAzules[]={
	{bL, TEMPO_500*3/8},
	{d, TEMPO_500*3/8},
	{fS, TEMPO_500*3/8},
	{493, TEMPO_500*5/4},

	{a, TEMPO_500*3/8},
	{gS, TEMPO_500*3/4},
	{fS, TEMPO_500*3/8},
	{d, TEMPO_500*3/4},
	{bL, TEMPO_500*3/2},
	//first bit

	{bL, TEMPO_500*3/8},
	{d, TEMPO_500*3/8},
	{fS, TEMPO_500*3/8},
	{493, TEMPO_500*5/4},

	{a, TEMPO_500*3/8},
	{gS, TEMPO_500*3/4},
	{fS, TEMPO_500*3/8},
	{d, TEMPO_500*3/4},
	{bL, TEMPO_500*3/2},
	//first bit

	{d, TEMPO_500*3/8},
	{d, TEMPO_500*3/8},
	{d, TEMPO_500*3/8},
	{cS, TEMPO_500*3/8},
	{d, TEMPO_500*5/8},
	{aL, TEMPO_500*5/4},
	
	{d, TEMPO_500*3/8},
	{d, TEMPO_500*3/8},
	{cS, TEMPO_500*3/8},
	{d, TEMPO_500*5/8},
	{aL, TEMPO_500*5/8},

//****************

	{fS, TEMPO_500*3/8},
	{fS, TEMPO_500*3/8},
	{fS, TEMPO_500*3/8},
	{e, TEMPO_500*3/8},
	{fS, TEMPO_500*5/8},
	{cS, TEMPO_500*5/4},

	{fS, TEMPO_500*3/8},
	{fS, TEMPO_500*3/8},
	{e, TEMPO_500*3/8},
	{fS, TEMPO_500*5/8},
	{cS, TEMPO_500*5/8},

//*****************

	{g, TEMPO_500*1/2},
	{g, TEMPO_500*1/2},
	{g, TEMPO_500*1/2},
	{g, TEMPO_500*1/2},
	{e, TEMPO_500*1/2},
	{d, TEMPO_500*1/2},
	{cS, TEMPO_500*3},

	{g, TEMPO_500*1/2},
	{g, TEMPO_500*1/2},
	{g, TEMPO_500*1/2},
	{g, TEMPO_500*1/2},
	{e, TEMPO_500*1/2},
	{d, TEMPO_500*1/2},
	{cS, TEMPO_500*3},

//Se repite todo*****

	{d, TEMPO_500*3/8},
	{d, TEMPO_500*3/8},
	{d, TEMPO_500*3/8},
	{cS, TEMPO_500*3/8},
	{d, TEMPO_500*5/8},
	{aL, TEMPO_500*5/4},
	
	{d, TEMPO_500*3/8},
	{d, TEMPO_500*3/8},
	{cS, TEMPO_500*3/8},
	{d, TEMPO_500*5/8},
	{aL, TEMPO_500*5/8},

//****************

	{fS, TEMPO_500*3/8},
	{fS, TEMPO_500*3/8},
	{fS, TEMPO_500*3/8},
	{e, TEMPO_500*3/8},
	{fS, TEMPO_500*5/8},
	{cS, TEMPO_500*5/4},

	{fS, TEMPO_500*3/8},
	{fS, TEMPO_500*3/8},
	{e, TEMPO_500*3/8},
	{fS, TEMPO_500*5/8},
	{cS, TEMPO_500*5/8},

//*****************

	{g, TEMPO_500*1/2},
	{g, TEMPO_500*1/2},
	{g, TEMPO_500*1/2},
	{g, TEMPO_500*1/2},
	{e, TEMPO_500*1/2},
	{d, TEMPO_500*1/2},
	{cS, TEMPO_500*3},

	{g, TEMPO_500*1/2},
	{g, TEMPO_500*1/2},
	{g, TEMPO_500*1/2},
	{g, TEMPO_500*1/2},
	{e, TEMPO_500*1/2},
	{d, TEMPO_500*1/2},
	{cS, TEMPO_500*3}
	//and we're done
};
const struct note Sans[] = {
    {d, TEMPO},
    {d, TEMPO},
    {dH, TEMPO*2},
    {a, TEMPO*3},
    {gS, TEMPO*2},
    {g, TEMPO*2},
    {f, TEMPO*2},
    {d, TEMPO},
    {f, TEMPO},
    {g, TEMPO},

    {c, TEMPO},
    {c, TEMPO},
    {dH, TEMPO*2},
    {a, TEMPO*3},
    {gS, TEMPO*2},
    {g, TEMPO*2},
    {f, TEMPO*2},
    {d, TEMPO},
    {f, TEMPO},
    {g, TEMPO},

    {246, TEMPO},
    {246, TEMPO},
    {dH, TEMPO*2},
    {a, TEMPO*3},
    {gS, TEMPO*2},
    {g, TEMPO*2},
    {f, TEMPO*2},
    {d, TEMPO},
    {f, TEMPO},
    {g, TEMPO},

    {233, TEMPO},
    {233, TEMPO},
    {dH, TEMPO*2},
    {a, TEMPO*3},
    {gS, TEMPO*2},
    {g, TEMPO*2},
    {f, TEMPO*2},
    {d, TEMPO},
    {f, TEMPO},
    {g, TEMPO},

};

const struct note Test[] = {
    {a, TEMPO},
    {a, TEMPO},
    {aH, TEMPO*2},
    {a, TEMPO*3},
    {aS, TEMPO*2},
    {a, TEMPO*2},
    {a, TEMPO*2},
    {a, TEMPO},
    {a, TEMPO},
    {a, TEMPO},
    {a, TEMPO},
    {a, TEMPO},
    {aH, TEMPO*2},
    {a, TEMPO*3},
    {aS, TEMPO*2},
    {a, TEMPO*2},
    {a, TEMPO*2},
    {a, TEMPO},
    {a, TEMPO},
    {a, TEMPO},
    {a, TEMPO},
    {a, TEMPO},
    {aH, TEMPO*2},
    {a, TEMPO*3},
    {aS, TEMPO*2},
    {a, TEMPO*2},
    {a, TEMPO*2},
    {a, TEMPO},
    {a, TEMPO},
    {a, TEMPO},
    {a, TEMPO},
    {a, TEMPO},
    {aH, TEMPO*2},
    {a, TEMPO*3},
    {aS, TEMPO*2},
    {a, TEMPO*2},
    {a, TEMPO*2},
    {a, TEMPO},
    {a, TEMPO},
    {a, TEMPO},

};

const struct note* Canciones[] = {
	AngelesAzules,
	Sans,
	Test
};

const uint8_t Duracion_Canciones[] = {
	sizeof(AngelesAzules)/sizeof(struct note),
	sizeof(Sans)/sizeof(struct note),
	sizeof(Test)/sizeof(struct note)
};

/*
const struct note arps[] PROGMEM = {
    {c, 32},
    {e, 32},
    {g, 32},
};

PGM_P const CANCIONES[] =
{
	&ImperialMarch[0],
	&arps[0]
};*/

int main(void) {
//	char data;
//	uint8_t cnt = 0;
//	uint8_t idx = 0;
	int i = 0;
	UART0_Ini();
	UART0_AutoBaudRate();
	UART0_puts("aaah");
	Timer0_Ini();
	DDRD = 	0b11110110;
	PORTD = 0b00001001;
	while(1) {
		if(UART0_available()) {
			switch(UART0_getchar()) {
				case 'p':
				case 'P':
					Timer2_Play(Canciones[i], Duracion_Canciones[i]);
					//UART0_putchar('p');
					break;
				case 'V':
					Timer2_Volume(1);
					break;
				case 'v':
					Timer2_Volume(-1);
					break;
				default: 
					break;
			}
			switch(checkBtn()) {
				case BtnNEXT:
					UART0_puts("boton1\r\n");
					if(i >= (sizeof(Canciones)/sizeof(struct note*) - 1)) 
						i = 0;
					else 
						i++;
					Timer2_Play(Canciones[i], Duracion_Canciones[i]);
					break;
				case BtnPREV:
					UART0_puts("boton2\r\n");
					if(i == 0) 
						i = (sizeof(Duracion_Canciones)/(sizeof(uint8_t))) - 1;
					else 
						i--;
					Timer2_Play(Canciones[i],Duracion_Canciones[i]);
					break;
				default:
					break;
			}
		}
	}
	return 0;
}

uint8_t checkBtn(void) {
	uint8_t state = UNDEFINED;
	if(PIND & 0b00001000)
		state = BtnNEXT;
	if(PIND & 0b00000001)
		state = BtnPREV;
	return state;
}

void delay(uint16_t mseg) {
    volatile uint16_t i, j;
	for(i = 0; i < mseg; i++) {
		for(j = 0; j < 887; j++) {
	        //__asm__ __volatile__ ("nop");
	    }
	}
}
