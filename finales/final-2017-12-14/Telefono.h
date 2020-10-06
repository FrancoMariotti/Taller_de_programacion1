#ifndef __TELEFONO_H_
#define __TELEFONO_H_

#include "iostream"
#include "string"

class Telefono
{
private:
    std::string telefono;
    friend std::ostream& operator<<(std::ostream& os,const Telefono& other);
    friend std::istream& operator>>(std::istream& is,Telefono& other);
public:
    Telefono();
    Telefono(int area,int numero);
    Telefono(const Telefono& other);
    Telefono& operator=(const Telefono& other);
    operator long() const;
    bool operator==(const Telefono& other);
    ~Telefono();
};
#endif