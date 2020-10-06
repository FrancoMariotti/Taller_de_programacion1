/*
    a) Declaración de un puntero a puntero a carácter
    b) Definición de una función RESTA que tome dos enteros largos con signo y devuelva su resta. Esta
        función sólo debe ser visible en el módulo donde se la define.
    c) Definición de un entero corto sin signo solamente visible en el módulo donde se la define.
*/

char ** a;

static long resta(long a,long b) {
    return a - b;
}

static unsigned short a = 1;