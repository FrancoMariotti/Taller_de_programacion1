#include "stdio.h"

#define HELLO_WORLD "Hola Mundo"

void printMensaje();

int main(int argc, char const *argv[]) {
    printMensaje();
    return 0;
}

void printMensaje() {
    #ifndef HELLO_WORLD
        printf("Hello world no definido\n");
    #else
        printf("%s\n",HELLO_WORLD);
    #endif
}