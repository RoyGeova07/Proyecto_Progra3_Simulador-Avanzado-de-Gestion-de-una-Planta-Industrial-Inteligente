#ifndef EMPLEADO_H
#define EMPLEADO_H

#include <iostream>
#include <string>

class Empleado
{
protected:

    std::string nombre;
    int id;
   std::string cargo;
    static int contadorID;

public:

    Empleado(const String &nombre, const String &cargo) 
        : nombre(nombre), cargo(cargo), id(++contadorID) {} // Asigna un ID unico automáticamente

    virtual void MostrarInfo() const {
        std::cout << "Empleado ID: " << id << " - Nombre: " << nombre << " - Cargo: " << cargo << std::endl;
    }

    virtual void RealizarTarea() = 0; // funciona pura (obligatorio en subclases)
    virtual ~Empleado() = default; // Destructor virtual

    // Getters
    int getId() const { return id; }
    std::string getNombre() const { return nombre; }
    std::string getCargo() const { return cargo; }
};

//aqui inicializacion del contador estatico
int Empleado::contadorID = 0;


#endif // EMPLEADO_H