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
    void agregarMateriaPrima(const MateriaPrima &materia)
    {
        materiasPrimas.push_back(materia);
    }

    void agregarProducto(const Producto &producto)
    {
        productos.push_back(producto);
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
