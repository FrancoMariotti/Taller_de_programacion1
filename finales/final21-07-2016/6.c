/*
	16 bits -> 2 bytes
*/

#include <stdio.h>
#include <stdlib.h>

#define ADDRESS_SIZE 32
#define SPACE " "

void print_address(unsigned int address) {
	char buffer[ADDRESS_SIZE];
	int i = 0;

	while (i < ADDRESS_SIZE) {
	    if (address & 1)
	        buffer[i] = '1';
	    else
	        buffer[i] = '0';

	    address >>= 1;
	    i++;
	}

	for (int i = ADDRESS_SIZE-1; i >= 0; --i) {
		printf("%c", buffer[i]);
	}
	printf(SPACE);
}

int main(int argc,char const* argv[]) {
	FILE* rfd = fopen(argv[1],"r");
	int nBytes = atoi(argv[2]);
	unsigned int address = atoi(argv[3]);


	fseek(rfd,address,SEEK_SET);

	char c = 0;
	int bytes = 0;
	int counter = 0;

	while (c != EOF && bytes < nBytes) {
		if (counter == 0) {
			print_address(address);
		}

		c = getc(rfd);

		printf("%c", c);
		
		bytes ++;
		counter ++;

		if(counter == 16) {
			address += 4;
			printf("\n");
			counter = 0;
		}

	}



	fclose(rfd);

	return 0;
}