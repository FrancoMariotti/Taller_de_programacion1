#include <iostream>
#include <list>

template < typename T >
std::istream& std::list<T>::operator<<(std::istream& in, std::list<T>& ls) {
	int cantidad; 
    in >> std::hex >>cantidad;

    for (int i=0; i<cantidad; i++) {
    	T elemento = 0;
    	in >> elemento;
    	ls.push_back(elemento);
    }
    return in;
}

template < typename T >
std::list<T> std::list<T>::operator-(const std::list<T>& lista) const {
	std::list<T>::iterator it = this->begin();
	std::list<T> result;
	
	for (it; it != this->end(); it++) {
		auto element = std::find(std::begin(lista), std::end(lista), *it);

		if (element == std::end(lista)) {
			result.push_back(element);
		}
	}

	return result;
}

int main(int argc, char const *argv[])
{
	std::list<int> l1;
	std::list<int> l2;

	std::cout << "Ingresar elementos de lista:" << std::endl;
	std::cin >> l1;


	l2.push_back(2);
	l2.push_back(5);
	l2.push_back(-1);

	std::list<int> result = l1-l2;

	std::list<int>::iterator it = result.begin();

	for (it; it != result.end(); it++) {
		std::cout << "elemento:" << *it << std::endl;
	}
	

	return 0;
}