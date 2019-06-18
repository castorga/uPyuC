#include "Timer.h"
#define BYTE unsigned char
#define WORD unsigned int
extern void putchar(char Letra);
extern void poke(WORD segment, WORD offset, BYTE data);
void UpdateClock(void);
void DisplayClock(void);
void PrintDec2d(BYTE);
void Delay(BYTE);
void setClock(BYTE Hora, BYTE Minutos, BYTE Segundos);

BYTE seg = 0;
BYTE min = 0;
BYTE hrs = 0;
WORD Direccion = 0xFFFF;
BYTE Dato = 0x0;


void main() {
    Timer_Ini();
    setClock(23, 59, 30);
    while(1) {
        if(TimerSecFlag()) {
            UpdateClock();
            DisplayClock();
            putchar(13);
        }
        poke(0x0, 0xFFFF, seg);
    }
}

void UpdateClock(void) {
    seg = seg + 1;
    if(seg > 59) {
        min = min + 1;
        if(min > 59) {
            hrs = hrs + 1;
            if(hrs > 23) {
                hrs = 0;
            }
            min = 0;
        }
        seg = 0;
    }
    Dato = Dato + 1;
    if(Dato > 255) {
        Dato = 0;
    }
}

void DisplayClock(void) {
    PrintDec2d(hrs);
    putchar(':');
    PrintDec2d(min);
    putchar(':');
    PrintDec2d(seg);
}

void Delay(BYTE i) {
    while(--i);
}

void PrintDec2d(BYTE dato) {
    putchar(dato/10 + '0');
    putchar(dato%10 + '0'); 
}

void setClock(BYTE Hora, BYTE Minutos, BYTE Segundos) {
    seg = Segundos;
    min = Minutos;
    hrs = Hora;
}