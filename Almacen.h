#ifndef ALMACEN_H
#define ALMACEN_H
#include "Producto.h"
#include "Frutas.h"
#include <vector>

class Almacen
{
private:
    std::vector<Frutas> frutita;
    std::vector<Producto> productos;

public:

    //aqui sobrecarga de funciones para agregar stock
    void AgregarFrutas(const Frutas& materia)
    {

        frutita.push_back(materia);
        
    }

    void AgregarFrutas(Frutas::Fruta tipo, double costo,int cantidad){

        frutita.push_back(Frutas(tipo,costo,cantidad));

    }

    void agregarProducto(const Producto &producto)
    {

        productos.push_back(producto);
        
    }

    void agregarProducto(const std::string& nombre,int cantidad,const std::string  &tipoEnvase,double precio){

        productos.push_back(Producto(nombre,cantidad,precio));

    }

};

#endif ALMACEN_H
