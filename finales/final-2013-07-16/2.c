/* Escriba una aplicacion C que lea de la linea de comandos un numero 
 * y lo imprima en todas las bases entre 2 y 16.
 */

#include "stdio.h"
#include "stdlib.h"
#include "math.h"

#define BASE_DEC 10
#define BASE_OCT 8

// int to_decimal(int num,int base) {
// 	int i = 0;
// 	int resultado = 0;
// 	int resto = -1;

// 	while(resto != 0) {
// 		resto = num % BASE_DEC;
// 		num /= BASE_DEC;

// 		resultado += resto*pow(base,i);
// 		i++;  
// 	} 

// 	return resultado;
// }

int main(int argc, char* argv[]) {
	// int num_octal = atoi(argv[1]);
	int num_decimal =  atoi(argv[1]);
	// int base = atoi(argv[2]);
	// int num_decimal =  to_decimal(num_octal,BASE_OCT);

	int division;
	int longitud;
	
	for (int base = 2; base < 17; base++) { //loop para imprimir en bases de 2 a 16.
		division = num_decimal;
		longitud = 0;

		while(division != 0) {
			division /= base;
			longitud ++;
		}

		int digitos[longitud];

		division = num_decimal;
		for (int i = longitud-1; i >= 0; i--) {
			digitos[i] = division % base;
			division /= base;
		}


		for (int i = 0; i < longitud; ++i) {
			if (base > 10 ) {
				switch(digitos[i]) {
					case 10:
						printf("A");
						break;
					case 11:
						printf("B");
						break;
					case 12:
						printf("C");
						break;
					case 13:
						printf("D");
						break;
					case 14:
						printf("E");
						break;
					case 15:
						printf("F");
						break;
					default:
						printf("%d",digitos[i]);
						break;
				}
			} else {
				printf("%d",digitos[i]);
			}


		}

		printf("\n");
	}

	return 0;
}
