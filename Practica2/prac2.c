//Practica 2 para repasar conocimientos de C
//Programa que tenia que imprimir el numero decimal introducido en binario y hexadecimal e imprimirlos
//Se tenian que implementar funciones hechas en ensamblador y llamarlas desde C.
void putchar(char data);
char getchar(void);
void puts(char *str);
void gets(char *str);
void itoa(char *str, unsigned int number, unsigned char base);
unsigned int atoi(char *str);
char string[21];
char pila[21];
char letra;
int i = 0;
int j = 0;
unsigned int numero;
unsigned int residuo;

void main(void) {
    while(1) {
        puts("Input: ");
     /*   puts("\n\r"); */
        gets(string);
        puts("\n\r");
        numero = atoi(string);
        itoa(string, numero, 16);
        puts("Hex -> ");
        puts(string);
        puts("\n\r");
        itoa(string, numero, 2);
        puts("Bin -> ");
        puts(string);
        puts("\n\r");
    }
}

void puts(char *str) {
    while(*str)
        putchar(*str++);
    /* putchar(10);
    putchar(13); */
}

void gets( char *str ) {
    const char* aux = str;
    i = 0;
    letra = getchar();
    while(letra != 13) {
        if (letra == '\b') {
            if(i > 0) {
                putchar(' ');
                putchar('\b');
                str[i] = 0;
                i--;
            } else {
                putchar(' ');
            }
        } else {
            if(i > 20) {
                putchar('\b');
                putchar(' ');
                putchar('\b');
            }
            else if(letra == 10) {
                putchar('\r');
                break;
            }
            else {
                str[i] = letra;
                i++;
            }
        }
        letra = getchar();
    }
    str[i] = 0;
}

unsigned int atoi(char *str) {
    numero = 0;
    for(i = 0; str[i] != '\0'; i++) {
        if(str[i] < '0' || str[i] > '9') 
            break;
        numero = numero*10 + str[i] - '0';
    }
    return numero;
}

void itoa(char *str, unsigned int number, unsigned char base) {
    i = 0;
    j = 0;
    do {
        residuo = number%base;
        pila[i] = residuo + '0';
        if(pila[i] > '9')
            pila[i] = pila[i] + 7;
        number = number/(int)base;
        i++;
    } while(number != 0);
    i--;
    do {
        str[j] = pila[i];
        j++;
        i--;
    } while(i >= 0);
    str[j] = '\0';
}
