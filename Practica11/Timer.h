#ifndef _TIMER_H
#define _TIMER_H
#include <inttypes.h>

#define c	261
#define d	294
#define e	329
#define f	349
#define g	391
#define gS	415
#define a	440
#define aS	455
#define b	466

#define cH	523
#define cSH	554
#define dH	587
#define dSH	622
#define eH	659
#define fH	698
#define fSH	740
#define gH	784
#define gSH	830
#define aH	880

#define bL 247
#define fS 370
#define cS 277
#define aL 220

#define gL 196
#define dS 311
#define gSL 208
#define cL 131
#define eL 165
#define aSL 233

#define nota_Fin 1

#define TEMPO		125
#define TEMPO_500	500
#define TEMPO_600	600
#define SILENCE	10

struct note {
	uint16_t freq;
	uint16_t delay;
};

void Timer0_Ini(void);
void Timer2_Freq_Gen(uint8_t ticks);
void Timer2_Play(const struct note song[], unsigned int len);
void Timer2_Volume(int8_t direction);

#endif

