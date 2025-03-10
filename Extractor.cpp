#include "Extractor.h"
#include <iostream>
#include <chrono>
#include <thread>
#include <cstdlib>         
#include "EmpleadoTecnico.h"
#include "NumeroValido.h" 

using namespace std;

Extractor::Extractor() : Maquina("Extractor de Jugo"){}

Extractor::~Extractor(){}


void Extractor::MostrarCronometro(int segundos, const std::string &frutaNombre){

    for (int i = 1; i <= segundos; ++i) {
        mtx.lock();
        
        cout << "Extrayendo jugo de: " << frutaNombre << " - Tiempo transcurrido: " << i << " seg\r";
        cout.flush();

        mtx.unlock();
        this_thread::sleep_for(chrono::seconds(1));

    }

    mtx.lock();
    cout << "Extrayendo jugo de: " << frutaNombre << " - Tiempo transcurrido: " << segundos << " seg\n";

    mtx.unlock();

}

// 25% probabilidad de fallo
bool Extractor::VerificarFallo(){
    return (rand() % 4 == 0);
}

// aqui lo llama un hiloo
void Extractor::ExtraerFruta(const std::string &frutaNombre){
    // simulamos 5 segundos de extracción, luego se puede cambiar
    MostrarCronometro(5, frutaNombre);

}

void Extractor::MenuExtractor(std::vector<Frutas> &inventarioFrutas, std::vector<Empleado*> &empleados, std::vector<Producto> &productos)
{
    int opcion;

    do {

        cout << "\n-- Menu Extractor --\n";
        cout << "1. Extraer Jugo\n";
        cout << "2. Reparar Maquina\n";
        cout << "3. Regresar\n";

        opcion = NumeroValido("Seleccione una opcion: ", 1, 3);

        if (opcion == 1) {
        
            if (!isEnUso()) {
                cout << "El extractor está inoperativo. Debe repararse antes de usar.\n";
                continue;
            }

            // Verificamos si hay frutas
            if (inventarioFrutas.empty()) {
                cout << "No hay frutas en el inventario.\n";
                continue;
            }

            // Listamos las frutas
            cout << "Frutas disponibles:\n";
            for (size_t i = 0; i < inventarioFrutas.size(); ++i) {
                
                cout << i + 1 << ". " << inventarioFrutas[i].getNombre() << " - Cantidad: " << inventarioFrutas[i].getCantidad() << "\n";
            
            }



            int frutaSeleccionada = NumeroValido("Seleccione fruta para extraer jugo: ", 1, inventarioFrutas.size());
            Frutas &f = inventarioFrutas[frutaSeleccionada - 1];

            cout << "Iniciando extraccion de jugo de: " << f.getNombre() << "\n";

            // Lanzamos hilo
            thread hiloExtraccion(&Extractor::ExtraerFruta, this, f.getNombre());
            hiloExtraccion.join();



            // Consumimos 1 unidad
            f.setCantidad(f.getCantidad() - 1);
            if (f.getCantidad() <= 0) {

                inventarioFrutas.erase(inventarioFrutas.begin() + (frutaSeleccionada - 1));
            
            }

            // (cantidad=1, precio=2.0 como ejemplo)
            productos.push_back(Producto("JugoMixto", 1, 2.0));

            
            if (VerificarFallo()) {
                cout << "EL EXTRACTOR SUFRIÓ ALGUNA FALLA. DEBE REPARARSE.\n";

                setEnUso(false);

            } else {

                cout << "Extraccion completada correctamente.\n";
            }

        } else if (opcion == 2) {

            // Reparar
            if (isEnUso()) {

                cout << "La máquina está en buen estado, no necesita reparación.\n";
            } else {

                // Buscar técnicos
                vector<EmpleadoTecnico*> tecnicos;
                for (auto &emp : empleados) {
                    if (auto t = dynamic_cast<EmpleadoTecnico*>(emp)) {

                        tecnicos.push_back(t);
                    }
                }

                // Llamamos a la función de reparación
                EmpleadoTecnico::RepararMaquina(*this, tecnicos);

            }
        } else if (opcion == 3) {
            // Salir
            return;
        }
    } while (opcion != 3);
}
