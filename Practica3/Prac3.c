void puts(char *String);
void prueba_Bus_Datos(unsigned int direccion_base, unsigned int Offset);
void prueba_Bus_Direcciones(unsigned int direccion_base, unsigned int offset_inicial, unsigned int Offset_Max);
extern unsigned char peek(unsigned int segment, unsigned int Offset);
extern void poke(unsigned int segment, unsigned int Offset, unsigned char data);
extern void putchar(char dato);
extern unsigned char getch();
void itoa(char *str, char *pila, unsigned int number, unsigned char base);

char string[21];
char pila[21];

void main ( void ) {
    while( 1 ) {
        puts("\r\nPrueba ducto de datos en 3800\r\n");
        getch();
        prueba_Bus_Datos(0, 0x3800);
        puts("\r\nPrueba ducto de direcciones en 3800\r\n");
        getch();
        prueba_Bus_Direcciones(0, 0x3800, 0x7FF);

        puts("\r\nPrueba ducto de datos en 7800\r\n");
        getch();
        prueba_Bus_Datos(0, 0x7800);
        puts("\r\nPrueba ducto de direcciones en 7800\r\n");
        getch();
        prueba_Bus_Direcciones(0, 0x7800, 0x7FF);
        
        puts("\r\nPrueba ducto de datos en 2200\r\n");
        getch();
        prueba_Bus_Datos(0, 0x2200);
        puts("\r\nPrueba ducto de direcciones en 2200\r\n");
        getch();
        prueba_Bus_Direcciones(0, 0x2200, 0x7FF); 
    }
}

void puts(char *String) {
    while(*String) 
        putchar(*String++);
}

void printBin8(unsigned char number) {
    int i = 0x80;
    do {
        if((i & number) != 0)
            putchar('1');
        else putchar('0');
    i >>= 1;
    } while(i != 0);
}

void prueba_Bus_Datos(unsigned int direccion_base, unsigned int Offset) {
    unsigned char Dato_0;
    unsigned char Dato_1;
    unsigned char Pines;
    unsigned short i = 0;
    poke(direccion_base, Offset, 0xFF);
    Dato_1 = peek(direccion_base, Offset);
    poke(direccion_base, Offset, 0x00);
    Dato_0 = peek(direccion_base, Offset);
    Pines = Dato_1 ^ Dato_0;
    Dato_1 = 0x1;
    do {
        if(!(Pines & Dato_1)) {
            puts("Error en el Ducto D"); putchar((char)i + '0'); puts("\r\n");
        }
        i++;
        Dato_1 <<= 1;
    } while(Dato_1);
}

void prueba_Bus_Direcciones(unsigned int direccion_base, unsigned int offset_inicial, unsigned int Offset_Max) {
    unsigned int Offset;
    unsigned int Offset_Aux;
    unsigned int Pines_Malos = 0;
    unsigned char Dat_Tmp;
    unsigned char Dato = 1;
	
	for(Offset = 1; Offset < (1 << 11); Offset <<= 1) {
		poke(direccion_base, offset_inicial + Offset, 0);
	}
	poke(direccion_base, offset_inicial, 0x55);
	for(Offset = 1; Offset < (1 << 11); Offset <<= 1) {
		if(peek(direccion_base, offset_inicial + Offset) != 0) {
			Pines_Malos = Pines_Malos | Offset;
		}
	}
    for(Offset = 1; Offset < Offset_Max; Offset <<= 1) {
        poke(direccion_base, offset_inicial, 0xFF);
        poke(direccion_base, offset_inicial + Offset, Dato);
        for(Offset_Aux = Offset; Offset_Aux < Offset_Max; Offset_Aux <<= 1) {
            if(Offset_Aux != Offset) {
                Dat_Tmp = peek(direccion_base, offset_inicial + Offset_Aux);
                if((unsigned char)Dato == (unsigned char)Dat_Tmp) {
                    Pines_Malos |= Offset;
                }
            }
        }
        Dat_Tmp = peek(direccion_base, offset_inicial + Offset);
        if((unsigned char)Dat_Tmp != (unsigned char)Dato) {
            Pines_Malos |= Offset;
        }
        Dat_Tmp = peek(direccion_base, 0);
        if((unsigned char)Dat_Tmp == Dato) {
            Pines_Malos |= Offset;
        }
        Dato++;
    }
    puts("\r\n");
    printBin8((unsigned char)(Pines_Malos >> 8));
    printBin8((unsigned char)Pines_Malos); 
	/*Offset = 1;
	Offset_Aux = 0;
	do {
        if(Pines_Malos & Offset) {
            puts("Error en el Ducto A"); putchar((char)Offset_Aux + '0'); puts("\r\n");
        }
        Offset_Aux++;
        Offset <<= 1;
    } while(Offset_Aux < 11);
    puts("\r\n");*/
}