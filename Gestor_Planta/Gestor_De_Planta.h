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
  
std::vector<Producto> productos;
std::vector<Ingrediente> ingredientes;
std::vector<Maquina> maquinas;
std::vector<Empleado> empleado;

public:

    Gestor_De_Planta()=default;
    ~Gestor_De_Planta();    

    void agregarEmpleado(const std::string &nombre, const std::string &cargo);
    void agregarProducto(Producto* nuevoProducto);
    void agregarMaquina(const std::string &nombre, const std::string &tipo);

    void listarEmpleados() const;
    void listarProductos() const;
    void listarMaquinas() const;

    void eliminarEmpleado(int id);
    void eliminarProducto(const std::string &nombre);
    void eliminarMaquina(int id);
    

};


#endif //GESTOR_DE_PLANTA_H