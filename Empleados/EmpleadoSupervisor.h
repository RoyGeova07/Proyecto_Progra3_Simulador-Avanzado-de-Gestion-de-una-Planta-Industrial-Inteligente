#ifndef SUPERVISOR_H
#define SUPERVISOR_H
#include <Empleado.h>


class Supervisor : public Empleado
{
public:


    Supervisor(std::string nombre) : Empleado(nombre, "Supervisor") {}


};


#endif //SUPERVISOR_H