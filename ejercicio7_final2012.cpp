#include "iostream"
#include "string"

class MiClase
{
private:
    float elemento;
public:
    MiClase();
    MiClase(float elemento);
    MiClase(std::string elemento);
    bool operator>(const MiClase& param) const;
    friend std::ostream& operator<<(std::ostream& out,const MiClase& param);
    ~MiClase();
};

MiClase::MiClase() {
    this->elemento = 0;
}

MiClase::MiClase(float elemento) {
    this->elemento = elemento;
}

MiClase::MiClase(std::string elemento) {
    this->elemento = std::stof(elemento);
}

bool MiClase::operator>(const MiClase& param) const {
    return this->elemento > param.elemento;
}

std::ostream& operator<<(std::ostream& out,const MiClase& param) {
    out << "elemento:" << param.elemento << std::endl;
    return out;
}

MiClase::~MiClase() = default;


int main(int argc, char const *argv[]) {
    MiClase C[2];

    C[1] = (C[0] > C[1]) ? MiClase(7.3) : MiClase("7.2");
    
    std::cout << "C[1]:" << C[1] << std::endl;
    return 0;
}
