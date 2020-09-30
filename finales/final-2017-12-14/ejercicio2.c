/*
    Escribir un programa C que procese el archivo “numeros.txt” sobre sí mismo (sin crear archivos in-
    termedios y sin subir el archivo a memoria). El procesamiento consiste en leer grupos de 5 digitos y
    reemplazarlos por 4 caracteres hexadecimales que representen el mismo número leído pero en hexadec-
    imal.
*/

#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include <unistd.h>
#include <sys/types.h>

#define FILENAME "numeros.txt"
#define DIGITOS_NUMERO 5

int truncate(const char *path, off_t length);

size_t leerNumero(char*buffer,FILE* reader) {
    size_t leido = 0;
    char caracter = 0;
    int contador = 0;

    while(caracter != EOF && contador < DIGITOS_NUMERO) {
        caracter = fgetc(reader);
        if(caracter != '\n') {
            buffer[contador] = caracter;
            contador ++;
            leido ++;
        }
    }

    return leido;
}


void escribirRepresentacionEnHexa(char* buffer,FILE* writer) {
    int numero = atoi(buffer);
    char hexa[DIGITOS_NUMERO];
    snprintf(hexa, DIGITOS_NUMERO, "%x", numero);
    fwrite(hexa,sizeof(char),DIGITOS_NUMERO -1 , writer);
}

int main(int argc, char const *argv[]) {
    size_t leido = 0;
    size_t total = 0;
    char buffer[DIGITOS_NUMERO + 1];
    memset(buffer,0,DIGITOS_NUMERO);

    FILE* fdr = fopen(FILENAME,"r");
    FILE* fdw = fopen(FILENAME,"r+");

    while (1) {
        leido = leerNumero(buffer,fdr);
        if(leido < DIGITOS_NUMERO)
            break;
        escribirRepresentacionEnHexa(buffer,fdw);
        total += leido - 1;
    }
    
    fclose(fdr);
    fclose(fdw);
    truncate(FILENAME,total*sizeof(char));
    return 0;
}
