#ifndef DISTRIBUCION_H
#define DISTRIBUCION_H
#include <Producto.h>

class Distribucion
{
private:
    vector<Producto> pedidos;

public:
    void agregarPedido(const Producto &producto)
    {
        pedidos.push_back(producto);
    }

    void mostrarPedidos() const
    {
        cout << "\n--- Pedidos en Distribución ---\n";
        for (const auto &pedido : pedidos)
        {
            pedido.mostrarInfo();
        }
    }

    // Función recursiva para calcular el tiempo estimado de entrega
    int calcularTiempoEntrega(int pedidosPendientes)
    {
        if (pedidosPendientes <= 0)
        {
            return 0;
        }
        return 2 + calcularTiempoEntrega(pedidosPendientes - 1); // Cada pedido toma 2 unidades de tiempo
    }
};

#endif DISTRIBUCION_H