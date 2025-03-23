#ifndef DISTRIBUCION_H
#define DISTRIBUCION_H

#include "Producto.h"
#include "NumeroValido.h"
#include <vector>
#include <map>
#include <string>
#include <chrono>
#include <algorithm>
#include <cstdlib>
#include <atomic>
#include <thread>

//ERRO DE CIRCULO DE DEPENDENCIAAASSSS  
class Gestor_De_Planta;

class Distribucion {
private:

    Gestor_De_Planta* gestorReferencia;
    //uso el map porque cada pedido tiene varios tipos de jugos con diferentes cantidades 
    /*
    {
        "Limon" : 3,
        "Coco" : 1,
        "Tamarindo" : 2
    }
    
    */
    //para representar estos jugos uso map, porque podemos buscar el nombre directamente(pedido["Limon"])
    //tambien es bueno porque se evita los duplicados, si se agrega 2 veces el mismo jugo, solo se suma la cantidad 
    //y es mas flexible y ordenado para trabajar con datos tipo "nombre → cantidad"
    std::vector<std::map<std::string, int>> pedidosPendientes;

    //este lo uso para medir el tiempo que ha pasado desde la ultima vez que se generaron los pedidos 
    //para que se pueda controlar si no hay pedidos, se regeneran automaticamente luego de 15 segundos 
    //uso steady_lock porque no se ve afectado por cambios en el reloj del sistema 
    // y siempre avanza a una velocidad constante y es buenisima para medir la duracion 
    std::chrono::steady_clock::time_point tiempoUltimoPedido;
    std::thread hiloGeneradorPedidos;
    std::atomic<bool> activo;  // para controlar si el hilo sigue corriendo


public:
    Distribucion();
    ~Distribucion();

    void verificarRegeneracionPedidos();
    void generarPedidosAleatorios();
    void mostrarPedidosDisponibles();
    bool verificarDisponibilidad(const std::map<std::string, int>& pedido, const std::vector<Producto>& jugos);
    void procesarPedido(Gestor_De_Planta& gestor, int indice);
    int calcularTiempoEntrega(int pedidosPendientes);
    void mostrarMenuPedidos(Gestor_De_Planta& gestor);
    double calcularPrecioPedido(const std::map<std::string,int>& pedido,const std::vector<Producto>& jugosDisponibles);
    void setGestor(Gestor_De_Planta* gestor){

        this->gestorReferencia=gestor;

    }


};


#endif // DISTRIBUCION_H

