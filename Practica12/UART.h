#ifndef _UART_H
#define _UART_H

#define MOD(idx)                ((idx)&(BUFFER_SIZE - 1))
#define buffer_full(buffer)     (buffer.out_idx == MOD(buffer.in_idx + 1))
#define buffer_empty(buffer)    (buffer.out_idx == buffer.in_idx)    
#define BUFFER_SIZE             64
#define Frecuencia              16000000
#define UART_BAUDRATE           9600
#define UART_parity             0
#define UART_BIT_SIZE           3
#define UART_com                0
#define UART_stop               0
#define GREEN			32
#define YELLOW			33
#define RED             31
#define BLUE			34
#define WHITE           37

typedef struct {
    char Buffer[BUFFER_SIZE];
    volatile unsigned char in_idx;
    volatile unsigned char out_idx;
} ring_buffer_t;

extern ring_buffer_t Rx;
extern ring_buffer_t Tx;

extern uint8_t* UCSRA;
extern uint8_t* UCSRB;
extern uint8_t* UCSRC;
extern uint8_t* UBBRL;
extern uint8_t* UBBRH;

void UART_Ini(uint8_t com, uint16_t baudrate, uint8_t size, uint8_t parity, uint8_t stop);
uint8_t UART_Available(void);
void UART_putchar(char data);
char UART_getchar(void);
void UART_puts(char *str);
void UART_gets(char *str);
unsigned int atoi(char *str);
void itoa(char *str, uint16_t number, unsigned char base);
void clrscr();
void gotoxy(int x, int y);
void setColor(uint8_t Color);

#endif

