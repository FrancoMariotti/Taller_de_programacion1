/* Escribir un programa en C que, sin crear arhivos intermedios, procese el archivo "enteros.dat". 
 * El procesamiento consiste en leer grupos de 2 enteros  sin signo de 32 bits desde el archivo y 
 * escribir, en su lugar, resta del grupo(es decir que el archivo se acortara). 
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <ctype.h>
#include <unistd.h>
#include <sys/types.h>

#define FILENAME "enteros.dat"

int truncate(const char*path, off_t length);

int main(int argc,char*argv[]) {
	FILE* frd = fopen(FILENAME,"rb");
	FILE* fwr = fopen(FILENAME,"r+b");

	int32_t numeros[2];
	int32_t resta = 0;
	int leidos = 0;
	bool terminar = false;

	while(!terminar) {
		leidos = fread(numeros,sizeof(int32_t),2,frd);
		if(leidos <= 0) {
			terminar = true;
		}

		if (!terminar) {
			resta = numeros[0] - numeros[1];
			fwrite(&resta,sizeof(int32_t),1,fwr);
		}
	}

	truncate(FILENAME,ftell(fwr));

	fclose(frd);
	fclose(fwr);

	return 0;
}