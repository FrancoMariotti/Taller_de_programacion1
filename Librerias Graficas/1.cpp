/* Escriba una rutina(para ambiente grafico windows o linux) que dibuje la siguiente imagen en su area de dibujo.
 * Un triangulo relleno en negro con las coordenadas (EsquinaInferiorIzquierda,esquinaInferiorDerecha,esquinaSuperiorDerecha)
*/
#include "gtkmm/drawingarea.h"
#include "gtkmm/window.h"
#include "gtkmm/main.h"
#include "cairomm/context.h"

class Triangulo : public Gtk::DrawingArea {
	public:
		Triangulo();
		~Triangulo();
	protected:
		//override signal handler.
		virtual bool on_expose_event(GdkEventExpose* event);
};

Triangulo::Triangulo() {};
Triangulo::~Triangulo() {};

//override signal handler.
bool Triangulo::on_expose_event(GdkEventExpose * event) {
	Glib::RefPtr<Gdk::Window> window = get_window();

	if (window) {
		Gtk::Allocation allocation = get_allocation();
		const int wHeight = allocation.get_height();
		const int wWidth = allocation.get_width();

		Cairo::RefPtr<Cairo::Context> context = window->create_cairo_context();	
		
		context->rectangle(event->area.x,event->area.y,
						event->area.width,event->area.height);
		context->set_source_rgb(1.0,1.0,1.0);
		context->fill();

		context->set_source_rgb(0.0,0.0,0.0);
		context->set_line_width(5.0);
		
		//Esquina inferior Izquierda
		context->move_to(0,wHeight);
		//Esquina superior Derecha
		context->line_to(wWidth,0);
		//Esquina inferior Derecha
		context->line_to(wWidth,wHeight);
		//Esquina inferior Izquierda			
		context->line_to(0,wHeight);

		context->fill();
	}

	return true;
}



int main(int argc,char * argv[]) {
	Gtk::Main kit(argc,argv);
	Gtk::Window win;

	win.set_title("Hola mundo");

	Triangulo tr;
	win.add(tr);
	tr.show();
	//Processing main loop.
	Gtk::Main::run(win);

	return 0;
}