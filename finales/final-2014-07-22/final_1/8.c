/*	El archivo medidas.txt posee numeros menores a 250, expresados con 3 digitos en formato ASCII y sin separacion.
	Escriba una aplicacion C que modifique el archivo medidas.txt sobre si mismo convirtiendo  cada numero a formato  hexadecimal 
	de 2 caracteres ASCII.
*/

#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include <stdbool.h>
#include <unistd.h>
#include <sys/types.h>

#define FILENAME "medidas.txt"

int ftruncate(int fd, off_t length);

int main(int argc, char* argv[]) {
	FILE* fr = fopen(FILENAME,"r");
	FILE* fw = fopen(FILENAME,"r+");

	char buffer[4];

	while(fread(buffer,sizeof(char),3,fr) > 0) {
		printf("buff:%s\n",buffer);
		int num = atoi(buffer);
		printf("num:%d\n",num );
		memset(buffer,0,3);
		snprintf(buffer,3,"%02x",num);
		printf("num_s:%s\n",buffer );
		fwrite(buffer,sizeof(char),2,fw);
		memset(buffer,0,3);
	}
	printf("\n");

	ftruncate(fileno(fw),ftell(fw));

	fclose(fr);
	fclose(fw);

	return 0;
}
