//Practica 11 Tocar musica mediante el PWM del microcontrolador
//Se utiliza el Timer0 para el tiempo de las notas y el Timer2 se utiliza en modo PWM para generar las notas
//Se implementan botones fisicos para poder cambiar la musica
//Agarre la musica de sans porque esta chistosa aunque no me gusta undertale 
#include <avr/io.h>
#include <avr/pgmspace.h>
#include "UART.h"
#include "Timer.h"

uint8_t checkBtn(void);
#define UNDEFINED 0
#define BtnNEXT 8
#define BtnPREV 1

const struct note AngelesAzules[] PROGMEM ={
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
	{cS, TEMPO_500*3},
	{END, 0}
	//and we're done
};
const struct note Sans[] PROGMEM = {
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
	{END, 0}
};

const struct note Mario [] PROGMEM ={
	//INTRO
	{e, TEMPO_600/4},
	{e, TEMPO_600/4},
	{0, TEMPO_600/4},
	{e, TEMPO_600/4},
	{0, TEMPO_600/4},
	{c, TEMPO_600/4},
	{e, TEMPO_600/4},
	{0, TEMPO_600/4},
	{g, TEMPO_600/4},
	{0, TEMPO_600/4},
	{0, TEMPO_600/2},
	{gL, TEMPO_600/4},
	{0, TEMPO_600/4},
	{0, TEMPO_600/2},
	//PARTE A
	{c, TEMPO_600/4},
	{0, TEMPO_600/4},
	{0, TEMPO_600/4},
	{gL, TEMPO_600/4},
	{0, TEMPO_600/2},
	{eL, TEMPO_600/4},
	{0, TEMPO_600/4},
	{0, TEMPO_600/4},
	{aL, TEMPO_600/4},
	{0, TEMPO_600/4},
	{bL, TEMPO_600/4},
	{0, TEMPO_600/4},
	{aSL, TEMPO_600/4},
	{aL, TEMPO_600/4},
	{0, TEMPO_600/4},
	{gL, TEMPO_600/3},
	{e, TEMPO_600/3},
	{g, TEMPO_600/3},
	{a, TEMPO_600/4},
	{0, TEMPO_600/4},
	{f, TEMPO_600/4},
	{g, TEMPO_600/4},
	{0, TEMPO_600/4},
	{e, TEMPO_600/4},
	{0, TEMPO_600/4},
	{c, TEMPO_600/4},
	{d, TEMPO_600/4},
	{bL, TEMPO_600/4},
	{0, TEMPO_600/2},
	{c, TEMPO_600/4},
	{0, TEMPO_600/4},
	{0, TEMPO_600/4},
	{gL, TEMPO_600/4},
	{0, TEMPO_600/2},
	{eL, TEMPO_600/4},
	{0, TEMPO_600/4},
	{0, TEMPO_600/4},
	{aL, TEMPO_600/4},
	{0, TEMPO_600/4},
	{bL, TEMPO_600/4},
	{0, TEMPO_600/4},
	{aSL, TEMPO_600/4},
	{aL, TEMPO_600/4},
	{0, TEMPO_600/4},
	{gL, TEMPO_600/3},
	{e, TEMPO_600/3},
	{g, TEMPO_600/3},
	{a, TEMPO_600/4},
	{0, TEMPO_600/4},
	{f, TEMPO_600/4},
	{g, TEMPO_600/4},
	{0, TEMPO_600/4},
	{e, TEMPO_600/4},
	{0, TEMPO_600/4},
	{c, TEMPO_600/4},
	{d, TEMPO_600/4},
	{bL, TEMPO_600/4},
	{0, TEMPO_600/2},
	//PARTE B
	{0, TEMPO_600/2},
	{g, TEMPO_600/4},
	{fS,TEMPO_600/4},
	{e, TEMPO_600/4},
	{dS, TEMPO_600/4},
	{0, TEMPO_600/4},
	{e, TEMPO_600/4},
	{0, TEMPO_600/4},
	{gSL, TEMPO_600/4},
	{aL, TEMPO_600/4},
	{c, TEMPO_600/4},
	{0, TEMPO_600/4},
	{aL, TEMPO_600/4},
	{c, TEMPO_600/4},
	{d,TEMPO_600/4},
	{0, TEMPO_600/2},
	{g, TEMPO_600/4},
	{fS, TEMPO_600/4},
	{e, TEMPO_600/4},
	{dS, TEMPO_600/4},
	{0, TEMPO_600/4},
	{e,TEMPO_600/4},
	{0, TEMPO_600/4},
	{cH, TEMPO_600/4},
	{0, TEMPO_600/4},
	{cH, TEMPO_600/4},
	{cH, TEMPO_600/4},
	{0, TEMPO_600/4},
	{0,TEMPO_600/2},
	{0, TEMPO_600/2},
	{g, TEMPO_600/4},
	{fS, TEMPO_600/4},
	{e, TEMPO_600/4},
	{dS, TEMPO_600/4},
	{0, TEMPO_600/4},
	{e,TEMPO_600/4},
	{0, TEMPO_600/4},
	{gSL, TEMPO_600/4},
	{aL, TEMPO_600/4},
	{c, TEMPO_600/4},
	{0, TEMPO_600/4},
	{aL, TEMPO_600/4},
	{c, TEMPO_600/4},
	{d,TEMPO_600/4},
	{0, TEMPO_600/2},
	{dS, TEMPO_600/4},
	{0, TEMPO_600/4},
	{0, TEMPO_600/4},
	{d, TEMPO_600/4},
	{0,TEMPO_600/2},
	{c, TEMPO_600/4},
	{0, TEMPO_600/4},
	{0, TEMPO_600/2},
	{0,TEMPO_600},
	{0, TEMPO_600/2},
	{g, TEMPO_600/4},
	{fS, TEMPO_600/4},
	{e, TEMPO_600/4},
	{dS, TEMPO_600/4},
	{0, TEMPO_600/4},
	{e,TEMPO_600/4},
	{0, TEMPO_600/4},
	{gSL, TEMPO_600/4},
	{aL, TEMPO_600/4},
	{c, TEMPO_600/4},
	{0, TEMPO_600/4},
	{aL, TEMPO_600/4},
	{c, TEMPO_600/4},
	{d,TEMPO_600/4},
	{0, TEMPO_600/2},
	{g, TEMPO_600/4},
	{fS, TEMPO_600/4},
	{e, TEMPO_600/4},
	{dS, TEMPO_600/4},
	{0, TEMPO_600/4},
	{e,TEMPO_600/4},
	{0, TEMPO_600/4},
	{cH, TEMPO_600/4},
	{0, TEMPO_600/4},
	{cH, TEMPO_600/4},
	{cH, TEMPO_600/4},
	{0, TEMPO_600/4},
	{0,TEMPO_600/2},
	{0, TEMPO_600/2},
	{g, TEMPO_600/4},
	{fS, TEMPO_600/4},
	{e, TEMPO_600/4},
	{dS, TEMPO_600/4},
	{0, TEMPO_600/4},
	{e,TEMPO_600/4},
	{0, TEMPO_600/4},
	{gSL, TEMPO_600/4},
	{aL, TEMPO_600/4},
	{c, TEMPO_600/4},
	{0, TEMPO_600/4},
	{aL, TEMPO_600/4},
	{c, TEMPO_600/4},
	{d,TEMPO_600/4},
	{0, TEMPO_600/2},
	{dS, TEMPO_600/4},
	{0, TEMPO_600/4},
	{0, TEMPO_600/4},
	{d, TEMPO_600/4},
	{0,TEMPO_600/2},
	{c, TEMPO_600/4},
	{0, TEMPO_600/4},
	{0, TEMPO_600/2},
	{0,TEMPO_600},
	//PARTE C
	{c, TEMPO_600/4},
	{c, TEMPO_600/4},
	{0, TEMPO_600/4},
	{c, TEMPO_600/4},
	{0, TEMPO_600/4},
	{c, TEMPO_600/4},
	{d, TEMPO_600/4},
	{0, TEMPO_600/4},
	{e, TEMPO_600/4},
	{c, TEMPO_600/4},
	{0, TEMPO_600/4},
	{aL, TEMPO_600/4},
	{gL, TEMPO_600/4},
	{0,TEMPO_600/4},
	{0,TEMPO_600/2},
	{c, TEMPO_600/4},
	{c, TEMPO_600/4},
	{0, TEMPO_600/4},
	{c, TEMPO_600/4},
	{0, TEMPO_600/4},
	{c, TEMPO_600/4},
	{d, TEMPO_600/4},
	{e,TEMPO_600/4},
	{0,TEMPO_600*2},
	{c, TEMPO_600/4},
	{c, TEMPO_600/4},
	{0, TEMPO_600/4},
	{c, TEMPO_600/4},
	{0, TEMPO_600/4},
	{c, TEMPO_600/4},
	{d, TEMPO_600/4},
	{0, TEMPO_600/4},
	{e, TEMPO_600/4},
	{c, TEMPO_600/4},
	{0, TEMPO_600/4},
	{aL, TEMPO_600/4},
	{gL, TEMPO_600/4},
	{0, TEMPO_600/4},
	{0,TEMPO_600/2},
	{e, TEMPO_600/4},
	{e, TEMPO_600/4},
	{0, TEMPO_600/4},
	{e, TEMPO_600/4},
	{0, TEMPO_600/4},
	{c, TEMPO_600/4},
	{e, TEMPO_600/4},
	{0,TEMPO_600/4},
	{g, TEMPO_600/4},
	{0, TEMPO_600/4},
	{0, TEMPO_600/2},
	{gL, TEMPO_600/4},
	{0, TEMPO_600/4},
	{0, TEMPO_600/2},
	//PARTE D
	{e, TEMPO_600/4},
	{c, TEMPO_600/4},
	{0, TEMPO_600/4},
	{gL, TEMPO_600/4},
	{0, TEMPO_600/2},
	{gSL, TEMPO_600/4},
	{0,TEMPO_600/4},
	{aL, TEMPO_600/4},
	{f, TEMPO_600/4},
	{0, TEMPO_600/4},
	{f, TEMPO_600/4},
	{aL, TEMPO_600/4},
	{0, TEMPO_600/4},
	{0,TEMPO_600/2},
	{bL, TEMPO_600/3},
	{a, TEMPO_600/3},
	{a, TEMPO_600/3},
	{a, TEMPO_600/3},
	{g, TEMPO_600/3},
	{f,TEMPO_600/3},
	{e, TEMPO_600/4},
	{c, TEMPO_600/4},
	{0, TEMPO_600/4},
	{aL, TEMPO_600/4},
	{gL, TEMPO_600/4},
	{0, TEMPO_600/4},
	{0,TEMPO_600/2},
	{e, TEMPO_600/4},
	{c, TEMPO_600/4},
	{0, TEMPO_600/4},
	{gL, TEMPO_600/4},
	{0, TEMPO_600/2},
	{gSL, TEMPO_600/4},
	{0,TEMPO_600/4},
	{aL, TEMPO_600/4},
	{f, TEMPO_600/4},
	{0, TEMPO_600/4},
	{f, TEMPO_600/4},
	{aL, TEMPO_600/4},
	{0, TEMPO_600/4},
	{0,TEMPO_600/2},
	{bL, TEMPO_600/4},
	{f, TEMPO_600/4},
	{0, TEMPO_600/4},
	{f, TEMPO_600/4},
	{f, TEMPO_600/3},
	{e, TEMPO_600/3},
	{d,TEMPO_600/3},
	{c, TEMPO_600/4},
	{eL, TEMPO_600/4},
	{0, TEMPO_600/4},
	{eL, TEMPO_600/4},
	{cL, TEMPO_600/4},
	{0, TEMPO_600/4},
	{0, TEMPO_600/2},
	{END, 0}
};

const struct note ImperialMarch[] PROGMEM ={
	{a, TEMPO_500},
	{a, TEMPO_500},
	{a, TEMPO_500},
	{f, TEMPO_500*3/4},
	{cH, TEMPO_500*1/4},

	{a, TEMPO_500},
	{f, TEMPO_500*3/4},
	{cH, TEMPO_500*1/4},
	{a, TEMPO_500*2},
	//first bit

	{eH, TEMPO_500},
	{eH, TEMPO_500},
	{eH, TEMPO_500},
	{fH, TEMPO_500*3/4},
	{cH, TEMPO_500*1/4},

	{gS, TEMPO_500},
	{f, TEMPO_500*3/4},
	{cH, TEMPO_500*1/4},
	{a, TEMPO_500*2},
	//second bit...

	{aH, TEMPO_500},
	{a, TEMPO_500*3/4},
	{a, TEMPO_500*1/4},
	{aH, TEMPO_500},
	{gSH, TEMPO_500/2},
	{gH, TEMPO_500/2},

	{fSH, TEMPO_500*1/4},
	{fH, TEMPO_500*1/4},
	{fSH, TEMPO_500/2},
	{0,TEMPO_500/2},
	{aS, TEMPO_500/2},
	{dSH, TEMPO_500},
	{dH, TEMPO_500/2},
	{cSH, TEMPO_500/2},
	//start of the interesting bit

	{cH, TEMPO_500*1/4},
	{b, TEMPO_500*1/4},
	{cH, TEMPO_500/2},
	{0,TEMPO_500/2},
	{f, TEMPO_500*1/4},
	{gS, TEMPO_500},
	{f, TEMPO_500*3/4},
	{a, TEMPO_500*1/4},

	{cH, TEMPO_500},
	{a, TEMPO_500*3/4},
	{cH, TEMPO_500*1/4},
	{eH, TEMPO_500*2},
	//more interesting stuff (this doesn't quite get it right somehow)

	{aH, TEMPO_500},
	{a, TEMPO_500*3/4},
	{a, TEMPO_500*1/4},
	{aH, TEMPO_500},
	{gSH, TEMPO_500/2},
	{gH, TEMPO_500/2},

	{fSH, TEMPO_500*1/4},
	{fH, TEMPO_500*1/4},
	{fSH, TEMPO_500/2},
	{0,TEMPO_500/2},
	{aS, TEMPO_500/2},
	{dSH, TEMPO_500},
	{dH, TEMPO_500/2},
	{cSH, TEMPO_500/2},
	//repeat... repeat

	{cH, TEMPO_500*1/4},
	{b, TEMPO_500*1/4},
	{cH, TEMPO_500/2},
	{0,TEMPO_500/2},
	{f, TEMPO_500/2},
	{gS, TEMPO_500},
	{f, TEMPO_500*3/4},
	{cH, TEMPO_500*1/4},

	{a, TEMPO_500},
	{f, TEMPO_500*3/4},
	{c, TEMPO_500*1/4},
	{a, TEMPO_500*2},
	{END, 0}
	//and we're done
};

PGM_P Canciones[] = {
	(PGM_P)AngelesAzules,
	(PGM_P)Sans,
	(PGM_P)Mario,
	(PGM_P)ImperialMarch
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
	int i = 1;
	char str[20];
	UART_Ini(0, 12345, 8, 1, 2);
	UART0_AutoBaudRate();
	UART_puts("Autobaud rate done\r\n");
	Timer0_Ini();
	DDRD = 	0b00000000;
	PORTD = 0b11111111;
	while(1) {
		switch(checkBtn()) {
			case BtnNEXT:
				UART_puts("Siguiente cancion\r\n");
				if(i >= (sizeof(Canciones)/sizeof(PGM_P) - 1)) 
					i = 0;
				else 
					i++;
				Timer2_Play(Canciones[i]);
				break;
			case BtnPREV:
				UART_puts("Cancion anterior\r\n");
				if(i == 0) 
					i = sizeof(Canciones)/sizeof(PGM_P) - 1;
				else 
					i--;
				Timer2_Play(Canciones[i]);
				break;
			default:
				break;
			}
		if(!buffer_empty(Rx)) {
			switch(UART_getchar()) {
				case 'p':
				case 'P':
					UART_puts("Play\r\n");
					Timer2_Play(Canciones[i]);
					break;
				case 'V':
					Timer2_Volume(1);
					UART_puts("Volumen 0-128: ");
					itoa(str, (Volumen*100)/128, 10);
					UART_puts(str);
					UART_puts("\r\n");
					break;
				case 'v':
					Timer2_Volume(-1);
					UART_puts("Volumen 0-128: ");
					itoa(str, (Volumen*100)/128, 10);
					UART_puts(str);
					UART_puts("\r\n");
					break;
				default: 
					break;
			}
		}
	}
	return 0;
}

uint8_t checkBtn(void) {
    uint8_t status = UNDEFINED;
    uint16_t msec = 0;
    if(~PIND & 9){
		while(1) {
			status = ~PIND;
			msec = ms;
        	while((ms - msec) < 50);
			if(!(~PIND & 9))
				break;
		}
    }
    return status;
}
