#include <string>
#include <iostream>
#include <list>

#define SPACE " "

int vocales(const string& str) {
	std::list<std::string>::iterator it = str.begin();
	int vocales = 0;

	for (it; it != str.end() ; it++) {
		if (*it == 'A' || *it == 'E' || *it == 'I' || *it == 'O' || *it == 'U'
			|| *it == 'a' || *it == 'e' || *it == 'i' || *it == 'o' || *it == 'u') {
			vocales++;
		}
	}


	return vocales;
} 

bool cmp(const string& a,const string& b) {
	return vocales(a) > vocales(b);
}

int main(int argc,char* argv[]) {	
	std::string oracion(argv[1]);
	std::list<std::string> palabras;
	int indice = 0;
	bool terminar = false;

	while(!terminar) {
		size_t pos = oracion.find(SPACE,indice);

		if(pos != std::string::npos) { // si encontre un espacio.
			palabras.push_back(oracion.substr(indice,pos+1));
			indice = pos + 1; // para saltar el espacio.
		} else { //queda la palabra final.
			palabras.push_back(oracion.substr(indice));
			terminar = true;
		}

	}

	std::sort(palabras.begin(),palabras.end(),cmp);

	std::list<std::string>::iterator it = palabras.begin();

	for (it; it != palabras.end() ; it++) {
		std::cout << *it << std::endl; //imprimo las palabras en orden.
	}

	return 0;
}