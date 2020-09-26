#include "Numero.h"


Numero::Numero(): numero(0) {}

istream &operator>>( istream  &input, Numero &num ) {
    input >> num.numero;
    return input;
}