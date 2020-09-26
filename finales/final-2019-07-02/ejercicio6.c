#include "stdio.h"
#include "string.h"
#include "stdbool.h"

#define TAMANIO_BUFFER 1024
#define ESPACIO ' '
#define FIN_CADENA '\0'

bool ocurrencia(const char* cadenaA,const char* cadenaB,int lenCadenaB);
int copiar_palabra(char* buffer,const char* cadena,int lenCadena);

int main(int argc, char const *argv[]) {
    printf("/**Inicio programa reemplazo**/\n");
    const char* cadenaA = argv[1];
    const char* cadenaB = argv[2];
    size_t lenCadenaA = strlen(cadenaA);
    size_t lenCadenaB = strlen(cadenaB);

    int i_a = 0;
    int i_b = 0;

    char buffer[TAMANIO_BUFFER];
    memset(buffer,0,TAMANIO_BUFFER);

    while(i_a < lenCadenaA) {
        int cantidad = 0;
        cantidad = copiar_palabra(buffer + i_b,cadenaA + i_a,lenCadenaA - i_a);
        i_b += cantidad;

        if(ocurrencia(cadenaA + i_a,cadenaB,lenCadenaB)) {
            copiar_palabra(buffer + i_b,cadenaA + i_a,lenCadenaA - i_a);
            i_b += cantidad;
        }
        
        i_a += cantidad;
    }

    printf("Cadena:%s\n",buffer);

    return 0;
}

bool ocurrencia(const char* cadenaA,const char* cadenaB,int lenCadenaB) {
    if(cadenaA[lenCadenaB] != ESPACIO && cadenaA[lenCadenaB] != FIN_CADENA) {
        return false;
    }

    for (size_t i = 0; i < lenCadenaB; i++) {
        if(cadenaA[i] != cadenaB[i]) {
            return false;
        }

    }
    
    return true;
}


int copiar_palabra(char* buffer,const char* cadena,int lenCadena) {
    int contador = 0;
	for(int i = 0; i< lenCadena; i++) {
		buffer[i] = cadena[i];	
        contador +=1;
		if(cadena[i] == ESPACIO) break;
	}

    return contador;
}