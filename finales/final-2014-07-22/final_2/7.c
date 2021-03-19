/*	Escribir un programa ISO C que procese un archivo "x.txt" sobre si mismo. El proceso consiste en 
	reemplazar todas las secuencias "123" por "12".Cabe que debe volver a procesar el texto ya reemplazado.
	Es decir "1233" debe finalmente quedar como "12".
*/

#include "stdio.h"
#include "stdlib.h"
#include <unistd.h>
#include <sys/types.h>


#define FILENAME "x.txt"

int ftruncate(int fd, off_t length);

typedef enum{LEER,UNO,DOS,TRES,ESCRIBIR} estado_t; 

int main(int argc, char *argv[]) {
	FILE* fr = fopen(FILENAME,"r");
	FILE* fw = fopen(FILENAME,"r+");

	char c = 0;
	estado_t actual = LEER; 
	estado_t anterior = LEER; 


	while(c != EOF) {
		if(actual != ESCRIBIR) {
			c = getc(fr);
		}

		switch(actual) {
			case LEER:
				anterior = LEER;
				if (c == '1') {
					actual = UNO;
				} else  if (c != EOF){
					putc(c,fw); //avanzo puntero de escritura.
				}
			break;
			case UNO:
				anterior = UNO;
				actual = ESCRIBIR;

				if (c == '2') {
					actual = DOS;
				}
			break;
			case DOS:
				anterior = DOS;
				actual = ESCRIBIR;

				if (c == '3') {
					actual = TRES;
				} 
			break;
			case TRES:
				anterior = TRES;
				actual = ESCRIBIR;

				if (c == '3') {
					actual = TRES;
				}
			break;
			case ESCRIBIR:
				putc('1',fw);

				if (anterior == DOS || anterior == TRES) {
					putc('2',fw);
				}

				if(c == '1') {
					actual = UNO;
				} else {
					if(c != EOF) {
						putc(c,fw);
					}
					actual = LEER;
				}
				
			break;
		}
	}

	ftruncate(fileno(fw),ftell(fw));

	fclose(fr);
	fclose(fw);

	return 0; 
}
