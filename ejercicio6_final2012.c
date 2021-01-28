/* Escribir un aplicacion C que modifique el archivo a.bin triplicando (repitiendo 3 veces) los bytes mayores a 0xD1.
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>


#define FILENAME "a.bin"
#define MAX_BYTE 0xD1

int fileno(FILE* stream);
int ftruncate(int fd,off_t length);

int main(int argc, char const *argv[]) {
    FILE* frd = fopen(FILENAME,"rb");
    FILE* fwr = fopen(FILENAME,"r+b");

    fseek(fwr,0,SEEK_END);
    int len = ftell(fwr);
    int bytes = 0;
    unsigned char c=0;

    for (int i = 0; i < len; i++) {
    	c = fgetc(frd);

    	if (c > MAX_BYTE) {
		putc(c,fwr);
		putc(c,fwr);
		putc(c,fwr);
		bytes+=3;
    	} else {
    		putc(c,fwr);
    		bytes++;
    	}
    }

    fseek(fwr,0,SEEK_SET);

    for (int i = 0; i < bytes; i++) {
    	c = fgetc(frd);
    	putc(c,fwr);
    }

    ftruncate(fileno(fwr),ftell(fwr));

    fclose(frd);
    fclose(fwr);
    return 0;
}
