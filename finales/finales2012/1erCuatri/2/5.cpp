#include <iostream>
#include <list>

template < typename T >
std::istream& operator>>(std::istream& in, std::list<T>& ls) {
	int cantidad; 
    in >>std::hex >> cantidad;

    for (int i=0; i<cantidad; i++) {
    	T elemento;
    	in >> elemento;
    	ls.push_back(elemento);
    }
    return in;
}

template < typename T >
std::list<T> operator-(const std::list<T>& l1,const std::list<T>& l2) {
	std::list<T> result;
	
	typename std::list<T>::const_iterator it;

	bool add;
	for (it = l1.begin(); it != l1.end(); it++) {
		typename std::list<T>::const_iterator it2;
		add = true;

		for (it2 = l2.begin(); it2 != l2.end(); it2++) {
			if (*it == *it2) {
				add = false;
			}
		}

		if (add) {
			result.push_back(*it);
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
	
	std::list<int>::iterator it = l1.begin();

	for (; it != l1.end(); it++) {
		std::cout << "elemento:" << *it << std::endl;
	}
	

	l2.push_back(1);
	l2.push_back(4);
	l2.push_back(-1);

	std::list<int> result = l1-l2;

	std::list<int>::iterator itRes = result.begin();
	
	std::cout << "Elementos de l1 que no estan en l2" << std::endl;
	for (; itRes != result.end(); itRes++) {
		std::cout << "elemento:" << *itRes << std::endl;
	}
	

	return 0;
}
