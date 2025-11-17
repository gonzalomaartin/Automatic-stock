// Definicion de la clase order que se utiliza para crear y mostrar el pedido de cajas
// Definition of the class order which is used to create and show the order of boxes

#ifndef ORDER_H
#define ORDER_H

class order : public box
{
    private:
        int num_boxes;
        std::vector<box> V_boxes_order;
    public:
        order();
        void show_order();
        int get_num_boxes();
        std::vector<box> get_V_boxes();
        void save_order();
};

#endif