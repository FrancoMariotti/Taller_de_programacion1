/*
    Escriba las siguientes definiciones/declaraciones:

    a) Definicion de una funcion SUMA, que tome dos enteros largos  con signo 
    y devuelva  su suma.Esta funcion solo debe ser visible  en el modulo donde 
    se la define.

    b) Declaracion de un puntero  a un puntero a entero sin signo.

    c) Definicion de un caracter  solamente visible  en el modulo donde se define.
*/

// a)

static long SUMA(long a,long b) {
    return a + b;
}

// b)

unsigned int *(*i);

// c)

static char g = 'g';