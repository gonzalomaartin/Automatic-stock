#include <iostream>
#include <fstream>
#include <vector>
#include "src/headers/Algorithms2.h"
#include "src/headers/order.h"
#include "src/headers/shipment.h"
#include "src/headers/box2.h"
#include "src/headers/container2.h"
#include <ctime> 

#define HEIGHT 50
#define WIDTH 100
#define LENGTH 100

int main()
{
    int menu;
    for(;;)
    {
        std::cout << "Welcome to the NN system" << std::endl; 
        std::cout << "Select an option" << std::endl;
        std::cout << "1. Order boxes" << std::endl;
        std::cout << "2. Exit" << std::endl;
        std::cin >> menu;
        if(menu == 1)
        {
            remove("D:\\repos\\Automatic_stock\\filesTXT\\shipment.txt");
            remove("D:\\repos\\Automatic_stock\\filesTXT\\results.txt");
            remove("D:\\repos\\Automatic_stock\\filesTXT\\order.txt");
            order O1;
            O1.save_order();
            Algorithms A1(O1.get_num_boxes(), LENGTH, WIDTH, HEIGHT, O1.get_V_boxes());
            A1.place_boxes();
            A1.resize_containers(); 
            A1.show_targets();
            shipment S1(O1.get_V_boxes(), A1.V_containers_in_use);   
            S1.save_shipment();
        }
        else if(menu == 2)
        {
            std::cout << "The program is finished" << std::endl;
            std::cout << "Have a nice day" << std::endl;
            break;
        }
        else
        {
            std::cout << "Invalid option" << std::endl;
        }
        
    }
    return 0;
}
