#ifndef EMPLEADO_H
#define EMPLEADO_H


#include <iostream>
#include <string>

using String = std::string;

class Empleado
{
private:

    static int contadorID;
    
public:

    String nombre;
    int id;
    String cargo;

    Empleado(const String &nombre,int id, const String &cargo) 
    : nombre(nombre), id(id),cargo(cargo) {}


    void MostrarInfo(){

        std::cout<<"ID: "<<this->id<<" - Nombre: "<<this->nombre<<" - Cargo"<<this->cargo<<std::endl;

    }

    // Destructor virtual para herencia
    virtual ~Empleado() {}

    String getNombre() const {return nombre;}
    int id() const {return id;}
    String cargo() const {return cargo;}

    void setNombre(const String &nombre) {this->nombre=nombre;}
    void setcargo(const String &cargo) {this->cargo=cargo;}
  
};

int Empleado::contadorID=0;


#endif //EMPLEADO_H