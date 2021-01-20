/*	Escribir un programa en c no recursivo que reciba una cantidad(entero) por linea de comandos. 
	El programa debe imprimir cantidad terminos de una serie elementos en la cual los primeros 3 
	elementos son 1 y los siguientes se calculan como la suma de los 3 terminos anteriores.
*/

#include "stdio.h"
#include "stdlib.h"

#define TERMINO_INICIAL 1

int main(int argc, char** const argv) {
	int cantidad = atoi(argv[1]);
	int serie[cantidad]; 

	printf("Serie: ");
	for(int i=0 ; i<cantidad ; i++) {
		if(i < 3) {
			printf("%d,", TERMINO_INICIAL);
			serie[i] = TERMINO_INICIAL;
		} else {
			serie[i] = serie[i-3] + serie[i-2] + serie[i-1]; 
			printf("%d,", serie[i]);
		}
	}

	printf("\n");
}
