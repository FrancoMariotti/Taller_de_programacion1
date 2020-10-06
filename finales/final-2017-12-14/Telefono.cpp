#include "Telefono.h"

std::istream& operator>>(std::istream& is,Telefono& other) {
    is >> other.telefono;

    return is;
}


Telefono::Telefono(int area,int numero) {

}