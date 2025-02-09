#ifndef INGREDIENTES_H
#define INGREDIENTES_H

#include <iostream>
#include <vector>
#include <string>
#include <string.h>

//la direccon de -> & el valor estara en constante cambio
//se usa 'const' para no modificar el objeto 

//en  los strings son objetos, no tipos primitivos como en Java.
//Si pasamos std::string nombre sin const &, se haría una copia completa del string, lo que es ineficiente.


class Ingrediente
{
private:
    

public:

    std::string nombre;
    int cantidad;
    std::string unidad_de_medida;

    //constructor
    // en C++ es mejor inicializar los atributos directamente en la lista de inicializacion
    //
    Ingrediente(const std::string &nombre, int cantidad,const std::string &unidad_de_medida) 
    : nombre(nombre), cantidad(cantidad), unidad_de_medida(unidad_de_medida) {}

    void MostrarInfo(){

        std::cout<<"Ingrediente: "<<this->nombre<<" - "<<this->cantidad<<" "<<this->unidad_de_medida<<std::endl;

    }

    //getterssss
    std::string getNombre() const {return nombre;}
    int getCantidad() const {return cantidad;}
    std::string getUniDeMedida() const  {return unidad_de_medida;}

    //settersss
    void setNombre(const std::string &nombre) {this->nombre=nombre;}
    void setCantidad(int cantidad) {this->cantidad=cantidad;}
    void setUnidad_De_Medida(const std::string &unidad_de_medida) {this->unidad_de_medida=unidad_de_medida;}
  
};

//Sin esta linea, el codigo quedaria abierto y el preprocesador no sabria donde termina la proteccion.
#endif //INGREDIENTES_H
