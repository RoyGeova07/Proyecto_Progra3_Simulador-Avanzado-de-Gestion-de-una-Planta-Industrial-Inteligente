#ifndef TECNICO_H
#define TECNICO_H
#include <Empleado.h>

class EmpleadoTecnico : public Empleado {
    public:

        EmpleadoTecnico(std::string nombre) : Empleado(nombre, "Tecnico de Mantenimiento") {}

    };
    

#endif //TECNICO_H