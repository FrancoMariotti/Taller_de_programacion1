#include <iostream>
#include "gtkmm/window.h"
#include "gtkmm/checkbutton.h"
#include "gtkmm/main.h"

class FooWindow :public Gtk::Window{
	public:
		FooWindow();
		virtual ~FooWindow();
	protected:
		void on_button_clicked();

		Gtk::CheckButton button;
};

FooWindow::FooWindow():button("Foo") {
	set_title("Foo Example");
	set_border_width(10);

	button.signal_clicked().connect(sigc::mem_fun(*this,&FooWindow::on_button_clicked));
	button.set_active();

	add(button);
	show_all_children();
}

FooWindow::~FooWindow() {

}

void FooWindow::on_button_clicked() {
	std::cout<<"checkbox Foo clicked"<<std::endl;
}

int main(int argc,char* argv[]) {
	Gtk::Main kit(argc,argv);
	FooWindow w;
	

	Gtk::Main::run(w);

	return 0;
}