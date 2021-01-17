/*	Escriba un programa en C que procese el archivo a.bin sobre si mismo. El procesamiento 
	consiste en imprimir y eliminar del archivo todas las secuencias del tipo 'ddxxxx' 
	siendo 'd' un digito y 'x' una letra mayuscula o minusucla.
*/
#include <stdio.h>

#define SEPARADOR ","
#define DIGITOS_SECUENCIA 2
#define CARACTERES_SECUENCIA 4

typedef enum{READING, COPYING, FIRST_BAR, LAST_STAR} state;


int main(int argc,char const ** argv) {
	char c;

	FILE* rd = fopen(FILENAME,"r");
	FILE* wr = fopen(FILENAME,"w+");

	state estado_actual = COPYING;
	char c = 0;
	int digitos = 0;
	int caracteres = 0;

	while(c != EOF) {
		c = fgetc(rd);

		if (state = LEER) {
			if (es_digito(c)) {
				state = PRIMER_DIGITO;
				digitos++;
			} else {
				putc(c,wr); //avanzo puntero de escritura.
			}

		} else if (state = PRIMER_DIGITO) {
			if (es_digito(c)) {
				digitos++;
			} else {
				if(es_caracter(c) && digitos = DIGITOS_SECUENCIA) {
					state = PRIMER_CARACTER;
					caracteres++;
				} else {
					state = ESCRIBIR;
				}
			}
		} else if (state = PRIMER_CARACTER) {
			if (es_caracter(c)) {
				caracteres++;

				if(caracteres = CARACTERES) {
					state = IMPRIMIR_SECUENCIA;
				}
			} else {
				state = ESCRIBIR;
			}
		} else if (state = IMPRIMIR_SECUENCIA) {
			
		} else if(state = COPIAR) {
			if(!encontre_secuencia) {
				putc(c,wr); 
			}
		}
	}

	fclose(rd);
	fclose(wr);
}


