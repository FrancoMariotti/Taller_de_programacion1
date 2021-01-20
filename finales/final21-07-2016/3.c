/* Escribir un programa que procese el archivo in.txt sobre si mismo. 
 * El proceso consiste en eliminar las palabras que tengan solo numeros.
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>

#define FILENAME "in.txt"
#define SEPARADORES " \n"


typedef enum{LEYENDO,ESCRIBIR,RESET} state;

int truncate(const char *path, off_t length);
bool es_digito(const int c);


int main(int argc, char* argv[]) {

	FILE* rd = fopen(FILENAME,"r");
	FILE* wr = fopen(FILENAME,"r+");


	state estado = LEYENDO;
	char c = 0;
	int digitos = 0;
	int caracteres_leidos = 0;
	int bytes_totales = 0;

	while (c != EOF) {

		switch(estado) {
			case LEYENDO:
				c = fgetc(rd);

				if(strstr(SEPARADORES,&c) || c == EOF) {
					if (caracteres_leidos != digitos) { //si la palabra leida no es un numero
						estado = ESCRIBIR;
					} else {
						estado = RESET;
					}

				} 
			
				if (es_digito(c)) {
					digitos ++;
				}
				caracteres_leidos ++;
				
				break;
			case ESCRIBIR: ;
				fseek(rd,-caracteres_leidos,SEEK_CUR);	//vuelvo al inicio de la palabra

				for (int i = 0; i < caracteres_leidos; i ++) {
					c = fgetc(rd);
					putc(c,wr); //adelanto puntero de escritura.
				}

				bytes_totales += caracteres_leidos;
				estado = RESET;
				break;

			case RESET: ;
				digitos = 0;
				caracteres_leidos = 0;
				estado = LEYENDO;
				break;	
		}



	}

	truncate(FILENAME,sizeof(char)*bytes_totales);

	fclose(rd);
	fclose(wr);

	return 0;
}

bool es_digito(const int c) {
	return (c >= 48 && c <= 57);
}