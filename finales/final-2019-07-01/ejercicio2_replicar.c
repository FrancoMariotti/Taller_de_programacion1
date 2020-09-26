#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//ejercicio2
//Escriba una funcion ISO C llamada replicar que reciba una cadena(s), dos indices y una cantidad.
//La funcion debe devolver una copia de S salvo los caracteres q se encuentran entre los indices 
//I1 e I2 que seran duplicados Q veces, siendo Q la cantidad.
//Ej: replicar("Hola",1,2,3) ->  "Hololola"

char* replicar(char* cadena,int indice1,int indice2,int cantidad);

int main(int argc, char const *argv[]) {
	char cadena[] = "Hola";
	
	char* replica = replicar(cadena,1,2,3);

	/* code */
	printf("Cadena Original:%s\n", cadena);
	printf("Replica:%s\n",replica);

	free(replica);
	return 0;
}

char* replicar(char* cadena,int indice1,int indice2,int cantidad) {
	int longitud_cadena = strlen(cadena);
	int cantidad_caracteres_a_copiar = indice2 - indice1 + 1;
	int longitud_copia_cadena = longitud_cadena + 1;
	longitud_copia_cadena += cantidad_caracteres_a_copiar * (cantidad - 1);

	int indice_final_cadena = 0;
	char* copia_cadena = (char*) malloc(longitud_copia_cadena);
	memset(copia_cadena,0,longitud_copia_cadena);

	strncpy(copia_cadena,cadena,indice1);
	indice_final_cadena += indice1; 

	for (int i=0 ; i<cantidad ; i++) { 
		strncpy(copia_cadena+indice_final_cadena,cadena+indice1,indice2);
		indice_final_cadena += cantidad_caracteres_a_copiar;
	}

	strncpy(copia_cadena+indice_final_cadena,cadena+indice2+1,longitud_cadena-indice2);
	
	return copia_cadena;
}