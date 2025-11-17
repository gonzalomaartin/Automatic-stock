// Definicion de la clase container, que representa un contenedor con una longitud, ancho, altura y un vector de cajas.
// Define the container class, which represents a container with a length, width, height, and a vector of boxes.

#ifndef CONTAINER_H
#define CONTAINER_H

class container
{
    protected:
        int length_container;
        int width_container;
        int height_container;
        std::vector<box> V_box;
        std::vector<container> list_containers; 

    public:
        int ***objects;
        int ***objects_in_use; 
        container();
        container(int l, int w, int h);
        void add_box(box b);
        void show_container();
        void preset_objects();
        void set_objects(int ***objects_in);
        int get_length();
        int get_width();
        int get_height();
        int get_volume(); 
        int get_num_boxes();
        void resize(int l, int w, int h); 
        std::vector<box> get_V();
        int volume();
        int get_surface_area();
        void show_objects_container();
        int add_volume_boxes();
        void save_container(std::ofstream &file);
};

#endif