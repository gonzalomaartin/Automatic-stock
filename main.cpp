#include <iostream>
#include <fstream>
#include <vector>
#include <filesystem>
#include <thread>
#include "src/headers/Algorithms.h"
#include "src/headers/order.h"
#include "src/headers/shipment.h"
#include "src/headers/box.h"
#include "src/headers/container.h"
#include <ctime> 

#define HEIGHT1 50
#define WIDTH1 100
#define LENGTH1 100
#define HEIGHT2 25
#define WIDTH2 50
#define LENGTH2 50
#define HEIGHT3 15
#define WIDTH3 25
#define LENGTH3 25

int main()
{
    int menu;
    for(;;)
    {
        while (!std::filesystem::exists("D:\\repos\\Automatic_stock\\filesTXT\\webOrder.txt")) {
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }
        order O1;
        O1.save_order();
        Algorithms A1(O1.get_num_boxes(), LENGTH1, WIDTH1, HEIGHT1, O1.get_V_boxes());
        A1.place_boxes();
        /*
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
            Algorithms A1(O1.get_num_boxes(), LENGTH1, WIDTH1, HEIGHT1, O1.get_V_boxes());
            A1.place_boxes();
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
        }*/
        
    }
    return 0;
}
