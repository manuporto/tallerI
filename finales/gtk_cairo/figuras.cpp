#include <gtkmm/application.h>
#include <gtkmm/drawingarea.h>
#include <gtkmm/window.h>
#include <cmath>

class Ovalo : public Gtk::DrawingArea {
    protected:
        virtual bool on_draw(const Cairo::RefPtr<Cairo::Context> &cr) {
            Gtk::Allocation alloc = get_allocation();
            int ancho = alloc.get_width();
            int alto = alloc.get_height();

            cr->translate(ancho/2.0, alto/2.0);
            cr->scale(ancho/2.0, alto/2.0);
            cr->arc(0.0, 0.0, 0.02, 0.0, 2 * M_PI);
            cr->set_source_rgba(0, 0, 1.0, 1);
            cr->stroke();
            return true;
        }
};

class Rectangulo : public Gtk::DrawingArea {
    protected:
        virtual bool on_draw(const Cairo::RefPtr<Cairo::Context> &cr) {
            cr->set_source_rgba(0, 0, 1.0, 1);
            //cr->set_line_width(1);
            cr->rectangle(20, 20, 80, 80);
            //cr->stroke();
            cr->fill();
            return true;
        }
};

class Triangulo : public Gtk::DrawingArea {
    protected:
        virtual bool on_draw(const Cairo::RefPtr<Cairo::Context> &cr) {
            Gtk::Allocation alloc = get_allocation();
            int ancho = alloc.get_width();
            int alto = alloc.get_height();
            int xc = ancho / 2;
            int yc = alto/2;

            cr->set_line_width(10.0);
            cr->set_source_rgba(0, 0, 1.0, 1);
            cr->move_to(0,0);
            cr->line_to(xc, yc);
            cr->line_to(0, alto);
            //cr->move_to(xc, yc);
            //cr->line_to(ancho, yc);
            cr->close_path();
            cr->stroke();
            return true;
        }
};

int main(int argc, char *argv[]) {
    Glib::RefPtr<Gtk::Application> app = Gtk::Application::create(argc, argv);
    Gtk::Window win;
    win.set_title("Drawing Area");
    Triangulo area;
    win.add(area);
    win.show_all();
    return app->run(win);
}
