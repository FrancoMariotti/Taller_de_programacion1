/*
    Escribir un programa ISO C que reciba por argumento el nombre de un archivo de texto y lo
    procese sobre sí mismo (sin crear archivos intermedios ni subiendo todo su contenido a
    memoria). El procesamiento consiste en eliminar las líneas de 1 sola palabra.
*/

#include "stdio.h"
#include "stdlib.h"
#include "string.h"

#define STATE_LEYENDO 0
#define STATE_FIN_PALABRA 1
#define STATE_NUEVA_LINEA 2
#define STATE_BORRAR 3
#define STATE_FINISHED 4
#define NUEVA_LINEA '\n'
#define ESPACIO ' '

int main(int argc, char const *argv[]) {
    printf("Nombre de archivo: %s\n",argv[1]);

    FILE* fdr = fopen(argv[1],"r");
    FILE* fdw = fopen(argv[1],"r+");
    char caracter = 0;
    int state = STATE_LEYENDO;
    int words = 0;

    while (state != STATE_FINISHED) {
        switch (state) {
            case STATE_LEYENDO: ;
                caracter = fgetc(fdr);
                if (caracter == EOF) {
                    state = STATE_FINISHED;
                } else if (caracter == NUEVA_LINEA || caracter == ESPACIO) {                
                    state = STATE_FIN_PALABRA;
                }
                break;
            case STATE_FIN_PALABRA:
                words += 1;
                if(caracter == NUEVA_LINEA) {
                    state = STATE_NUEVA_LINEA;
                } else {
                    state = STATE_LEYENDO;
                }
                break;
            case STATE_NUEVA_LINEA:
                if(words == 1) {
                    state = STATE_BORRAR;
                } else {
                    int corrimiento = ftell(fdr) - ftell(fdw);
                    fseek(fdw,corrimiento,SEEK_CUR);
                    state = STATE_LEYENDO;
                    words = 0;
                }
                break;
            case STATE_BORRAR: ;
                long int cantidadABorrar = ftell(fdr) - ftell(fdw) - 1;
                for (size_t i = 0; i < cantidadABorrar; i++) {
                    fputc(32,fdw);
                }
                fseek(fdw,1,SEEK_CUR);
                state = STATE_LEYENDO;
                break;
        }
    }

    fclose(fdr);
    fclose(fdw);
    return 0;
}
