#ifndef PRODUCTO_H // SI PRODUCTO NO ESTA DEFINIDOs
#define PRODUCTO_H // LO DEFINIMOS

#include <iostream>
#include <fstream>
#include <thread>
#include <vector>


class Producto
{
    
private:
    std::string nombre;
    int cantidad;
    double precio;

public:

    enum Jugos{Limonada,JugoNaranja,JugoPilla,JugoSandia,JugoFresa,JugoTamarindo,AguaCoco};

    //aqui sobrecarga de constructores
    Producto(const std::string& nombre, int cantidad, double precio)
        : nombre(nombre), cantidad(cantidad), precio(precio) {}

    Producto(const std::string& nombre) : nombre(nombre),cantidad(0),precio(0){}

    void mostrarInfo() const
    {

        std::cout << "Jugo: " << nombre << " | Cantidad: " << cantidad<< " | Precio: " << precio << "\n";
        
    }

    virtual ~Producto() {}

    std::string getNombre() const { return nombre; }
    int getCantidadProducida() const { return cantidad; }
    int getCantidad() const {return cantidad;}
    double getPrecio() const {return precio;}


    // Setters (const & en string para evitar copias innecesarias)
    void setNombre(const std::string &nuevoNombre) { this->nombre = nuevoNombre; }
    void setCantidadProducida(int nuevaCantidad) { this->cantidad = nuevaCantidad; }

};

#endif // PRODUCTO_H