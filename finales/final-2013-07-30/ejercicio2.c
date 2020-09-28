#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "stdbool.h"

#define TAMANIO_BUFFER  600
#define NOMBRE_ARCHIVO  "numeros.txt"

int cambiarDeBase(int numero,int base) {
    int resultado = 0;
    int resto = 1;
    int division = 0;
    int modificador = 1;
    while(resto > 0) {
        division = numero / base;
        resto = numero % base;
        resultado += resto * modificador;
        numero = division;
        modificador *= 10;
    }

    resultado += division * modificador;

    return resultado;
}

bool dejar_de_leer(char caracter) {
    if(caracter == '\n' || caracter == ' ') 
        return true;
    return false;
}

int leerNumero(char* buffer,FILE* fdr) {
    char caracter = 0;
    int i_b = 0;
    while ((caracter = fgetc(fdr))!= EOF) {
        if(dejar_de_leer(caracter))
            break;
        buffer[i_b] = caracter;
        i_b+=1;
    }
    return i_b;
}

int main(int argc, char const *argv[]) {
    printf("Programa decimal a octal\n");

    int i_b = 0;
    char buffer[TAMANIO_BUFFER];
    memset(buffer,0,TAMANIO_BUFFER);

    FILE* fdr = fopen(NOMBRE_ARCHIVO,"r");
    FILE* fdw = fopen(NOMBRE_ARCHIVO,"r+");
    
    bool finalizar = false;

    while(!finalizar) {
        int cantidad = leerNumero(buffer,fdr);
        int numero_decimal = atoi(buffer);
        int numero_octal = cambiarDeBase(numero_decimal,8);
        i_b += cantidad;
        finalizar = true;
    }

    fclose(fdr);
    fclose(fdw);

    return 0;
}
