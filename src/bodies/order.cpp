#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <string>
#include <cstdio>
#include "../headers/box.h"
#include "../headers/order.h"

// Constructor de la orden, donde generamos el menú para seleccionar las cajas
// Order constructor, where we generate the menu to select the boxes
order::order()
{
    std::ifstream file("D:\\repos\\Automatic_stock\\filesTXT\\webOrder.txt");
        if (!file) {
            throw std::runtime_error("Could not open file");
        }

    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string ignore;
        int id, quantity;
        iss >> ignore >> id >> ignore >> ignore >> quantity;
        if (id == 1) {
            for (int i = 0; i < quantity; i++) {
                V_boxes_order.push_back(box(15, 12, 10, false, 'S'));
            }
        }
        else if (id == 2) {
            for (int i = 0; i < quantity; i++) {
                V_boxes_order.push_back(box(20, 21, 7, false, 'M'));
            }
        }
        else if (id == 3) {
            for (int i = 0; i < quantity; i++) {
                V_boxes_order.push_back(box(20, 21, 21, false, 'L'));
            }
        }
        else if (id == 4) {
            for (int i = 0; i < quantity; i++) {
                V_boxes_order.push_back(box(25, 30, 21, false, 'X'));
            }
        }
    }
    file.close();
    if (std::remove("D:\\repos\\Automatic_stock\\filesTXT\\webOrder.txt") == 0) {
        std::cout << "Archivo <webOrder.txt> eliminado con exito\n";
    } else {
        std::cerr << "No se pudo eliminar el archivo\n";
    }
    std::cout << "Order loaded" << std::endl;
    num_boxes = V_boxes_order.size();
    

    /*
    std::cout << "Welcome to the box ordering system" << std::endl;
    std::cout << "Type the number of the box that you want to order" << std::endl;
    for(int i = 0; i < 1000; i++)
    {
        std::cout << "--------------------------" << std::endl;
        std::cout << "Select Box: " << std::endl;
        std::cout << "  Box 1: 150mm x 120mm x 100mm" << std::endl;
        std::cout << "  Box 2: 200mm x 210mm x  70mm" << std::endl;
        std::cout << "  Box 3: 200mm x 210mm x 210mm"<< std::endl;
        std::cout << "  Box 4: 250mm x 300mm x 210mm" << std::endl;
        std::cout << "  Finish the order: 7" << std::endl;
        std::cout << "--------------------------" << std::endl;

        int menu;
        std::cin >> menu;
        switch (menu)
        {
        case 1:
            std::cout << "Selected Box 1" << std::endl;
            V_boxes_order.push_back(box(15, 12, 10, false, 'S'));
            break;
        case 2:
            std::cout << "Selected Box 2" << std::endl;
            V_boxes_order.push_back(box(20, 21, 7, false, 'M'));
            break;
        case 3:
            std::cout << "Selected Box 3" << std::endl;
            V_boxes_order.push_back(box(20, 21, 21, false, 'L'));
            break;
        case 4:
            std::cout << "Selected Box 4" << std::endl;
            V_boxes_order.push_back(box(25, 30, 21, false, 'X'));
            break;
        case 7:
            std::cout << "The order is finished" << std::endl;
            i = 1000;
            break;
        default:    
            std::cout << "Invalid option" << std::endl;
            break;
        }
    }
    num_boxes = V_boxes_order.size();*/
}
// Mostrar la orden
// Show the order
void order::show_order()
{
    std::cout << std::endl << "--------------------------" << std::endl;
    std::cout << "  Number of boxes: " << V_boxes_order.size() << std::endl;
    for (int i = 0; i < V_boxes_order.size(); i++)
    {
        std::cout << "  Box " << i + 1 << std::endl;
        V_boxes_order[i].show_box();
    }
}
// Obtener el número de cajas
// Get the number of boxes
int order::get_num_boxes()
{
    return num_boxes;
}
// Obtener el vector que contiene las cajas
// Get the vector that contains the boxes
std::vector<box> order::get_V_boxes()
{
    return V_boxes_order;
}
// Guardar la orden en un archivo
// Save the order in a file
void order::save_order()
{
    std::ofstream file("D:\\repos\\Automatic_stock\\filesTXT\\order.txt", std::ios::app);
    file << std::endl << "--------------------------" << std::endl;
    file << "  Number of boxes: " << V_boxes_order.size() << std::endl;
    for (int i = 0; i < V_boxes_order.size(); i++)
    {
        file << "  Box " << i + 1 << std::endl;
        V_boxes_order[i].save_box(file);
    }
}