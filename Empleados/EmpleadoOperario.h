#ifndef OPERARIO_H
#define OPERARIO_H
#include <Empleado.h>

class Operario : public Empleado
{
public:


    Operario(std::string nombre) : Empleado(nombre, "Operario") {}


};

#endif //OPERARIO_H