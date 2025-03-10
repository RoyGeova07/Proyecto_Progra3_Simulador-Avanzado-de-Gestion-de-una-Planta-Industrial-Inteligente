#include "Pasteurizador.h"
#include <iostream>
#include <chrono>
#include <thread>
#include <cstdlib>
#include "EmpleadoTecnico.h"
#include "NumeroValido.h"

using namespace std;

Pasteurizador::Pasteurizador() : Maquina("Pasteurizador"){}

Pasteurizador::~Pasteurizador(){}

// Cronómetro
void Pasteurizador::MostrarCronometro(int segundos, const std::string &productoNombre)
{
    for (int i = 1; i <= segundos; ++i) {
        mtx.lock();
        cout << "Pasteurizando: " << productoNombre << " - Tiempo transcurrido: " << i << " seg\r";

        cout.flush();
        mtx.unlock();

        this_thread::sleep_for(chrono::seconds(1));
    }

    mtx.lock();
    cout << "Pasteurizando: " << productoNombre
         << " - Tiempo transcurrido: " << segundos << " seg\n";
    mtx.unlock();

}

// 25% chance de fallar
bool Pasteurizador::VerificarFallo()
{

    return (rand() % 4 == 0);
}


void Pasteurizador::PasteurizarProducto(const std::string &productoNombre)
{
    
    MostrarCronometro(5, productoNombre);
}

// Menú interactivo
void Pasteurizador::MenuPasteurizador(std::vector<Producto> &productos,
                                      std::vector<Empleado*> &empleados)


{
    int opcion;
    do {


        cout << "\n-- Menu Pasteurizador --\n";
        cout << "1. Pasteurizar Producto\n";
        cout << "2. Reparar Maquina\n";
        cout << "3. Regresar\n";

        opcion = NumeroValido("Seleccione: ", 1, 3);

        if (opcion == 1) {

            if (!isEnUso()) {
                cout << "El pasteurizador está inoperativo. Debe repararse antes de usar.\n";
                continue;

            }

            if (productos.empty()) {
                cout << "No hay productos para pasteurizar.\n";
                continue;

            }

            // Listamos productos
            cout << "Productos disponibles:\n";
            for (size_t i = 0; i < productos.size(); ++i) {
                cout << i + 1 << ". " << productos[i].getNombre()
                     << " - Cantidad: " << productos[i].getCantidad() << "\n";

            }

            int selProd = NumeroValido("Seleccione un producto: ", 1, productos.size());
            Producto &p = productos[selProd - 1];

            cout << "Iniciando pasteurización de: " << p.getNombre() << "\n";

            
            thread hiloPasteur(&Pasteurizador::PasteurizarProducto, this, p.getNombre());
            hiloPasteur.join();

  
            
            p.setCantidadProducida(p.getCantidad() - 1);
            if (p.getCantidad() <= 0) {
                productos.erase(productos.begin() + (selProd - 1));
            }

            // Verificamos fallo
            if (VerificarFallo()) {
                cout << "EL PASTEURIZADOR SUFRIÓ DE ALGUN FALLO. DEBE REPARARSE.\n";
                setEnUso(false);
            } else {
                cout << "Pasteurización completada correctamente.\n";
            }

        } else if (opcion == 2) {

            // Reparar
            if (isEnUso()) {
                cout << "La máquina está en buen estado, no necesita reparación.\n";

            } else {
                vector<EmpleadoTecnico*> tecnicos;

                for (auto &emp : empleados) {

                    if (auto t = dynamic_cast<EmpleadoTecnico*>(emp)) {
                        tecnicos.push_back(t);

                    }
                }
                EmpleadoTecnico::RepararMaquina(*this, tecnicos);
            }

        } else if (opcion == 3) {
            // salir
            return;
        }

    } while (opcion != 3);

}
