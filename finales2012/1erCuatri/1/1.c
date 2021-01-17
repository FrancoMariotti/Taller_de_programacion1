/* Escribir un algoritmo que procese el archivo 1.dat invirtiendo los bytes xy por yx */
#include "stdio.h"

#define FILENAME "1.dat"
#define INVERTIDA "yx"

int encontrar_secuencia(FILE* reader,FILE* writer,char* actual,char* siguiente) {
	*siguiente = fgetc(reader);
	if (*actual == 'x' && *siguiente == 'y') {	
		return 1;	
	}

	fputc(*actual,writer); //adelanto puntero de escritura.
	*actual = *siguiente; //actual toma valor de siguiente.
	
	return 0;
}

void invertir_secuencia(FILE* reader,FILE* writer,char* actual) {
	fputc('y',writer);
	fputc('x',writer);
	
	//adelanto actual al proximo valor de siguiente.
	*actual = fgetc(reader); 
}

int main(int argc, char const *argv[]) {
	/* code */
	FILE* reader;
	FILE* writer;

	reader = fopen(FILENAME,"rb");
	writer = fopen(FILENAME,"rb+");

	char actual = fgetc(reader);
	char siguiente;
	while(!feof(reader)) {
		if(encontrar_secuencia(reader,writer,&actual,&siguiente)) {
			invertir_secuencia(reader,writer,&actual);
		}
	}

	fclose(reader);
	fclose(writer);

	return 0;
}
