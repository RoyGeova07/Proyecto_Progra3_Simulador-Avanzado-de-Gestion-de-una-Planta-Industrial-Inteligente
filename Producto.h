#ifndef PRODUCTO_H //SI PRODUCTO NO ESTA DEFINIDO
#define PRODUCTO_H// LO DEFINIMOS

#include <iostream>
#include <fstream>
#include <thread>
#include <vector>
#include "Ingrediente.h"


using String = std::string;

class Producto
{

private:

String nombre;
std::vector<Ingrediente> ingredientes;
int cantidadProducida;
   
public:

    Producto(const String &nombre, int cantidadProducida) : nombre(nombre), cantidadProducida(cantidadProducida){}

    void AgregarIngrediente(const Ingrediente i){

        this->ingredientes.push_back(i);

    }

    void MostrarInfo(){

        std::cout<<"Producto: "<<this->nombre<<" - Cantidad: "<<this->cantidadProducida<<" unidades"<<std::endl;
        std::cout<<"Ingredientes Usados: "<<std::endl;
        for (auto &i : this->ingredientes)
        {
            
            i.MostrarInfo();

        }
        

    }

    String getNombre() const { return nombre; }
    int getCantidadProducida() const { return cantidadProducida; }
    const std::vector<Ingrediente>& getIngredientes() const { return ingredientes; } // Devuelve referencia constante

    // Setters (const & en string para evitar copias innecesarias)
    void setNombre(const String &nuevoNombre) { nombre = nuevoNombre; }
    void setCantidadProducida(int nuevaCantidad) { cantidadProducida = nuevaCantidad; }

   
};


#endif // PRODUCTO_H