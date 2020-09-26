#ifndef __NUMERO_H_
#define __NUMERO_H_

#include "iostream"
/*
Declare la clase Número para almacenar un número de 100 cifras decimales. Incluya: constructor default, constructor de copia, 
los operadores ``+``, ``++`` (posfijo), ``++`` (prefijo), ``>``, ``=``, ``<<`` (corrimiento de bits) y ``<<``(impresión). 
Implemente el operador ``<<``(impresión).
*/


class Numero {
private:
    int numero;
    friend std::ostream& operator<<(std::ostream& output,const Numero&);
public:
    Numero();
    Numero(const Numero&);
    Numero operator+(const Numero&);
    Numero operator=(const Numero&);//Por copia
    Numero& operator=(Numero&&);//Por movimiento
    Numero& operator++(); //pre-incremento
    Numero operator++(int); //post-incremento
    bool operator>(Numero&);
    short operator<<(int c);
    ~Numero();
};

#endif