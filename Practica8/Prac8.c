#include <avr/io.h>

#define SetBitPort(port, bit) __asm__ ( "sbi %0, %1" : : "I" (_SFR_IO_ADDR(port)), "I" (bit) )
#define ClrBitPort(port, bit) __asm__ ( "cbi %0, %1" : : "I" (_SFR_IO_ADDR(port)), "I" (bit) )

#define UNDEFINED       0
#define SHORT_PRESSED   1
#define LONG_PRESSED    2

void    delay(uint16_t mseg);
void    InitPorts(void);
uint8_t checkBtn(void);
void    updateLeds(void);

uint8_t     globalCounter = 0;
uint32_t    millis = 0;

int main(void) {
    InitPorts();
    while(1) {
        switch(checkBtn()) {
            case SHORT_PRESSED:     globalCounter++;
                                    break;
            case LONG_PRESSED:      globalCounter--;
                                    break;
        }
        updateLeds();
        delay(1);
        millis++;
    }
}

void InitPorts(void) {
	DDRF 	= 0b10011111;
	PORTF 	= 0b01100000;
    return;
}
uint8_t checkBtn(void) {
    uint8_t i, status = UNDEFINED;
    if(!(PINF & 0b00100000)) {
		updateLeds();
		delay(2);
        while(1) {
            for(i = 0; i < 54; i++) {
                updateLeds();
				delay(1);
				if((PINF & 0b00100000))
					break;
            }
            if((PINF & 0b00100000)) {
                if(status == UNDEFINED)
                    status = SHORT_PRESSED;
                else
                    status = LONG_PRESSED;
                break;
            }
            if(status == UNDEFINED) 
                status = SHORT_PRESSED;
        }
    }
    return status;
}

void updateLeds(void) {
    SetBitPort(DDRF, 0);
    SetBitPort(DDRF, 1);
    ClrBitPort(DDRF, 2);
    ClrBitPort(DDRF, 3);
    ClrBitPort(PORTF, 2);
    ClrBitPort(PORTF, 3);

    ClrBitPort(PORTF, 0);
    if(globalCounter & 1) {
        SetBitPort(PORTF, 1);
    } else {
        ClrBitPort(PORTF, 1);
    }

    delay(1);

    ClrBitPort(PORTF, 1);
    if((globalCounter >> 1) & 1) {
        SetBitPort(PORTF, 0);
    } else {
        ClrBitPort(PORTF, 0);
    }

    delay(1);

    ClrBitPort(DDRF, 0);
    ClrBitPort(PORTF, 0);
    SetBitPort(DDRF, 2);
    if((globalCounter >> 2) & 1) {
        SetBitPort(PORTF, 2);
    } else {
        ClrBitPort(PORTF, 2);
    }

    delay(1);

    ClrBitPort(PORTF, 2);
    if((globalCounter >> 3) & 1) {
        SetBitPort(PORTF, 1);
    } else {
        ClrBitPort(PORTF, 1);
    }

    delay(1);

    SetBitPort(DDRF, 0);
    ClrBitPort(DDRF, 1);
    ClrBitPort(PORTF, 1);
    if((globalCounter >> 4) & 1) {
        SetBitPort(PORTF, 0);
    } else {
        ClrBitPort(PORTF, 0);
    }

    delay(1);

    ClrBitPort(PORTF, 0);
    if((globalCounter >> 5) & 1) {
        SetBitPort(PORTF, 2);
    } else {
        ClrBitPort(PORTF, 2);
    }

    delay(1);

    ClrBitPort(DDRF, 0);
    ClrBitPort(PORTF, 0);
	ClrBitPort(DDRF, 1);
	ClrBitPort(PORTF, 1);
    SetBitPort(DDRF, 3);
    ClrBitPort(PORTF, 2);
    if((globalCounter >> 6) & 1) {
        SetBitPort(PORTF, 3);
    } else {
        ClrBitPort(PORTF, 3);
    }

    delay(1);

    ClrBitPort(PORTF, 3);
    if((globalCounter >> (uint8_t)7) & 1) {
        SetBitPort(PORTF, 2);
    } else {
        ClrBitPort(PORTF, 2);
    }

    delay(1);
}

void delay(uint16_t mseg) {
    volatile uint16_t i, j;
	for(i = 0; i < mseg; i++) {
		for(j = 0; j < 887; j++) {
	        //__asm__ __volatile__ ("nop");
	    }
	}
}
