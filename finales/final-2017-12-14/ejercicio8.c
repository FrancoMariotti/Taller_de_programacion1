/*
    Escriba un programa C que tome 2 cadenas por línea de comandos: A y B; e imprima la cadena A
    después de haber suprimido todas las ocurrencias de B.
    Ej: reemp.exe "El final no está aprobado" "no" ---> El final está aprobado
*/

#include "stdio.h"
#include "stdlib.h"
#include "string.h"

char* suprimir_ocurrencias(const char* cadenaA,const char* cadenaB) {
	if(!cadenaA || !cadenaB) return NULL;

	size_t lenCadenaA = strlen(cadenaA);
	size_t lenCadenaB = strlen(cadenaB);

	char* cadenaSinOcurrencias = (char*) malloc(sizeof(char) * (lenCadenaA + 1));
	if(!cadenaSinOcurrencias) return NULL;
	memset(cadenaSinOcurrencias,0,lenCadenaA + 1);
	
	int indiceAux = 0;
	char* ret = strstr(cadenaA,cadenaB);
	for (int i = 0; i < lenCadenaA; i++) {
		if (ret == (cadenaA + i)) {
			i += lenCadenaB;
			ret = strstr(cadenaA + i,cadenaB);
			continue;
		} 

		cadenaSinOcurrencias[indiceAux] = cadenaA[i];
		indiceAux ++;
	}

	return cadenaSinOcurrencias;
}

int main(int argc, char const *argv[]) {
	if(argc != 3) {
		fprintf(stderr, "cantidad de parametros incorrecta");
		return 1;
	}
	const char* cadenaA = argv[1];
	const char* cadenaB = argv[2];

	char *cadena = suprimir_ocurrencias(cadenaA,cadenaB);
	fprintf(stdout, "cadena A:%s\n", cadenaA);
	fprintf(stdout, "cadena B:%s\n", cadenaB);
	fprintf(stdout, "cadena sin ocurrencias:%s\n", cadena);
	free(cadena);
	return 0;
}