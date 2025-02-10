#ifndef GESTOR_DE_PLANTA_H
#define GESTOR_DE_PLANTA_H

#include <iostream>
#include <vector>
#include <string>
#include <string.h>
#include "Ingrediente.h"
#include <Producto.h>
#include <Maquina.h>
#include <Empleado.h>


class Gestor_De_Planta
{
private:
  


public:

    std::vector<Producto> productos;
    std::vector<Ingrediente> ingredientes;
    std::vector<Maquina> maquinas;
    std::vector<Empleado> empleado;

    

};


#endif //GESTOR_DE_PLANTA_H