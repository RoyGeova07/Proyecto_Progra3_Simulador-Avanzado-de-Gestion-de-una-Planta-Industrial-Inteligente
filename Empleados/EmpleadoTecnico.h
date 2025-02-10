#ifndef TECNICO_H
#define TECNICO_H
#include <Empleado.h>

class TecnicoMantenimiento : public Empleado {
    public:

        TecnicoMantenimiento(std::string nombre) : Empleado(nombre, "Tecnico de Mantenimiento") {}

    };
    

#endif //TECNICO_H