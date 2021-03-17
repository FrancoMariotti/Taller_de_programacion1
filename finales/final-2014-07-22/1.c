/*

*/
#include <stdio.h>
#include <stdlib.h>

#define TERMINOS_SIZE 3
#define C 1
#define N 2
#define N_1 1
#define N_2 0

int calcular_termino(int n_1,int n_2) {
	return (3 * n_2 + 2 * n_1);
}

int main(int argc, char* argv[]) {
	
	int n = atoi(argv[1]);
	int k = atoi(argv[2]);

	int serie[TERMINOS_SIZE];

	serie[N_2] = C;
	serie[N_1] = C;

	for (int i = 2; i < n; i++) {
		serie[N] = calcular_termino(serie[N_1],serie[N_2]);
		serie[N_2] = serie[N_1];
		serie[N_1] = serie[N];
	}

	printf("Serie:");

	for (int i = n; i < n+k ; i++) {
		if (i < 2) {
			serie[N] = C;
		} else {
			serie[N] = calcular_termino(serie[N_1],serie[N_2]);
			serie[N_2] = serie[N_1];
			serie[N_1] = serie[N];
		}

		printf("%d ", serie[N]);
	}

	printf("\n");

	return 0;
}
