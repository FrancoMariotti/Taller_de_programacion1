class Circulo: public Gtk::DrawingArea {
public:
	Circulo();
	~Circulo();
protected:
	virtual bool on_expose_event(GdkEventExpose* event);
};

Circulo::Circulo() {};

Circulo::~Circulo() {};

bool Circulo::on_expose_event(GdkEventExpose* event) {
	Glib::RefPtr<Gdk::Window> window = getWindow();

	if (window) {
		Gtk::Allocation allocation = get_allocation();

		int wWidth = allocation.getWidth();
		int wHeight = allocation.getHeight();

		Cairo::RefPtr<Cairo::Context> context = window->create_cairo_context();
		context->scale(width,height);

		context->rectangle(0,0,1.0,1.0); //toda la ventana
		context->set_source_rgb(0.0,0.0,0.0,0.0) //fondo negro
		context->fill();

		context->arc(0.5,0.5, 0.5,0.0/*angle start*/,M_PI * 2 /*angle end*/);
		context->set_source_rgb(1.0,1.0,1.0);
		context->fill_preserve();
		context->set_line_width(0.15);
		context->stroke();
	}

	return true;
} 



int main(int argc,char* argv[]) {
	Gtk::Main kit(argc,argv);
	
	Gtk::Window window;
	Circulo circulo;
	window.add(circulo);
	circulo.show_all();

	Gtk::Main::run(window);
	return 0;
}