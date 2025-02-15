#ifndef ALMACEN_H
#define ALMACEN_H
#include <Producto.h>
#include <Frutas.h>

class Almacen
{
private:
    std::vector<Frutas> frutita;
    Frutas tipo;
    std::vector<Producto> productos;

public:

    //aqui sobrecarga de funciones para agregar stock
    void AgregarFrutas(const Frutas& materia)
    {

        frutita.push_back(materia);
        
    }

    void AgregarFrutas(Frutas nombre, double costo,int cantidad){

        //frutita.push_back(Frutas(nombre,costo,cantidad));

    }

    void agregarProducto(const Producto &producto)
    {
        productos.push_back(producto);
    }

    void agregarProducto(const std::string& nombre,int cantidad,const std::string  &tipoEnvase,double precio){

        productos.push_back(Producto(nombre,cantidad,precio));

    }

    void mostrarStock() const
    {
        std::cout << "\n--- Stock de frutas  ---\n";
        for (const auto &fruts : frutita)
        {

           fruts.MostrarInfo();

        }
        //almacen de de los jugos...
        std::cout << "\n--- Stock de Productos ---\n";
        for (const auto &producto : productos)
        {

            producto.mostrarInfo();
            
        }
    }
};

#endif ALMACEN_H
