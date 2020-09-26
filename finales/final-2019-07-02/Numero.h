/*Declare la clase Numero para encapsular una cadena numerica larga. Incluya al menos:
Constructor(unsigned long), Constructor default y Constructor move; Operador <<,(),=,long y ++(int).
Implemente el operador >>.*/

#ifndef __NUMERO_H__
#define __NUMERO_H__

#include "iostream"
#include "string"

using namespace std;

class Numero {
    private:
        unsigned long numero;
        friend ostream &operator<<( ostream &output, const Numero &num );
        friend istream &operator>>( istream  &input, Numero &num );
    public:
        Numero();
        Numero(unsigned long numero);
        Numero(Numero&& numero);
        const Numero& operator=(const Numero& numero);
        void operator()();
        Numero& operator=(Numero&& numero);
        Numero& operator++(); //pre-incremento
        Numero operator++(int);//post-incremento
        operator long() const;
        ~Numero() = default;
};

#endif
