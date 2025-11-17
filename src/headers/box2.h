// Definicion de la clase box, que representa una caja con una longitud, ancho, altura y volumen.
// Define the box class, which represents a box with a length, width, height, and volume.


#ifndef BOX_H
#define BOX_H

class box 
{
    protected:

        char id_box;
        int length_box;
        int width_box;
        int height_box;
        int volume_box;
        bool placed;

    public:

        box() :id_box('Z'), length_box(0), width_box(0), height_box(0), volume_box(0), placed(false) {}
        box(int l, int w, int h, bool p, char id);
        int surface_area();
        char get_id();
        int get_length();
        int get_width();
        int get_height();
        int get_volume();
        void show_box();
        void set_placed(bool p);
        bool get_placed();
        void save_box(std::ofstream &file);
};

#endif