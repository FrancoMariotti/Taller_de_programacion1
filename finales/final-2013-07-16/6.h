/* Declare una clase Complejo para encapsular un nro complejo.Incluya la menos:Contructor default,
 * Constructor con valores de inicializacion y Constructor copia; operador <,==,=,int(devuelve la 
 * parte real del numero encapsulado) y <<(impresion).
*/

class Complejo {
private:
	float real,imaginaria;
	friend std::ostream& operator<<(std::ostream& out,const Complejo& complejo);
public:
	Complejo();
	Complejo(float real=0,float imaginaria=0);
	Complejo(const Complejo& complejo);
	bool operator<(const Complejo& complejo) const;
	bool operator==(const Complejo& complejo) const;
	Complejo& operator=(const Complejo& complejo);
	operator int() const;
}

std::ostream& Complejo::operator<<(std::ostream& out,const Complejo& complejo) {
	out<< complejo.real << "+i" << complejo.imaginaria << std::endl;

	return out;
}