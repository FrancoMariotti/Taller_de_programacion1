#include "stdio.h"

void print_foo(const int foo) {
	printf("foo:%d\n", foo);
}

// void print2_foo(const int foo) {
// 	foo = 3;
// 	printf("foo:%d\n", foo);
// }

void print3_foo(const int * foo ,const int *foo2) {
	foo = foo2; 
	printf("foo:%d\n", *foo);
}



int main(int argc, char const *argv[]) {
	int foo = 20;
	int foo2 = 3;

	print_foo(foo);
	print3_foo(&foo,&foo2);
	return 0;
}