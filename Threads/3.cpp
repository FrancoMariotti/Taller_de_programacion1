/*
 * Escriba un ejemplo en el cual un thread genere los nros. de la serie de fibonacci
 * a razón de 1 cada 2 segundos; y otro thread del mismo proceso los imprima al
 * mismo ritmo. Ambos threads deben coordinar el acceso a la memoria y deben correr
 * sincronizados de forma que la serie se imprima correctamente.
 */

#include <mutex>
#include <thread>


std::mutex m;
int s[3];
bool imprimir;

void imprimir() {
	while(true) {
		if(imprimir) {
			std::lock_guard lock(m);
			std::cout << s[2] << std::endl;
			imprimir = false;
		}	
	}
}

void fibonacci() {
	while(true) {
		if(!imprimir) {
			std::lock_guard lock(m);
			s[2] = s[1] + s[0];
			s[0] = s[1];
			s[1] = s[2];
			imprimir = true;
			sleep(2);
		}	
	}
}

int main(int argc,char* argv[]) {
	s[0] = 1;
	s[1] = 1;
	imprimir = false;

	std::thread th1(imprimir);
	std::thread th2(fibonacci);

	th1.join();
	th2.join();

	return 0;
}