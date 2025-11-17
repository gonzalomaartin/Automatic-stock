#include <iostream>
#include <fstream>
#include "../headers/box.h"

// Constructor de la caja
// Box constructor
box::box(int l, int w, int h, bool p, char id)
{
    length_box = l;
    width_box = w;
    height_box = h;
    placed = p;
    volume_box = l * w * h;
    id_box = id;
}

// Obtener la longitud de la caja
// Get the length of the box
int box::get_length()
{
    return length_box;
}
// Obtener el ancho de la caja
// Get the width of the box
int box::get_width()
{
    return width_box;
}
// Obtener la altura de la caja
// Get the height of the box
int box::get_height()
{
    return height_box;
}
// Calcular el volumen de la caja (largo * ancho * altura)
// Calculate the volume of the box (length * width * height)
int box::get_volume()
{
    return volume_box;
}
// Calcular el área superficial de la caja (largo * ancho)
// Calculate the surface area of the box (length * width)
int box::surface_area()
{
    return length_box * width_box;
}
// Obtener el id de la caja
// Get the box id
char box::get_id()
{
    return id_box;
}
// Mostrar la caja
// Show the box
void box::show_box()
{
    std::cout << "Box " << id_box << std::endl;
    std::cout << "  Length: " << length_box << std::endl;
    std::cout << "  Width: " << width_box << std::endl;
    std::cout << "  Height: " << height_box << std::endl;
    std::cout << "  Volume: " << volume_box << std::endl;
}

// Guardar la caja en un archivo
// Save the box in a file
void box::save_box(std::ofstream &file)
{
    file << "  ID_Box " << id_box << std::endl;
    file << "  Length: " << length_box << std::endl;
    file << "  Width: " << width_box << std::endl;
    file << "  Height: " << height_box << std::endl;
    file << "  Volume: " << volume_box << std::endl;
}
// Establecer si la caja está colocada o no
// Set if the box is placed or not
void box::set_placed(bool p)
{
    placed = p;
}
// Obtener si la caja está colocada o no
// Get if the box is placed or not
bool box::get_placed()
{
    return placed;
}
