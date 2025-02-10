#ifndef PRODUCTO_H // SI PRODUCTO NO ESTA DEFINIDO
#define PRODUCTO_H // LO DEFINIMOS

#include <iostream>
#include <fstream>
#include <thread>
#include <vector>
#include "Ingrediente.h"

class Producto
{

private:
    std::string nombre;
    int cantidad;
    std::string tipoEnvase;
    double precio;

public:
    //aqui sobrecarga de constructores
    Producto(const std::string& nombre, int cantidad,const std::string& tipoEnvase, double precio)
        : nombre(nombre), cantidad(cantidad), tipoEnvase(tipoEnvase), precio(precio) {}

    Producto(const std::string& nombre,const std::string& tipoEnvase) : nombre(nombre),cantidad(0),tipoEnvase(tipoEnvase),precio(0){}

    void mostrarInfo() const
    {
        std::cout << "Producto: " << nombre << " | Cantidad: " << cantidad
             << " | Envase: " << tipoEnvase << " | Precio: " << precio << "\n";
    }

    virtual ~Producto() {}

    String getNombre() const { return nombre; }
    int getCantidadProducida() const { return cantidad; }

    // Setters (const & en string para evitar copias innecesarias)
    void setNombre(const String &nuevoNombre) { nombre = nuevoNombre; }
    void setCantidadProducida(int nuevaCantidad) { cantidad = nuevaCantidad; }

};

#endif // PRODUCTO_H