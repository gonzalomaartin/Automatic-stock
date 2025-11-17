#include <iostream>
#include <fstream>
#include <vector>
#include "../headers/box2.h"
#include "../headers/container2.h"
#include "../headers/shipment.h"
#include "../headers/order.h"
#include "../headers/target.h"   
#include "../headers/Algorithms2.h"

#define HEIGHT1 50
#define WIDTH1 100
#define LENGTH1 100
#define HEIGHT2 35 
#define WIDTH2 75
#define LENGTH2 75 
#define HEIGHT3 25
#define WIDTH3 50
#define LENGTH3 50


// Constructor de la clase Algorithms
// Algorithms class constructor
Algorithms::Algorithms(int nb, int l, int w, int h, std::vector<box> V)
{
    container cont(l, w, h); 
    V_containers_in_use.push_back(cont);  
    //V_containers_in_use.reserve(nb); 
    V_boxes_in_use = V;
}
/* FUNCION PARA COMPROBAR QUE LAS CAJAS SE COLOCAN CORRECTAMENTE EN EL ALGORITMO
 * FUNCTION TO CHECK THAT THE BOXES ARE PLACED CORRECTLY IN THE ALGORITHM
 * void Algorithms::show_boxes()
 * {
 *    for (int i = 0; i < V_boxes_in_use.size(); i++)
 *    {
 *        std::cout << "Box " << i + 1 << std::endl;
 *        V_boxes_in_use[i].show_box();
 *    }
 * }
 */
void Algorithms::add_container(container in)
{
    V_containers_in_use.push_back(in);
    /* COMPROBAR QUE LOS CONTENEDORES SE AÑADEN CORRECTAMENTE EN EL ALGORITMO
     * PROVE THAT THE CONTAINERS ARE ADDED CORRECTLY IN THE ALGORITHM
     *  std::cout << std::endl << "--------------------------" << std::endl;
     *  std::cout << "  Container added" << std::endl;
     *  std::cout << "  Length: " << in.get_length() << std::endl;
     *  std::cout << "  Width: " << in.get_width() << std::endl; 
     *  std::cout << "  Height: " << in.get_height() << std::endl;   
     *  std::cout << "--------------------------" << std::endl << std::endl;
     */
}
// Función para añadir un objetivo
// Function to add a target
void Algorithms::add_target(target in)
{
    V_targets.push_back(in);
}

// Función para comprobar si se puede colocar un objeto en una posición
// Function to check if an object can be placed in a position
bool Algorithms::prove_object(int ***objects, int w, int l, int h, box v, bool inverted)
{
    int width, length, height = h + v.get_height();
    if(inverted)
    {
        width = w + v.get_length();
        length = l + v.get_width();
    } else
    {
        width = w + v.get_width();
        length = l + v.get_length();
    }

    for (int i = h; i < height; i++)
    {
        for (int j = w; j < width; j++)
        {
            for(int k = l; k < length; k++)
            {
                if (objects[i][j][k] != 0)
                {
                    return false;
                }
            }
        }
    }
    return true;
}
// Función para establecer el vecto de las cajas
// Function to set the vector of boxes
void Algorithms::set_boxes(std::vector<box> V)
{
    V_boxes_in_use = V;
}
// Función para ordenar las cajas de mayor a menor tamaño
// Function to sort the boxes from largest to smallest
void Algorithms::order_boxes()
{
    for (int i = 1; i < V_boxes_in_use.size(); i++)
    {
        int j = i - 1;
        int n = V_boxes_in_use[i].get_volume();        
        while (j >= 0  && V_boxes_in_use[j].get_volume() < n)
        {
            box temp = V_boxes_in_use[j];
            V_boxes_in_use[j] = V_boxes_in_use[j + 1];
            V_boxes_in_use[j + 1] = temp;
            j--;
        }
    }
}
/* FUNCION PARA COMPROBAR QUE LAS CAJAS SE COLOCAN CORRECTAMENTE EN EL ALGORITMO
 * FUNCTION TO CHECK THAT THE BOXES ARE PLACED CORRECTLY IN THE ALGORITHM
 *  void Algorithms::show_objects()
 *  {
 *      for (int i = 0; i < height_container_in_use; i++)
 *      {
 *          for (int j = 0; j < width_container_in_use; j++)
 *          {
 *              for(int k = 0; k < length_container_in_use; k++)
 *              {
 *                  std::cout << objects_in_use[i][j][k] << " ";
 *              }
 *              std::cout << std::endl;
 *          }
 *          std::cout << std::endl << std::endl;
 *      }
 *  }
 */
/* FUNCION PARA COMPROBAR QUE LOS CONTENEDORES SE CREAN CORRECTAMENTE EN EL ALGORITMO
 *  void Algorithms::show_containers()
 *  {
 *      for (int i = 0; i < V_containers_in_use.size(); i++)
 *      {
 *          std::cout << "Container " << i + 1 << std::endl;
 *          V_containers_in_use[i].show_container();
 *      }
 *  }
 */
// Función para mostrar los objetivos
// Function to show the targets
void Algorithms::show_targets()
{
    for (int i = 0; i < V_targets.size(); i++)
    {
        std::cout << "Target " << i + 1 << std::endl;
        V_targets[i].show_target();
    }
}

// Función para resetear los objetos
// Function to reset the objects
void Algorithms::reset_objects()
{
    for(container cont : V_containers_in_use){
        for (int i = 0; i < cont.get_height(); i++)
        {
            for (int j = 0; j < cont.get_width(); j++)
            {
                for(int k = 0; k < cont.get_length(); k++)
                {
                    cont.objects_in_use[i][j][k] = 0;
                }
            }
        }
    }
}
// Función para eliminar las cajas colocadas
// Function to remove placed boxes
void Algorithms::erase_boxes_placed()
{
    for(int i = 0; i < V_boxes_in_use.size(); i++)
    {
        if(V_boxes_in_use[i].get_placed())
        {   
            V_boxes_in_use.erase(V_boxes_in_use.begin() + i);
            i--;
        }
    }
}
// Función para calcular la posición del objetivo
// Function to calculate the target position
void Algorithms::calculate_position_target(float *pos_x, float *pos_y, float *pos_h, 
                                           int l, int w, int h,
                                           int o, int n, int m,
                                           bool inverted)
{
    if(!inverted)
    {
        *pos_x = ((2.0 * (float)(l) + (float)(o)) / 2.0);
        *pos_y = ((2.0 * (float)(w) + (float)(n)) / 2.0);
        *pos_h = (float)(h + m);
    } 
    else
    {
        *pos_x = ((2.0 * (float)(l) + (float)(n)) / 2.0);
        *pos_y = ((2.0 * (float)(w) + (float)(o)) / 2.0);
        *pos_h = (float)(h + m);    
    }
}

void Algorithms::save_container(int n_container, int n_box)
{
    std::ofstream file;
    file.open("D:\\repos\\Automatic_stock\\filesTXT\\results.txt", std::ios::app);
    file << "Container: " << n_container << std::endl;
    file << "Number-boxes: " << n_box << std::endl;
    file.close();
}

void Algorithms::save_results(target t_in, box b_in)
{
    std::ofstream file;
    file.open("D:\\repos\\Automatic_stock\\filesTXT\\results.txt", std::ios::app);
    file << "ID_Box: " << b_in.get_id() << std::endl;
    file << "Target: (" << t_in.get_position_x() << ", " << t_in.get_position_y() << ", " << t_in.get_position_z() << ")" << std::endl;
    file.close();
}
/* FUNCION PARA COLOCAR LAS CAJAS EN LOS CONTENEDORES
 * Consiste en la anidación de bucles para recorrer las dimensiones del contenedor y comprobar si la caja cabe en esa posición.
 * El primero comprueba que no estén todas las cajas colocadas.
 * El segundo recorre el vector que contiene las cajas.
 * El tercero , cuarto y quinto recorren la altura, la anchura y la longitud del contenedor.
 * Si se cumplen las siguientes condiciones:
 * - La altura de la caja es menor o igual a la altura del contenedor menos la altura actual.
 * - La anchura de la caja es menor o igual a la anchura del contenedor menos la anchura actual.
 * - La longitud de la caja es menor o igual a la longitud del contenedor menos la longitud actual.
 * - La función prove_object devuelve true.
 * Se recorren las dimensiones de la caja y se asigna el número de la caja a la posición correspondiente en el contenedor.
 * Se calcula la posición del objetivo que se enviará al robot.
 * Se cambia el valor de la anchura, altura y longitud de las variables del bucle para salir.
 * Se cambia el valor de la variable placed de la caja a true.
 * Se incrementa el número de caja.
 * Una vez se han colocado todas las cajas se crea un contenedor con las cajas colocadas y se añade al vector de contenedores.
 * Se resetean los objetos.
 * Se eliminan las cajas colocadas.
 * Si no quedan cajas por colocar se sale del bucle, sino se repite con un contenedor nuevo y vacío.
 */

/*FUNCTION TO PLACE THE BOXES IN THE CONTAINERS
 * It consists of the nesting of loops to go through the dimensions of the container and check if the box fits in that position.
 * The first one checks that all the boxes are not placed.
 * The second one goes through the vector containing the boxes.
 * The third, fourth and fifth go through the height, width and length of the container.
 * If the following conditions are met:
 * - The height of the box is less than or equal to the height of the container minus the current height.
 * - The width of the box is less than or equal to the width of the container minus the current width.
 * - The length of the box is less than or equal to the length of the container minus the current length.
 * - The prove_object function returns true.
 * The dimensions of the box are traversed and the box number is assigned to the corresponding position in the container.
 * The position of the target to be sent to the robot is calculated.
 * The value of the width, height and length of the loop variables is changed to exit.
 * The value of the placed variable of the box is changed to true.
 * The box number is incremented.
 * Once all the boxes have been placed, a container is created with the placed boxes and added to the container vector.
 * The objects are reset.
 * The placed boxes are removed.
 * If there are no more boxes to place, the loop is exited, otherwise it is repeated with a new and empty container.
 */
void Algorithms::place_boxes()
{    
    int n_box = 1, n_container = 1;
    int m, n, o, t = 0;
    float pos_x, pos_y, pos_z; 
    order_boxes();
    bool all_boxes_placed = false;
    int container_count = 1; 
    while(!all_boxes_placed)
    { 
        for (int i = 0; i < V_boxes_in_use.size(); i++)
        {
            if(V_boxes_in_use[i].get_height() <= HEIGHT1 && V_boxes_in_use[i].get_length() <= LENGTH1 && V_boxes_in_use[i].get_width() <= WIDTH1)
            {
                for(container cont : V_containers_in_use){
                    for(int h = 0; h < cont.get_height(); h++)
                    {
                        for (int w = 0; w < cont.get_width(); w++)
                        {
                            for (int l = 0; l < cont.get_length(); l++)
                            {
                                if (V_boxes_in_use[i].get_height() <= cont.get_height() - h
                                && V_boxes_in_use[i].get_width() <= cont.get_width() - w 
                                && V_boxes_in_use[i].get_length() <= cont.get_length() - l 
                                && prove_object(cont.objects_in_use, w, l, h, V_boxes_in_use[i]))
                                {
                                    
                                    for (m = 0; m < V_boxes_in_use[i].get_height(); m++)
                                    {
                                        for (n = 0; n < V_boxes_in_use[i].get_width(); n++)
                                        {
                                            for (o = 0; o < V_boxes_in_use[i].get_length(); o++)
                                            {
                                                cont.objects_in_use[h + m][w + n][l + o] = n_box;
                                            }
                                        }
                                    }

                                    calculate_position_target(&pos_x, &pos_y, &pos_z, l, w, h, o, n, m, false);
                                    target T1(pos_x, pos_y, pos_z);
                                    add_target(T1);
                                    w = cont.get_width();
                                    l = cont.get_length();
                                    h = cont.get_height();
                                    n_box++;
                                    V_boxes_in_use[i].set_placed(true);
                                }
                                else if (V_boxes_in_use[i].get_height() <= cont.get_height() - h 
                                && V_boxes_in_use[i].get_length() <= cont.get_width() - w
                                && V_boxes_in_use[i].get_width() <= cont.get_length() - l 
                                && prove_object(cont.objects_in_use,  w, l, h, V_boxes_in_use[i], true))
                                {
                                    for (m = 0; m < V_boxes_in_use[i].get_height(); m++)
                                    {
                                        for (n = 0; n < V_boxes_in_use[i].get_width(); n++)
                                        {
                                            for (o = 0; o < V_boxes_in_use[i].get_length(); o++)
                                            {
                                                cont.objects_in_use[h + m][w + o][l + n] = n_box;
                                            }
                                        }
                                    }
                                    
                                    calculate_position_target(&pos_x, &pos_y, &pos_z, l, w, h, o, n, m, true);
                                    target T1(pos_x, pos_y, pos_z);
                                    add_target(T1);
                                    w = cont.get_width();
                                    l = cont.get_length();
                                    h = cont.get_height();
                                    n_box++;
                                    V_boxes_in_use[i].set_placed(true);
                                }
                            }
                        }
                    }

                }
                if(!V_boxes_in_use[i].get_placed()){
                    container Container2(LENGTH1, WIDTH1, HEIGHT1); 
                    V_containers_in_use.push_back(Container2); 
                    i--; 
                }
            }
            else{
                std::cout << "Las dimensiones de la caja, son más grandes que las dimensiones del contenedor " << std::endl; 
                std::cout << V_boxes_in_use[i].get_height() << " " << V_boxes_in_use[i].get_length() << " " << V_boxes_in_use[i].get_width()<< std::endl;            
            }
        }
        //erase_boxes_placed(); 
        if(V_boxes_in_use.empty())
        {
            all_boxes_placed = true;
        }
    }
}

void Algorithms::resize_containers(){
    for(container cont : V_containers_in_use){
        if(cont.get_height() <= HEIGHT3 and cont.get_length() <= LENGTH3 and cont.get_width() <= WIDTH3)
            cont.resize(LENGTH3, WIDTH3, HEIGHT3); 
        else if(cont.get_height() <= HEIGHT2 and cont.get_length() <= LENGTH2 and cont.get_width() <= WIDTH2)
            cont.resize(LENGTH2, WIDTH2, HEIGHT2); 
    }
}
