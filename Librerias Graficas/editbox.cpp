#include "gtkmm.h"

void formatear(Gtk::Entry* entry) {
	Glib::ustring texto = entry->get_text();
	char letraMinuscula = texto.substring(0,1).uppercase();
	texto.replace(0,1,letraMinuscula);
	entry->set_text(texto);
}

class FormatearButton: public Gtk::Button {
public:
	FormatearButton(Gtk::Entry* entry);
	~FormatearButton();
protected:
	void on_clicked();
	Gtk::Entry* entry;
}

FormatearButton::FormatearButton(): Gtk::Button("Formatear") {};
FormatearButton::~FormatearButton() {};

void FormatearButton::on_clicked() {
	 formatear(this->entry);
}

int main(int argc,char* argv[]) {
	Gtk::Main kit(argc,argv);
	Gtk::Window w;
	Gtk::Entry entry;
	FormatearButton button(&entry);
	Gtk::VBox box;
	box.add(entry);
	box.add(button);
	w.add(box);
	w.show_all();

	Gtk::Main::run(w);
	return 0;
}