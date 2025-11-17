#include <iostream>
#include <fstream>
#include <vector>
#include "../headers/box.h"
#include "../headers/container.h"
#include "../headers/shipment.h"

// Constructor base del envío
// Base constructor of the shipment
shipment::shipment()
{
    V_boxes = {};
    V_containers = {};
}
// Constructor del envío con parámetros
// Constructor of the shipment with parameters
shipment::shipment(std::vector<box> V, std::vector<container> C)
{
    V_boxes = V;
    V_containers = C;
}
// Mostrar el envío
// Show the shipment
void shipment::show_shipment()
{
    std::cout << std::endl << "Welcome to the box shipment system" << std::endl;
    std::cout << "This is the resume of your shipment" << std::endl;
    std::cout << std::endl << "--------------------------" << std::endl;
    std::cout << "  Number of containers: " << V_containers.size() << std::endl;
    std::cout << "  Number of boxes: " << V_boxes.size() << std::endl;
    for (int i = 0; i < V_containers.size(); i++)
    {
        std::cout << std::endl << "  Container " << i + 1 << std::endl;
        std::cout << "  Volume of boxes: " <<  V_containers[i].add_volume_boxes() << std::endl;
        V_containers[i].show_container();
    }
    std::cout << "--------------------------" << std::endl;
}

void shipment::save_shipment()
{
    std::ofstream file("D:\\repos\\Automatic_stock\\filesTXT\\shipment.txt", std::ios::app);
    file << std::endl << "Welcome to the box shipment system" << std::endl;
    file << "This is the resume of your shipment" << std::endl;
    file << std::endl << "--------------------------" << std::endl;
    file << "  Number of containers: " << V_containers.size() << std::endl;
    file << "  Number of boxes: " << V_boxes.size() << std::endl;
    for (int i = 0; i < V_containers.size(); i++)
    {
        file << std::endl << "  Container " << i + 1 << std::endl;
        file << "  Volume of boxes: " <<  V_containers[i].add_volume_boxes() << std::endl;
        V_containers[i].save_container(file);
    }
    file << "--------------------------" << std::endl;
    file.close();

}
// Obtener el número de contenedores
// Get the number of containers
int shipment::get_num_containers()
{
    return V_containers.size();
}
// Obtener el número de cajas
// Get the number of boxes
int shipment::get_num_boxes()
{
    return V_boxes.size();
}