
template<typename T>
std::list<T> DobleSiNo(std::list<T> a,std::list<T> b) {
	typename std::list<T>::iterator it_a = a.begin();
	typename std::list<T>::iterator it_b = b.begin();

	std::list<T> result;

	bool encontrado = false;

	for(it_a;it_a != a.end(); it_a++) {
		for(it_b;it_b != a.end(); it_b++) {
			if(*it_a == *it_b) {
				encontrado = true;
			}
		}

		if(!encontrado) {
			result.push_back(*it_a);
			result.push_back(*it_a);
		}

		encontrado = false;
	}
}