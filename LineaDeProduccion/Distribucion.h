#ifndef DISTRIBUCION_H
#define DISTRIBUCION_H
#include <Producto.h>

class Distribucion
{
private:
    std::vector<Producto> pedidos;

public:
    void agregarPedido(const Producto &producto)
    {

        pedidos.push_back(producto);
        
    }

    void mostrarPedidos() const
    {
        std::cout << "\n--- Pedidos en Distribucion ---\n";
        for (const auto &pedido : pedidos)
        {

            pedido.mostrarInfo();

        }
    }

    //aqui una Funcion recursiva para calcular el tiempo estimado de entrega
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