#define BYTE unsigned char
#define WORD unsigned int

#define PA 0x40
#define PB 0x41
#define PC 0x42
#define RCtr 0x43
#define PTOs_all_out 0x80
extern BYTE inportb(WORD port);
extern void outportb(WORD port, BYTE dato);
extern BYTE getchar();
extern void putchar();
void outportb(WORD, BYTE);
void printLeds(BYTE Dato);
void SetBitPort(WORD Puerto, BYTE num_bit);
void ClrBitPort(WORD Puerto, BYTE num_bit);
void NotBitPort(WORD Puerto, BYTE num_bit);
void delay(int ms);
BYTE TstBitPort(WORD Puerto, BYTE num_bit);

BYTE dato = 0;
BYTE i;

void main(void) {
    outportb(RCtr, 0x88);
    for(i = 0; i < 8; i++) {
        putchar(i + '0');
        getchar();
        putchar(TstBitPort(PC, 4) + '0');
        dato |= TstBitPort(PC, 4) << i;
        putchar('\r');
        putchar('\n');
    }
    outportb(RCtr, PTOs_all_out);
    while(1) {
        printLeds(dato);
    }
}

void delay(int ms) {
    while(--ms);
}

void printLeds(BYTE Dato) {
    outportb(RCtr, 0x89);
    ClrBitPort(PA, 0);
    (0x1 & Dato) ? SetBitPort(PB, 0) : ClrBitPort(PB, 0);

    getchar();

    ClrBitPort(PB, 0);
    (0x1 & (Dato >> 1)) ? SetBitPort(PA, 0) : ClrBitPort(PA, 0);

    getchar();

    NotBitPort(RCtr, 0);
    NotBitPort(RCtr, 3);
    NotBitPort(RCtr, 4);
    ClrBitPort(PB, 0);
    (0x1 & (Dato >> 2)) ? SetBitPort(PC, 0) : ClrBitPort(PC, 0);

    getchar();

    ClrBitPort(PC, 0);
    (0x1 & (Dato >> 3)) ? SetBitPort(PB, 0) : ClrBitPort(PB, 0);

    getchar();

    NotBitPort(RCtr, 1);
    NotBitPort(RCtr, 4);
    ClrBitPort(PC, 0);
    (0x1 & (Dato >> 4)) ? SetBitPort(PA, 0) : ClrBitPort(PA, 0);

    getchar();

    ClrBitPort(PA, 0);
    (0x1 & (Dato >> 5)) ? SetBitPort(PC, 0) : ClrBitPort(PC, 0);

    getchar();

}


void SetBitPort(WORD Puerto, BYTE num_bit) {
    outportb(Puerto, (inportb(Puerto) | (0x01 << num_bit)));
}

void ClrBitPort(WORD Puerto, BYTE num_bit) {
    outportb(Puerto, (inportb(Puerto) & (~(0x01 << num_bit))));
}

void NotBitPort(WORD Puerto, BYTE num_bit) {
    outportb(Puerto, (inportb(Puerto) ^ (0x01 << num_bit)));
}

BYTE TstBitPort(WORD Puerto, BYTE num_bit) {
    if((inportb(Puerto) & (0x01 << num_bit)) != 0)
        return 1;
    else
        return 0;
}