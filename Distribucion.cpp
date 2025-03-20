#include "Distribucion.h"
#include <iostream>
#include <cstdlib>  
#include <ctime>    

using namespace std;

// Agrega un producto al vector de pedidos
void Distribucion::agregarPedido(const Producto &producto)
{
    pedidos.push_back(producto);
}

// Muestra los pedidos
void Distribucion::mostrarPedidos() const
{
    cout << "\n--- Pedidos en Distribucion ---\n";
    if (pedidos.empty()) {
        cout << "No hay pedidos.\n";
        return;
    }
    for (const auto &pedido : pedidos)
    {
        pedido.mostrarInfo();  // Asumiendo que Producto::mostrarInfo() imprime datos
    }
}

// Calcula el tiempo de entrega recursivamente
int Distribucion::calcularTiempoEntrega(int pedidosPendientes)
{
    if (pedidosPendientes <= 0) {
        return 0;
    }
    // Cada pedido toma 2 unidades de tiempo
    return 2 + calcularTiempoEntrega(pedidosPendientes - 1);
}

// Genera 'cantidad' pedidos aleatorios con los productos de la tienda 
void Distribucion::generarPedidosAleatorios(int cantidad)
{
    
    srand(static_cast<unsigned>(time(nullptr)));


    for (int i = 0; i < cantidad; ++i) {
        int tipo = 1 + (rand() % 10); 
        int cant = 1 + (rand() % 20); 

        double precioUnit = 0.0;
        string nombre;

        switch (tipo) {
            case 1: nombre = "Limon";       precioUnit = 2.4; break;
            case 2: nombre = "Naranja";     precioUnit = 3.4; break;
            case 3: nombre = "Pina";        precioUnit = 5.6; break;
            case 4: nombre = "Sandia";      precioUnit = 7.8; break;
            case 5: nombre = "Fresa";       precioUnit = 2.0; break;
            case 6: nombre = "Tamarindo";   precioUnit = 4.0; break;
            case 7: nombre = "Coco";        precioUnit = 2.1; break;
            case 8: nombre = "Conservante"; precioUnit = 3.0; break;
            case 9: nombre = "Envases";     precioUnit = 7.0; break;
            case 10:nombre = "Agua";        precioUnit = 5.0; break;
        }


        double precio = precioUnit;

        Producto nuevoPedido(nombre, cant, precio);

        pedidos.push_back(nuevoPedido);
    }

    cout << "Se generaron " << cantidad << " pedidos aleatorios.\n";
}
