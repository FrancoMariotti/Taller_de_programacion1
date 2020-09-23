#include "iostream"
#include "vector"

class Persona
{
private:
    /* data */
    int edad;
    std::string nombre;
public:
    Persona(int edad,std::string nombre);
    Persona(const Persona& copiable) = default;
    void mostrar() const;
    ~Persona();
};

Persona::Persona(int edad,std::string nombre): edad(edad),nombre(nombre) {}

/*Persona::Persona(const Persona& copiable) {
    this->edad = copiable.edad;
    this->nombre = copiable.nombre;
}*/

void Persona::mostrar() const {
    std::cout << "Mi nombre es:" << nombre << std::endl;
    std::cout << "Mi edad es:" << edad << std::endl;
}

Persona::~Persona() { }


class Lista
{
private:
    /* data */
    std::vector<int> elementos;
    int *foo;
public:
    Lista();
    Lista(const Lista&) = delete;
    void agregar(int elemento);
    void mostrar();
    void cambiarFoo();
    ~Lista();
};

Lista::Lista() {
    foo = new int[5];
    foo[0] = 15;
}

void Lista::agregar(int elemento) {
    elementos.push_back(elemento);
}

void Lista::mostrar() {
    std::vector<int>::iterator it = elementos.begin();

    for (it; it != elementos.end(); it++) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    std::cout << "Foo[0]:" << this->foo[0] << std::endl;
}

void Lista::cambiarFoo() {
    this->foo[0] = 84;
}

Lista::~Lista(){}

int main(int argc, char const *argv[]) {
    Persona franco(23,"Franco");
    franco.mostrar();
    Persona clon = franco;
    clon.mostrar();

    Lista lista;

    lista.agregar(34);
    lista.agregar(67);

    lista.mostrar();

    //Lista lista2 = lista;
    //lista2.cambiarFoo();

    lista.agregar(84);
    lista.mostrar();
    //lista2.mostrar();

    return 0;
}
