#ifndef GESTOR_DE_PLANTA_H
#define GESTOR_DE_PLANTA_H

#include <iostream>
#include <vector>
#include <string>
#include <string.h>
#include "Frutas.h"
#include "Producto.h"
#include "Maquina.h"
#include "Empleado.h"


class Gestor_De_Planta
{
private:
  
std::vector<Producto> productos;
std::vector<Frutas> FRUTAS;
std::vector<Maquina*> maquinas;
std::vector<Empleado*> empleado;

public:

    Gestor_De_Planta()=default;
    ~Gestor_De_Planta();    

    //void agregarEmpleado(const std::string &nombre, const std::string &cargo);
    


    void listarEmpleados() const;
    void listarProductos() const;
    void ListarFrutas() const;
    void VerEstadoMaquina() const;
    void eliminarEmpleado(int id);
    
    

};


#endif //GESTOR_DE_PLANTA_H