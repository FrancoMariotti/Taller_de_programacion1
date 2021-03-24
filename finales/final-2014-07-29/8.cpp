/*Escriba una rutina que dibuje una cruz diagonal ocupando toda la pantalla. */

#include "gtkmm.h"


class CruzDiagonal: public Gtk::DrawingArea {
public:
	CruzDiagonal();
	~CruzDiagonal();
protected:
	virtual bool on_expose_event(GdkEventExpose *event);
};

CruzDiagonal::CruzDiagonal() {};
CruzDiagonal::~CruzDiagonal() {};

bool CruzDiagonal::on_expose_event(GdkEventExpose *event) {
	Glib::RefPtr<Gdk::Window> window = get_window();

	if (window) {
		Gtk::Allocation alloc = get_allocation();
		int height = alloc.get_height();
		int width = alloc.get_width();

		Cairo::RefPtr<Cairo::Context> context = window->create_cairo_context();
		context->scale(height,width);
		context->rectangle(0.0,0.0,1.0,1.0);
		context->set_source_rgb(1.0,1.0,1.0);
		context->fill();



		context->set_source_rgb(1.0,0.0,0.0);
		context->set_line_width(0.1);
		context->move_to(0,0);
		context->line_to(1.0,1.0);
		context->move_to(0.0,1.0);
		context->line_to(1.0,0.0);
		context->stroke();
	}

	return true;
}

int main(int argc, char* argv[]) {
	Gtk::Main kit(argc,argv);

	Gtk::Window w;
	w.set_title("Hello World");

	CruzDiagonal cruz;
	w.add(cruz);

	w.show_all();

	Gtk::Main::run(w);

	return 0;
}