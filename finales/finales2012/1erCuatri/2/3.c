/*	Escriba un programa en C que procese el archivo a.bin sobre si mismo. El procesamiento 
	consiste en imprimir y eliminar del archivo todas las secuencias del tipo 'ddxxxx' 
	siendo 'd' un digito y 'x' una letra mayuscula o minusucla.
*/
#include <stdio.h>
#include "stdlib.h"
#include <stdbool.h>
#include <ctype.h>
#include <unistd.h>
#include <sys/types.h>

#define LARGO_SECUENCIA 6
#define DIGITOS_SECUENCIA 2
#define CARACTERES_SECUENCIA 4

int truncate(const char *path, off_t length);

typedef enum{LEYENDO, PRIMER_DIGITO, ELIMINAR_SECUENCIA,ESCRIBIR} state;

bool es_digito(const int c);
bool es_caracter(const char c);


int main(int argc,char const ** argv) {
	char c = 0;

	FILE* rd = fopen(argv[1],"r");
	FILE* wr = fopen(argv[1],"r+");

	state estado = LEYENDO;
	int digitos;
	int caracteres;
	int bytes_totales;

	while(c != EOF) {
		switch(estado) {
			case LEYENDO:
				c = fgetc(rd);

				if (es_digito(c)) {
					digitos ++;
					estado = PRIMER_DIGITO;	
				} else if (c != EOF) {
					putc(c,wr);
					bytes_totales ++;
				}
				break;
			case PRIMER_DIGITO: ;
				for (int i = 0; i < LARGO_SECUENCIA-1; i++) {
					c = fgetc(rd);

					if (es_digito(c)) {
						digitos ++;
					} else if(es_caracter(c)) {
						caracteres ++;
					}
				}

				estado = ESCRIBIR;
				
				if(digitos == DIGITOS_SECUENCIA && caracteres == CARACTERES_SECUENCIA) {
					estado = ELIMINAR_SECUENCIA;
				}

				fseek(rd,-LARGO_SECUENCIA,SEEK_CUR);
				break;
			case ESCRIBIR: ;
				c = fgetc(rd);
				putc(c,wr); //avanzo puntero de escritura.

				caracteres = 0;
				digitos = 0;
				bytes_totales ++;	

				estado = LEYENDO;
				break;
			case ELIMINAR_SECUENCIA: ;

				for (int i = 0; i < LARGO_SECUENCIA; i++) {
					c = fgetc(rd);
					printf("%c", c);
				}
				printf("\n");

				caracteres = 0;
				digitos = 0;
				estado = LEYENDO;
				break;

		}
	}

	truncate(argv[1],sizeof(char)*bytes_totales);

	fclose(rd);
	fclose(wr);
}


bool es_digito(const int c) {
	return (c >= 48 && c <= 57);
}

bool es_caracter(const char c) {
	char cUpper = toupper(c);
	return (cUpper >= 65 && cUpper <= 90);
}

