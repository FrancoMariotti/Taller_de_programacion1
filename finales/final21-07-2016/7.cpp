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
	std::vector<std::string> palabras;

    	for(int i=1;i<argc;i++){
        	palabras.push_back(argv[i]);
    	}

	std::sort(palabras.begin(),palabras.end(),palabras_cmp);

	std::vector<std::string>::iterator it;

	for (it = palabras.begin(); it != palabras.end(); it++) {
		std::cout<< *it <<std::endl;
	}
	
	return 0;
}
