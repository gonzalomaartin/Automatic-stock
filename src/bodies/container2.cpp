#include <iostream>
#include <fstream>
#include <vector>
#include "../headers/box2.h"
#include "../headers/container2.h"
#include <fstream>

// Constructor base del contenedor
// Container base constructor
container::container()
{
    length_container = 0;
    width_container = 0;
    height_container = 0;
    preset_objects();
}
// Constructor del contenedor con parámetros
// Container constructor with parameters
container::container(int l, int w, int h)
{
    length_container = l;
    width_container = w;
    height_container = h;
    preset_objects();

    for (int i = 0; i < h; i++)
    {
        objects_in_use[i] = new int *[w];
        for (int j = 0; j < w; j++)
        {
            objects_in_use[i][j] = new int[l];
            for (int k = 0; k < l; k++)
            {
                objects_in_use[i][j][k] = 0;
            }
        }
    }
}
// Presetear los objetos del contenedor
// Preset the container objects
void container::preset_objects()
{
    objects = new int **[height_container];
    for (int i = 0; i < height_container; i++)
    {
        objects[i] = new int *[width_container];
        for (int j = 0; j < width_container; j++)
        {
            objects[i][j] = new int[length_container];
            for(int k = 0; k < length_container; k++)
            {
                objects[i][j][k] = 0;
            }
        }
    }
}
// Establecer los objetos del contenedor
// Set the container objects
void container::set_objects(int ***objects_in)
{
    for (int i = 0; i < height_container; i++)
    {
        for (int j = 0; j < width_container; j++)
        {
            for(int k = 0; k < length_container; k++)
            {
                objects[i][j][k] = objects_in[i][j][k];
            }
        }
    }
}
// Añadir una caja al contenedor
// Add a box to the container
void container::add_box(box b)
{
    V_box.push_back(b);
}
// Obtener la longitud del contenedor
// Get the container length
int container::get_length()
{
    return length_container;
}
// Obtener el ancho del contenedor
// Get the container width
int container::get_width()
{
    return width_container;
}
// Obtener la altura del contenedor
// Get the container height
int container::get_height()
{
    return height_container;
}
int container::get_volume(){
    return length_container * width_container * height_container; 
}
// Obtener el número de cajas
// Get the number of boxes
int container::get_num_boxes()
{
    return V_box.size();
}
void container::resize(int l, int w, int h){
    length_container = l;
    width_container = w;
    height_container = h;
}
// Calcular el volumen del contenedor
// Calculate the container volume
int container::volume()
{
    return length_container * width_container * height_container;
}
// Calcular el área superficial del contenedor
// Calculate the container surface area
int container::get_surface_area()
{
    return length_container * width_container;
}
// Obtener el vector de cajas
// Get the box vector
std::vector<box> container::get_V()
{
    return V_box;
}
// Calcular el volumen de las cajas
// Calculate the volume of the boxes
int container::add_volume_boxes()
{
    int volume = 0;
    for (int i = 0; i < V_box.size(); i++)
    {
        volume += V_box[i].get_volume();
    }
    return volume;
}
// Mostrar los objetos del contenedor
// Show the container objects
void container::show_objects_container()
{
    for (int i = 0; i < height_container; i++)
    {
        std::cout << " Layer " << i + 1 << std::endl;
        for (int j = 0; j < width_container; j++)
        {
            for(int k = 0; k < length_container; k++)
            {
                std::cout << objects[i][j][k] << " ";
            }
            std::cout << std::endl;
        }
        std::cout << std::endl << std::endl;
    }
}

// Mostrar las cajas del contenedor
// Show the container boxes
void container::show_container()
{
    std::cout << std::endl << "--------------------------" << std::endl;
    std::cout << "  Length: " << length_container << std::endl;
    std::cout << "  Width: " << width_container << std::endl;
    std::cout << "  Height: " << height_container << std::endl;
    std::cout << "  Number of boxes: " << V_box.size() << std::endl;
    for (int i = 0; i < V_box.size(); i++)
    {
        std::cout << std::endl << " Box " << i + 1 << std::endl;
        V_box[i].show_box();
    }
    std::cout << std::endl << " Objects" << std::endl << std::endl;
    show_objects_container();
    std::cout << "--------------------------" << std::endl << std::endl;
}

// Guardar el contenedor en un archivo
// Save the container in a file
void container::save_container(std::ofstream &file)
{
    file << std::endl << "--------------------------" << std::endl;
    file << "  Length: " << length_container << std::endl;
    file << "  Width: " << width_container << std::endl;
    file << "  Height: " << height_container << std::endl;
    file << "  Number of boxes: " << V_box.size() << std::endl;
    for (int i = 0; i < V_box.size(); i++)
    {
        file << std::endl << " Box " << i + 1 << std::endl;
        V_box[i].save_box(file);
    }
    file << std::endl << " Objects" << std::endl << std::endl;
    for (int i = 0; i < height_container; i++)
    {
        file << " Layer " << i + 1 << std::endl;
        for (int j = 0; j < width_container; j++)
        {
            for(int k = 0; k < length_container; k++)
            {
                file << objects[i][j][k] << " ";
            }
            file << std::endl;
        }
        file << std::endl << std::endl;
    }
    file << "--------------------------" << std::endl << std::endl;
}