#define INTR 8
extern void pokeW(unsigned int  segment, unsigned int offset, unsigned int value);
extern void putchar(char Letra); 
volatile static unsigned char SecFlag = 0;

void interrupt ManejadorISR(void) {
    static unsigned char Cont = 0;
    Cont++;
    if(Cont == 20) {
        SecFlag = 1;
        Cont = 0;
    }
}

unsigned char TimerSecFlag(void) {
    if(SecFlag == 1) {
        SecFlag = 0;
        return 1;
    } else
        return 0;
        
}

void Timer_Ini(void) {
    SecFlag = 0;
    pokeW(0x0, INTR*4, ((unsigned int)ManejadorISR) + 0x0100);
    pokeW(0x0, (INTR*4)+2, _CS);
}