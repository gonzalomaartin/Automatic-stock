// Definicion de la clase Algorithms 
// Definition of the class Algorithms

#include "box.h"
#include "container.h"
#include "target.h"

#ifndef ALGORITHMS_H
#define ALGORITHMS_H

class Algorithms 
{
    public:
        std::vector<box> V_boxes_in_use;
        std::vector<container> V_containers_in_use;
        std::vector<target> V_targets;
        int length_container_in_use;
        int width_container_in_use;
        int height_container_in_use;
        int ***objects_in_use;
        int boxes_volume; 
        Algorithms(int nb, int l, int w, int h, std::vector<box> V);
        void set_boxes(std::vector<box> V);
        //void show_boxes(); FUNCION PARA COMPROBAR QUE LAS CAJAS SE COLOCAN CORRECTAMENTE EN EL ALGORITMO
        void add_container(container in);
        void select_container(); 
        void place_boxes();
        bool prove_object(int ***objects, int w, int l, int h, box v, bool inverted = false);
        void order_boxes(); 
        //void show_objects(); FUNCION PARA COMPROBAR QUE LAS CAJAS SE COLOCAN CORRECTAMENTE EN EL ALGORITMO
        //void show_containers(); FUNCION PARA COMPROBAR QUE LOS CONTENEDORES SE COLOCAN CORRECTAMENTE EN EL ALGORITMO
        void reset_objects();
        void erase_boxes_placed();   
        void add_target(target in);
        void show_targets();
        void calculate_position_target(float *pos_x, float *pos_y, float *pos_h, 
                                       int l, int w, int h,
                                       int o, int n, int m, 
                                       bool inverted);
        void save_container(int n_container, int n_box);
        void save_results(target t_in, box b_in);
};

#endif