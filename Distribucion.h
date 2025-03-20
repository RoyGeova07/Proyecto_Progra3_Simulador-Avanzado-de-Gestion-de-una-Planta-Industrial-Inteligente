#ifndef DISTRIBUCION_H
#define DISTRIBUCION_H

#include "Producto.h"
#include <vector>
#include <string>

class Distribucion
{
private:
    std::vector<Producto> pedidos;  

public:
    // Constructor por defecto
    Distribucion() = default;

    void agregarPedido(const Producto &producto);
    void mostrarPedidos() const;

    int calcularTiempoEntrega(int pedidosPendientes);

    // Genera 'cantidad' pedidos aleatorios
    void generarPedidosAleatorios(int cantidad);
};

#endif // DISTRIBUCION_H
