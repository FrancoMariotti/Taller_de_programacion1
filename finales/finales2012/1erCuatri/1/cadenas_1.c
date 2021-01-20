#include <stdio.h>

int saltear_ocurrencia(char* cadenaA,char* cadenaB) {
	int idx = 0;
	int count = 0;
	
	while(cadenaB[idx] != '\0') {
		if(cadenaB[idx] != cadenaA[idx] || cadenaA[idx] == '\0') {
			return 0;
		}

		idx ++;
		count ++;
	}

	return count;
}


int main(int argc, char *argv[]) {
	char* cadenaA = argv[1];
	char* cadenaB = argv[2];

	printf("Cadena A: %s\n", cadenaA);
    printf("Cadena B: %s\n", cadenaB);

	int idxRd = 0;
	int idxWr = 0;
	int salto = 0;

	while(cadenaA[idxRd] != '\0') {
		salto = saltear_ocurrencia(cadenaA + idxRd, cadenaB);

		if (salto > 0) {
			idxRd += salto;
		} else {
			cadenaA[idxWr] = cadenaA[idxRd];
			idxRd ++;
			idxWr ++;
		}

	} 

	cadenaA[idxWr] = '\0';

    printf("Salida  : %s\n", cadenaA);

	return 0;
}
