/* Escriba una aplicacion ISO C++ que acepte una cadena (unico parametro) por linea 
 * de comandos e imprima las palabras de la oracion de mayor a menor cantidad de letras.
*/
#include <iostream>
#include <algorithm>
#include <string>
#include <vector>

#define DELIMITER " "

bool palabras_cmp(std::string str1,std::string str2) {
	return str1.length() > str2.length();
}

int main(int argc,char* argv[]) {
	std::string cadena(argv[1]);
	std::size_t pos = 0;
	std::vector<std::string> palabras;
	int comienzo = 0;
	std::string palabra;

	while (pos != std::string::npos) {
		pos = cadena.find(DELIMITER,comienzo);
		palabra = cadena.substr(comienzo,pos-comienzo);
		comienzo = pos + 1;
		palabras.push_back(palabra);
	}

	std::sort(palabras.begin(),palabras.end(),palabras_cmp);

	std::vector<std::string>::iterator it;

	for (it = palabras.begin(); it != palabras.end(); it++) {
		std::cout<< *it <<std::endl;
	}

	return 0;
}