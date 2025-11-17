#include <iostream>
#include <vector>
#include "../headers/target.h"

// Constructor base del objetivo
// Target base constructor
target::target()
{
    position_x = 0.0;
    position_y = 0.0;
    position_z = 0.0;
}
// Constructor del objetivo con parámetros
// Target constructor with parameters
target::target(float x, float y, float z)
{
    position_x = x;
    position_y = y;
    position_z = z;
}
// Obtener la posición x del objetivo
// Get the x position of the target
float target::get_position_x()
{
    return position_x;
}
// Obtener la posición y del objetivo
// Get the y position of the target
float target::get_position_y()
{
    return position_y;
}
// Obtener la posición z del objetivo
// Get the z position of the target
float target::get_position_z()
{
    return position_z;
}
// Mostrar el objetivo
// Show the target
void target::show_target()
{
    std::cout << "Target position: (" << position_x << ", " << position_y << ", " << position_z << ") non_unities" << std::endl;
}
