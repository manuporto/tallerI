#include <gtkmm/application.h>
#include <gtkmm/button.h>
#include <gtkmm/window.h>
#include <gtkmm/comboboxtext.h>
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

class VentanaLBox : public Gtk::Window {
     protected:
        Gtk::ComboBoxText cbox;

    public:
        VentanaLBox() {
            Glib::ustring str = "Linea ";
            std::stringstream ss;
            for (int i = 1; i <= 10; ++i) {
                ss << i;
                cbox.append(str + ss.str());
                ss.str(""); 
            }
            cbox.append("Linea 1");
            add(cbox);
            show_all();
        }

        ~VentanaLBox() {
            std::cout << "Se cierra ordenadamente" << std::endl;
        }   
};

int main(int argc, char *argv[]) {
    Glib::RefPtr<Gtk::Application> app = Gtk::Application::create(argc, argv);
    VentanaLBox ventana;
    ventana.set_title("Ejemplo");
    return app->run(ventana);
}
