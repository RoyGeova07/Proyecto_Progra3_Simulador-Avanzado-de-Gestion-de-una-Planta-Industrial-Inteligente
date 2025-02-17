#ifndef OPERARIO_H
#define OPERARIO_H
#include "Empleado.h"

class EmpleadoOperario : public Empleado
{
public:


    EmpleadoOperario(std::string nombre) : Empleado(nombre, "EmpleadoOperario") {}

    void RealizarTarea() override{

        std::cout<<nombre<<" esta realizando la tarea de generar los reportes de la planta.\n";

    }


};

#endif //OPERARIO_H