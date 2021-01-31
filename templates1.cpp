/* Definir la rutina PRIMERO_PRIMOS de forma que ordene los elementos recibidos de la siguiente manera: Primero los primos y luego el resto,
 * y dentro de * esa clasificación, por orden ascendente. Ejemplo: Si recibe los elementos 1,6,7,2,9,4,3 debe devolver 1,3,7,2,4,6,9
 * std:list<T> PRIMERO_PRIMOS(std:list<T> &Lista);
 * Nota: Asuma que el tipo T posee el operador < y el método bool EsDivisible(int Div).
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>

template <typename T>
std:list<T> primero_primos(std:list<T> &lista) {
	std::list<T> resto;
	std::list<T> primos;
	std::list<T> resultado;

	typename std::list<T>::iterator it = lista.begin();

	for(it; it!= lista.end(); it++) {
		if (it->EsDivisible(2)) {
			resto.push_back(*it);
		} else {
			primos.push_back(*it);
		}

	}

	//esto utiliza el operador <
	std::sort(primos.begin(),primos.end());
	std::sort(resto.begin(),resto.end());

	std::set_union(primos.begin(),primos.end(),
					resto.begin(),resto.end(), std::back_inserter(resultado));

	return resultado;
}

int main(int argc,char* argv[]) {
	std::std::vector<int> v1 {1,6,7,2,9,4,3};
	std::std::vector<int> v2;

	std::std::vector<int>::iterator it = v1.begin();

	std::cout << "v1={";
	for (it; it != v1.end(); it++) {
		std::cout << *it << " ";
	}

	std::cout<< "}" << std::endl;

	v2 = primero_primos(v1);

	it = v2.begin();

	std::cout << "v2={";
	for (it; it != v2.end(); it++) {
		std::cout << *it << " ";
	}

	std::cout<< "}" << std::endl;

	return 0;
}