#ifndef INGREDIENTES_H
#define INGREDIENTES_H

#include <iostream>
#include <vector>
#include <string>
#include <string.h>
#include <vector>   



class Ingrediente
{
private:
    

public:

    std::string nombre;
    int cantidad;
    std::string unidad_de_medida;

    Ingrediente(std::string nombre, int cantidadm, std::string unidad_de_medida){

        this->nombre=nombre;
        this->cantidad=cantidad;
        this->unidad_de_medida=unidad_de_medida;

    }

    void MostrarInfo(){

        std::cout<<"Ingrediente: "<<this->nombre<<" - "<<this->cantidad<<" "<<this->unidad_de_medida<<std::endl;

    }
  
};

#endif //INGREDIENTES_H