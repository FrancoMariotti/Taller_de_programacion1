/*
    Escribir un programa ISO C que reciba por argumento el nombre de un archivo de texto y lo
    procese sobre sí mismo (sin crear archivos intermedios ni subiendo todo su contenido a
    memoria). El procesamiento consiste en eliminar las líneas de 1 sola palabra.
*/

#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "stdbool.h"
#include <unistd.h>
#include <sys/types.h>


#define STATE_LEER 0
#define STATE_FIN_PALABRA 1
#define STATE_FIN_LINEA 2
#define STATE_ESCRIBIR 3
#define STATE_FINISHED 4
#define DELIMITADORES " \n"

int truncate(const char *path, off_t length);
int ftruncate(int fd, off_t length);

int main(int argc, char const *argv[]) {
    printf("Nombre de archivo: %s\n",argv[1]);

    FILE* fdr = fopen(argv[1],"r");
    FILE* fdw = fopen(argv[1],"r+");
    
    int words = 0;
    size_t tamanio_final = 0;
    size_t contador = 0;
    bool reposicionar = false;
    char caracter = 0;
    int state = STATE_LEER;

    while (state != STATE_FINISHED) {
        switch (state) {
            case STATE_LEER: ;
                caracter = fgetc(fdr);
                ++ contador;
                if (caracter == EOF) {
                    state = STATE_FINISHED;
                } else if (strchr(DELIMITADORES,caracter)) {                
                    ++ words;
                    if(caracter == '\n') {
                        state = STATE_FIN_LINEA;
                    }
                }
                break;
            case STATE_FIN_LINEA: ;
                int proximoState = STATE_LEER;
                if(words > 1) {
                    tamanio_final += contador;
                    if (reposicionar) {
                        proximoState = STATE_ESCRIBIR;
                    } else {
                        fseek(fdw,ftell(fdr),SEEK_SET);
                    }
                } else {
                    reposicionar = true;                    
                }

                if(proximoState == STATE_LEER) {
                    contador = 0;
                }

                state = proximoState;
                words = 0;
                break;
            case STATE_ESCRIBIR: ;
                fseek(fdr,-contador,SEEK_CUR);
                for(int i = 0; i< contador; i++) {
                    fputc(fgetc(fdr),fdw);
                }
                state = STATE_LEER;
                break;
                
        }
    }

    fclose(fdr);
    fclose(fdw);

    truncate(argv[1],sizeof(char) * tamanio_final);
    return 0;
}
