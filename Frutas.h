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

    static Fruta ObtenerFrutaDesdeNombre(const std::string& nombre) {
        if(nombre == "Agua") return Frutas::Agua;
        if(nombre == "Limon") return Frutas::Limon;
        if(nombre == "Naranja") return Frutas::Naranja;
        if(nombre == "Piña") return Frutas::Pilla;
        if(nombre == "Sandia") return Frutas::Sandia;
        if(nombre == "Fresa") return Frutas::Fresa;
        if(nombre == "Tamarindo") return Frutas::Tamarindo;
        if(nombre == "Coco") return Frutas::Coco;
        return Frutas::Agua; // por defecto
    }

private:

    bool lavada=false;
    Fruta tipo;
    int CantidadLavada;//contador que me ayuda a contar las frutas ya lavadas
    double costo;
    int cantidad;

public:

    
    //constructor
    // en C++ es mejor inicializar los atributos directamente en la lista de inicializacion
    Frutas(Fruta tipo, double costo,int cantidad) : tipo(tipo),costo(costo), cantidad(cantidad),CantidadLavada(0) {}

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
    int getCantidad() const {return cantidad;}
    int getCantidadLavada()const {return CantidadLavada;}
    void setLavada(bool estado) {lavada=estado;}
    void setCantidadLavada(int NuevaCantidad) {CantidadLavada=NuevaCantidad;}
    
    bool isLavada()const{return lavada;}
    
    void setCantidad(int nuevaCantidad) {
        
        this->cantidad=nuevaCantidad;
        
    }
    void setCosto(int NuevoCosto){

        this->costo=NuevoCosto;

    }

    void IncrementarLavada(){

        if (cantidad>0)
        {
            
            CantidadLavada++;

        }
        

    }

    bool hayFrutasLavadas()const{return CantidadLavada>0;}

    void DecrementarLavada(int cantidad){

        if (CantidadLavada>=cantidad)
        {
            
            CantidadLavada-=cantidad;

        }else{
        
            CantidadLavada=0;//esto para evitar valores negativos

        }
        

    }

    void MostrarInfo() const {

        std::cout<<"Fruta: "<<getNombre()<<", Unidades $ "<<cantidad<<"\n";

    }

  
};
    
//Sin esta linea, el codigo quedaria abierto y el preprocesador no sabria donde termina la proteccion.
#endif //INGREDIENTES_H
