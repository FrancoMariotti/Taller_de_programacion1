/*
 * Escriba un programa C que tome 3 cadenas por línea de comandos: A, B y C;
 * e imprima la cadena A después de haber reemplazado todas las ocurrencias de B por C.
 * ej.: reemp.exe “El ejercicio está mal hecho” mal bien -----> El ejercicio está bien hecho
 */

//Compilo: >>> gcc 2.c -lm -o 2
//Ejecuto: >>> ./2 "Está mal hecho" mal bien

#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

enum estados_t {INICIO_PALABRA,COPIAR_A,COPIAR_C,FIN_CADENA};

bool empieza_con_B(char* cadA,char* cadB,int lenB) {
	for (int j = 0; j < lenB; ++j) {
		if (cadA[j] == '\0' || cadA[j] != cadB[j]) {
			return false;
		}
	}

	return true;
}

int cantidad_ocurrencias(char* cadA,int lenA,char* cadB,int lenB) {
	int ocurrencias = 0;

	for (int i = 0; i < lenA; ++i) {
		if(cadA[i] == cadB[0]) {
			if(empieza_con_B(cadA+i,cadB,lenB)) {
				ocurrencias ++;
			}
		}
	}

	return ocurrencias;
}

int main(int argc, char *argv[]) {

	char* cadA = argv[1];
	char* cadB = argv[2];
	char* cadC = argv[3];

	int lenA = strlen(cadA);
	int lenB = strlen(cadB);
	int lenC = strlen(cadC);

	int ocurrencias = cantidad_ocurrencias(cadA,lenA,cadB,lenB);
	int size_result = lenA + (lenC - lenB) * ocurrencias; 

	char* resultado = (char*)malloc(sizeof(char)* ocurrencias);

	if (!resultado) {
		exit(EXIT_FAILURE);
	}

	int idxA = 0;
	int idxResult = 0;
	int estado = INICIO_PALABRA;

	while(estado != FIN_CADENA) {
		if(idxResult >= size_result) {
			estado = FIN_CADENA;
		} else if (estado == INICIO_PALABRA) {
			estado = COPIAR_A;
			if (empieza_con_B(cadA+idxA,cadB,lenB)) {
				estado = COPIAR_C;
			}
		} else if(estado == COPIAR_A) {
			resultado[idxResult] = cadA[idxA];
			if (cadA[idxA] == ' ') {
				estado = INICIO_PALABRA;
			} 
			idxA ++;
			idxResult ++;
		} else if(estado == COPIAR_C) {
			memcpy(resultado+idxResult,cadC,lenC);
			idxA += lenB;
			idxResult += lenC;
			estado = INICIO_PALABRA;
		} 

	}

	printf("cadenaA:%s\n", cadA);
	printf("cadenaB:%s\n", cadB);
	printf("cadenaC:%s\n", cadC);
	printf("resultado:%s\n", resultado);

	free(resultado);

	return 0;
}
