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
    int CantidadJugosSinIngredientes;

public:

    enum Jugos{Limonada,JugoNaranja,JugoPilla,JugoSandia,JugoFresa,JugoTamarindo,AguaCoco};

    //aqui sobrecarga de constructores
    Producto(const std::string& nombre, int cantidad, double precio)
        : nombre(nombre), cantidad(cantidad), precio(precio) {}

    Producto(const std::string& nombre) : nombre(nombre),cantidad(cantidad),precio(precio),CantidadJugosSinIngredientes(cantidad){}

    void mostrarInfo() const
    {

        std::cout << "Jugo: " << nombre << " | Cantidad: " << cantidad<< " | Precio: " << precio << "\n";
        
    }


    virtual ~Producto() {}

    std::string getNombre() const { return nombre; }
    int getCantidadProducida() const { return cantidad; }
    int getCantidad() const {return cantidad;}
    int getCantidadSinIngredientes()const{return CantidadJugosSinIngredientes;}
    void setCantidadSinIngredientes(int NuevaCantidadJugosSinIngredientes){this->CantidadJugosSinIngredientes=NuevaCantidadJugosSinIngredientes;}
    double getPrecio() const {return precio;}

    bool hayJugosSinIngredientes()const{return CantidadJugosSinIngredientes>0;}

    // Setters (const & en string para evitar copias innecesarias)
    void setNombre(const std::string &nuevoNombre) { this->nombre = nuevoNombre; }
    void setCantidadProducida(int nuevaCantidad) { this->cantidad = nuevaCantidad; }

    void DecrementarJugosSinIngredientes(int CantidadProcesada){
        
        if(CantidadJugosSinIngredientes>=CantidadProcesada){

            CantidadJugosSinIngredientes-=CantidadProcesada;

        }else{

            CantidadJugosSinIngredientes=0;

        }

    }

};

#endif // PRODUCTO_H