#include <stdio.h>

#define divisor 10

int main(int argc,char *argv[]) {
	
	int dividendo = 50;

	#if divisor != 0 
		printf("%d\n", dividendo/divisor);
	#endif

	return 0;
}