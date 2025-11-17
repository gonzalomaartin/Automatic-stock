// Definicion de la clase target, que representa un objetivo en el espacio de trabajo del robot
// Definition of the class target, which represents a target in the robot's workspace

#ifndef TARGET_H
#define TARGET_H

class target
{
    private:
        float position_x;
        float position_y;
        float position_z;
    
    public:
        target();
        target(float x, float y, float z);
        float get_position_x();
        float get_position_y();
        float get_position_z();
        void show_target();
        
};

#endif