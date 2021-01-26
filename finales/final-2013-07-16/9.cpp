/* Esciba una aplicacion basica con interfaz grafica. El programa debe desplegar una vetana 
 * con un boton "Cerrar"(que haga terminar ordenadamente la aplicacion).Comente/Explique el programa.
*/
#include <iostream>
#include "gtkmm.h"

class FooWindow: public Gtk::Window {
public:
	FooWindow();
	virtual ~FooWindow();
protected:
	void on_button_clicked();
	Gtk::Button button;
};

FooWindow::FooWindow(): button("Cerrar") {
	this->set_title("Ejemplo button");
	this->set_default_size(200,200);

	button.signal_clicked().connect(sigc::mem_fun(*this,&FooWindow::on_button_clicked));

	add(button);
	show_all_children();
}

FooWindow::~FooWindow() {}

void FooWindow::on_button_clicked() {
	std::cout << "Saliendo de la aplicacion" << std::endl;
	Gtk::Main::quit();
}

int main(int argc,char*argv[]) {
	Gtk::Main kit(argc,argv);
	FooWindow window;

	Gtk::Main::run(window);

	return 0;
}