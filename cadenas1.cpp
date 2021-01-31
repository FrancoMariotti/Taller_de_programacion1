/* Escribir un programa que permita ingresar 3 cadenas desde STDIN e imprima la primera, 
 * reemplazando las ocurrencias de la segunda por la tercera.
*/

#include <iostream>
#include <string>

int main(int argc,char* argv[]) {
	std::string cadena1(argv[1]);
	std::string cadena2(argv[2]);
	std::string cadena3(argv[3]);

	bool terminar = false;

	std::cout << cadena1 << std::endl;


	while(!terminar) {
		size_t pos = cadena1.find(cadena2);
		terminar = (pos == std::string::npos);

		if(!terminar) {
			cadena1.replace(pos,cadena2.length(),cadena3);
		}
	}

	std::cout << cadena1 << std::endl;


	return 0;
}