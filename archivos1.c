/*Escribir un programa C que procese el archivo texto.txt sobre sí mismo.
El proceso consiste en triplicar las palabras que tengan todas las vocales.*/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>


#define FILENAME "texto.txt"
#define CARACTER 'x'
#define FACTOR 2
#define SIZE_VOCALES 5
#define ESPACIO ' '
#define NUEVA_LINEA '\n'
#define TRIPLICAR 3

bool es_delimitador(const char c) {
	return (c == ESPACIO || c == NUEVA_LINEA || c == EOF);
}

bool tiene_vocales(const char* palabra) {
	char vocales[] = {'a','e','i','o','u'};
	bool tiene_vocal;
	for (int i = 0; i < SIZE_VOCALES; ++i) {
		tiene_vocal = false;
		for (int j = 0; j < strlen(palabra); j++) {
			if (palabra[j] == vocales[i]) {
				tiene_vocal = true;
			}
		}	

		if(!tiene_vocal) return false;
	}
	return true;
}

void triplicar_palabras(FILE* reader,FILE* writer,int reader_pos) {
	fseek(writer, 0, SEEK_END);
	int writer_pos = ftell(writer);
	bool finalizar = false;
	char c = 0;
	int len_palabra = 0;

	while (!finalizar) {

		while(!es_delimitador(c) && reader_pos >= 0) {
			if (reader_pos-1 < 0) {
				break;
			}
			fseek(reader,-1,SEEK_CUR);
			c = fgetc(reader);
		 	len_palabra ++;
		 	reader_pos --;
		 	fseek(reader,-1,SEEK_CUR);
		}
		
		if (len_palabra > 0) {
			char palabra[len_palabra+1];
			memset(palabra,0,len_palabra+1);
			fread(palabra,sizeof(char),len_palabra,reader);
			fseek(reader,-len_palabra,SEEK_CUR);

			int veces = (tiene_vocales(palabra)) ? TRIPLICAR : 1;
			int len = veces*len_palabra;
			writer_pos -= len;

			fseek(writer,writer_pos,SEEK_SET);
			for (int i = 0; i < veces; i++) {
				fwrite(palabra,sizeof(char),len_palabra,writer);
			}
		}

		finalizar = (reader_pos == 0);
		len_palabra = 0;
		c = 0;
	}
}

int resize_file(FILE* reader,FILE* writer) {
	int len_palabra = 0;
	int size_agregado = 0;
	int pos = 0;

	while(!feof(reader)) {
		len_palabra = 0;
		pos = ftell(reader);

		while(!es_delimitador(fgetc(reader))) {
		 	len_palabra ++;
		}

		if (len_palabra > 0) {
			char palabra[len_palabra+1];
			memset(palabra,0,len_palabra+1);

			fseek(reader, pos , SEEK_SET);
			fread(palabra,sizeof(char),len_palabra,reader);

			if(tiene_vocales(palabra)) {
				size_agregado += (len_palabra + 1) * FACTOR;
			}
		}
	}

	pos = ftell(reader);

	fseek(writer,0,SEEK_END);

	for (int i = 0; i < size_agregado; i++) {
		putc(CARACTER,writer);
	}

	return pos;
}

int main(int argc, char* argv[]) {
	FILE* frd = fopen(FILENAME,"r");
	FILE* fwr = fopen(FILENAME,"r+");

	int old_len = resize_file(frd,fwr);
	triplicar_palabras(frd,fwr,old_len);
	fclose(frd);
	fclose(fwr);
	return 0;
}
