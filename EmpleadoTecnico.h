#ifndef TECNICO_H
#define TECNICO_H
#include "Empleado.h"

class EmpleadoTecnico : public Empleado {
    public:

        EmpleadoTecnico(std::string nombre) : Empleado(nombre, "Tecnico de Mantenimiento") {}

        void RealizarTarea() override{

            std::cout<<nombre<<" esta realizando la tarea de mantenimiento tecnico.\n";

        }

    };
    

#endif //TECNICO_H