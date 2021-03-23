/*
 * Escriba un ejemplo en el cual un thread use un contador global entero y lo 
 * incremente de a una unidad; y otro thread del mismo proceso lo imprima y lo 
 * decremente. Ambos threads deben coordinar el acceso a la memoria y deben 
 * correr sincronizados de forma que siempre se impriman los números 1,0,1,0..
 */
#include <iostream>
#include <thread>
#include <mutex>

int contador;
std::mutex m;
bool imprimir;
bool incrementar;

void imprimir_contador() {
	while (true) {
		if (imprimir) {
			std::lock_guard lock(m);
			imprimir = false;
			incrementar = false;
		}
	}
}

void incrementar_contador() {
	while (true) {
		if (incrementar) {
			std::lock_guard lock(m);
			contador++;	
			imprimir = true;
		}
	}
}

void decrementar_contador() {
	while (true) {
		if (!incrementar) {
			std::lock_guard lock(m);
			contador--;
			incrementar = true;
		}
	}
}

int main(int argc, char* argv[]) {
	contador = 0;
	turno = 

	std::thread th1(imprimir_contador);
	std::thread th2(incrementar_contador);
	std::thread th3(decrementar_contador);

	th1.join();
	th2.join();
	th3.join();

	return 0;
}
