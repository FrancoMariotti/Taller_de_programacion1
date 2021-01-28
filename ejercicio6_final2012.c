/* Escribir un aplicacion C que modifique el archivo a.bin triplicando (repitiendo 3 veces) los bytes mayores a 0xD1.
*/

#include <stdlib.h>
#include <sys/types.h>


#define FILENAME "a.bin"
#define MAX_BYTE 0xD1

int main(int argc, char const *argv[]) {
    FILE* frd = fopen(FILENAME,"rb");
    FILE* fwr = fopen(FILENAME,"r+b");

    fseek(fwr,0,SEEK_END);
    int len = ftell(fwr);
    char c=0;

    for (int i = 0; i < len; i++) {
    	c = fgetc(frd);

    	if (c > MAX_BYTE) {
    		fwrite(&c,sizeof(char),3,fwr);
    	} else {
    		putc(c,wr);
    	}
    }

    fseek(fwr,0,SEEK_SET);

    while (c!=EOF) {
    	c = fgetc(frd);
    	putc(c,fwr); 
    } 

    ftruncate(fileno(fwr),ftell(fwr));

    fclose(frd);
    fclose(fwr);
    return 0;
}
