#ifndef SUPERVISOR_H
#define SUPERVISOR_H
#include "Empleado.h"


class EmpleadoSuperVisor : public Empleado
{
public:


    EmpleadoSuperVisor(std::string nombre) : Empleado(nombre, "EmpleadoSuperVisor") {}

    void RealizarTarea() override{

        std::cout<<nombre<<" esta realizando la tarea de supervisar las maquinas.\n";

    }


};


#endif //SUPERVISOR_H