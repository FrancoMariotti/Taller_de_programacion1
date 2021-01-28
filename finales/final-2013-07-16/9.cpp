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

	//Seteo un titulo a la ventana.
	this->set_title("Ejemplo button");
	//Seteo un tamanio de ventana.
	this->set_default_size(200,200);

	// asocio la funcion on_button_clicked con la senial "clicked" del boton
	button.signal_clicked().connect(sigc::mem_fun(*this,&FooWindow::on_button_clicked));

	add(button);
	//Mostramos el botón que contiene la ventana
	show_all_children();
}

FooWindow::~FooWindow() {}
 
// Función 'callback' para atender la señal "clicked" del botón
void FooWindow::on_button_clicked() {
	std::cout << "Saliendo de la aplicacion" << std::endl;
	//salimos del loop de eventos
	Gtk::Main::quit();
}

int main(int argc,char*argv[]) {
	//Inicializamos el framework
	Gtk::Main kit(argc,argv);
	FooWindow window;

	//Inicia el loop de eventos
	Gtk::Main::run(window);

	return 0;
}