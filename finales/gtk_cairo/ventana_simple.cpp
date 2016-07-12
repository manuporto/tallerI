#include <gtkmm/application.h>
#include <gtkmm/button.h>
#include <gtkmm/window.h>

#include <iostream>

class Ventana : public Gtk::Window {
    protected:
        Gtk::Button cerrar_btn;
        void on_cerrar_btn_clicked() {
            std::cout << "Cerrando programa" << std::endl;
            unset_application();
        }

    public:
        Ventana() : cerrar_btn("Cerrar") {
            add(cerrar_btn);
            cerrar_btn.signal_clicked().connect(sigc::mem_fun(*this, 
                        &Ventana::on_cerrar_btn_clicked));
            show_all();
        }

        ~Ventana() {
            std::cout << "Se cierra ordenadamente" << std::endl;
        }
};

int main(int argc, char *argv[]) {
    Glib::RefPtr<Gtk::Application> app = Gtk::Application::create(argc, argv);
    Ventana ventana;
    ventana.set_title("Ejemplo");
    return app->run(ventana);
}
