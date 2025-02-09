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

    Empleado(String nombre,int id, String cargo){

        this->id = ++contadorID;
        this->nombre=nombre;
        this->cargo=cargo;

    }

    void MostrarInfo(){

        std::cout<<"ID: "<<this->id<<" - Nombre: "<<this->nombre<<" - Cargo"<<this->cargo<<std::endl;

    }
  
};

int Empleado::contadorID=0;


#endif //EMPLEADO_H