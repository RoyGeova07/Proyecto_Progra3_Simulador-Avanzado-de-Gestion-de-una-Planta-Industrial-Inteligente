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


class Frutas
{

public: 

    enum Fruta{Agua,Limon,Naranja,Pilla,Sandia,Fresa,Tamarindo,Coco};


private:

    Fruta tipo;
    double costo;
    int cantidad;

public:

    
    //constructor
    // en C++ es mejor inicializar los atributos directamente en la lista de inicializacion
    Frutas(Fruta tipo, double costo,int cantidad) : tipo(tipo),costo(costo), cantidad(cantidad) {}

    //funcion para obtener la informacion de las frutas

    std::string getNombre() const {

        switch (tipo)
        {

        case Agua: return "Agua";
        case Limon: return "Limon";
        case Naranja: return "Naranja";
        case Pilla: return "Piña";
        case Sandia: return "Sandia";
        case Fresa: return "Fresa";
        case Tamarindo: return "Tamarindo";
        case Coco: return "Coco";
        
        default: return "Desconocido";
        }

    }

    double getCosto() const {return costo;}

    void MostrarInfo() const {

        std::cout<<"Fruta: "<<getNombre()<<", Costo $ "<<costo<<"\n";

    }

  
};
    
//Sin esta linea, el codigo quedaria abierto y el preprocesador no sabria donde termina la proteccion.
#endif //INGREDIENTES_H
