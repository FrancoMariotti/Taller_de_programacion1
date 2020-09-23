#include "iostream"

using namespace std;


class Complejo {
    int real;
    int imaginaria;
    public:
        Complejo(int real,int imaginaria);
        Complejo operator+(const Complejo& complejo);
        friend ostream &operator<<( ostream &output, const Complejo &c );
        friend istream &operator>>( istream  &input, Complejo &c );
        ~Complejo();
};

Complejo::Complejo(int real,int imaginaria): real(real),imaginaria(imaginaria) { }

Complejo Complejo::operator+(const Complejo& complejo) {
    int x = this->real + complejo.real;
    int y = this->imaginaria + complejo.imaginaria;
    Complejo c(x,y);
    return c;
}

ostream &operator<<( ostream &output, const Complejo &c ) { 
    output << "X : " << c.real << " Y : " << c.imaginaria;
    return output;            
}

istream &operator>>( istream  &input, Complejo &c ) { 
    input >> c.real >> c.imaginaria;
    return input;            
}


Complejo::~Complejo() {}



int main(int argc, char const *argv[]) {
    Complejo c1(2,1);
    Complejo c2(3,1);

    Complejo c3 = c1 + c2;

    cout << "c1:" << c1 << endl;
    cout << "c2:" << c2 << endl;
    cout << "Suma de c1 y c2:" << c3 << endl;
    return 0;
}

