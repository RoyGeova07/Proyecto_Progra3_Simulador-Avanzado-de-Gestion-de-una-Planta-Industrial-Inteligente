#ifndef ALMACEN_H
#define ALMACEN_H
#include <Producto.h>
#include <MateriaPrima.h>

class Almacen
{
private:
    vector<MateriaPrima> materiasPrimas;
    vector<Producto> productos;

public:

    //aqui sobrecarga de funciones para agregar stock
    void agregarMateriaPrima(const MateriaPrima& materia)
    {
        materiasPrimas.push_back(materia);
    }

    void agregarMateriaPrima(const std::string& nombre, double cantidad,const std::string& unidad){

        materiasPrimas.push_back(MateriaPrima(nombre,cantidad,unidad));

    }

    void agregarProducto(const Producto &producto)
    {
        productos.push_back(producto);
    }

    void agregarProducto(const std::string& nombre,int cantidad,const std::string& tipoEnvase,double precio){

        productos.push_back(Producto(nombre,cantidad,tipoEnvase,precio));

    }

    void mostrarStock() const
    {
        cout << "\n--- Stock de Materias Primas ---\n";
        for (const auto &materia : materiasPrimas)
        {

            materia.mostrarInfo();

        }
        cout << "\n--- Stock de Productos ---\n";
        for (const auto &producto : productos)
        {
            producto.mostrarInfo();
        }
    }
};

#endif ALMACEN_H
