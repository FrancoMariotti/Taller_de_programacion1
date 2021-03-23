/*
 * Escriba un ejemplo en el cual un thread incremente un contador global
 * entero de a una unidad; y otro thread del mismo proceso lo imprima. 
 * Ambos threads deben coordinar el acceso a la memoria y deben correr
 * sincronizados de forma que siempre se impriman los números 1,2,3,4..
 */

#include <iostream>
#include <mutex>

#define LIMITE 100

int contador;
std::mutex m;
bool imprimir;

void incrementar_contador() {
	while(contador < LIMITE && !imprimir) {
		std::lock_guard lock(m);
		contador++;
		imprimir = true;
		usleep(100);
	}
}

void imprimir_contador() {
	while(contador < LIMITE && imprimir) {
		std::lock_guard lock(m);
		std::cout << "contador:" << contador << std::endl;
		imprimir = false;
		usleep(100);
	}
}

int main(int argc,char* argv[]) {
	imprimir = false;
	contador = 0;
	std::thread th1(incrementar_contador);
	std::thread th2(imprimir_contador);

	th1.join();
	th2.join();

	return 0;
}