#include <iostream>
#include <conio.h>
#include <string>
#include <string.h>
#include <limits>
#include <stdlib.h>
#include <ctime>
#include <cstdlib> // para seed random
#include <thread>
#include <chrono>  // para sleep_for
#include <set>
#include <vector>

// Cabeceras de tus clases
#include "Empleado.h"
#include "EmpleadoTecnico.h"
#include "EmpleadoOperario.h"
#include "EmpleadoSupervisor.h"
#include "Maquina.h"
#include "MaquinaLavadora.h"
#include "Pasteurizador.h"
#include "Extractor.h"
#include "Frutas.h"
#include "Gestor_De_Planta.h"

using namespace std;


int NumeroValido(std::string mensaje, int minimo, int maximo) {
    int valor;
    while (true) {
        std::cout << mensaje;
        std::cin >> valor;

        if (std::cin.fail() || valor < minimo || valor > maximo) {
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            std::cout << "Error: Entrada no valida. Intente de nuevo.\n";
        } else {
            return valor;
        }
    }
}


vector<string> ObtenerListaDeNombres() {
    return {
        "Carlos Gonzalez", "Maria Lopez", "Juan Martinez", "Ana Rodriguez", "Luis Perez",
        "Elena Sanchez", "Pedro Diaz", "Carmen Vega", "Jose Ruiz", "Sofia Fernandez",
        "Andres Castro", "Raquel Navarro", "Diego Mendoza", "Victoria Jimenez", "Fernando Rojas",
        "Paula Silva", "Jorge Acosta", "Natalia Herrera", "Manuel Morales", "Rosa Torres",
        "Ismael Gutierrez", "Gloria Figueroa", "Roberto Ortega", "Beatriz Paredes", "Daniel Escobar",
        "Gabriela Miranda", "Rodrigo Cabrera", "Martina Castillo", "Sebastian Fuentes", "Clara Rivas",
        "Hugo Salazar", "Valeria Villanueva", "Oscar Delgado", "Lucia Guzman", "Ramiro Peña",
        "Adriana Cardenas", "Victor Solis", "Daniela Campos", "Ricardo Espinoza", "Margarita Montoya",
        "Emilio Nunez", "Estefania Tapia", "Raul Olivares", "Patricia Bermudez", "Julian Serrano",
        "Melissa Duarte", "Alberto Valenzuela", "Lorena Meza", "Francisco Arce", "Renata Ibarra"
    };
}


vector<string> ObtenerNombresAleatorios(int cantidad) {
    vector<string> base = ObtenerListaDeNombres();
    set<int> usados;
    vector<string> resultado;

    while (int(usados.size()) < cantidad) {
        int idx = rand() % base.size();
        if (usados.find(idx) == usados.end()) {
            usados.insert(idx);
            resultado.push_back(base[idx]);
        }
    }
    return resultado;
}


char obtenerRespuestaSN(string mensaje) {
    char respuesta;
    while (true) {
        cout << mensaje;
        cin >> respuesta;
        respuesta = tolower(respuesta);
        if (respuesta == 's' || respuesta == 'n') return respuesta;
        cout << "Entrada invalida. Ingrese 's' para si o 'n' para no.\n";
    }
}

// ---------------------------------------------------------

void ConfigurarParametrosIniciales(Gestor_De_Planta &gestor)
{
    srand((unsigned)time(nullptr)); // Inicializamos semilla random

    // Pedir nombre de la planta (opcional)
    string nombrePlanta;
    cout << "\nIngrese el nombre de la planta: ";
    cin.ignore();
    getline(cin, nombrePlanta);

    double capitalInicial = 10000.0;
    double capitalAdicional = 0.0;

    int aguaLitros = 100; // Agua por defecto
    char respuesta;

    // --- Agregar FRUTAS ---
    while (true)
    {
        respuesta = obtenerRespuestaSN("\n¿Desea agregar frutas a la planta? (s/n): ");
        if (respuesta == 'n') break;

        int opcion = NumeroValido(
            "\nSeleccione una fruta para agregar:\n"
            "1. Limon\n2. Naranja\n3. Piña\n4. Sandia\n5. Fresa\n6. Tamarindo\n7. Coco\n8. Terminar\n"
            "Opcion: ",
            1, 8
        );
        if (opcion == 8) break;

        int cant   = NumeroValido("Ingrese la cantidad de la fruta: ", 1, 1000);
        double prec = NumeroValido("Ingrese el precio por unidad de la fruta: ", 1, 100);

        //  enum es (0=Agua, 1=Limon, 2=Naranja, 3=Piña, etc.)
        
        gestor.agregarFruta(Frutas((Frutas::Fruta)opcion, prec, cant));

        cout << "Se agregaron " << cant << " unidades de la fruta [" << opcion 
             << "] a un precio de $" << prec << "\n";
    }

    // --- Agregar CAPITAL extra (opcional) ---
    char respCapital = obtenerRespuestaSN("\nEl capital inicial de la planta es de $10,000. ¿Desea agregar mas dinero? (s/n): ");
    if (respCapital == 's') {
        capitalAdicional = NumeroValido("Ingrese la cantidad a adicionar: ", 1, 50000);
        capitalInicial += capitalAdicional;
    }

    // --- Agregar EMPLEADOS ---
    int cantEmpleados = NumeroValido("\nIngrese la cantidad de empleados a contratar (maximo 50): ", 1, 50);
    vector<string> nombresGenerados = ObtenerNombresAleatorios(cantEmpleados);

    for (int i = 0; i < cantEmpleados; i++) {
        string nombreEmp = nombresGenerados[i];
        int tipoEmpleado = rand() % 3; // 0=Técnico, 1=Supervisor, 2=Operario
        Empleado* nuevoEmp = nullptr;

        if (tipoEmpleado == 0) {
            nuevoEmp = new EmpleadoTecnico(nombreEmp);
            nuevoEmp->setSalario(2500);
        } else if (tipoEmpleado == 1) {
            nuevoEmp = new EmpleadoSuperVisor(nombreEmp);
            nuevoEmp->setSalario(3500);
        } else {
            nuevoEmp = new EmpleadoOperario(nombreEmp);
            nuevoEmp->setSalario(1800);
        }
        gestor.agregarEmpleado(nuevoEmp);
    }

    // --- Agregar MAQUINAS ---
    // Creamos punteros y setEnUso aleatorio (50%)
    Maquina* ext = new Extractor();
    Maquina* past = new Pasteurizador();
    Maquina* lava = new MaquinaLavadora();

    ext->setEnUso(rand() % 2);
    past->setEnUso(rand() % 2);
    lava->setEnUso(rand() % 2);

    gestor.agregarMaquina(ext);
    gestor.agregarMaquina(past);
    gestor.agregarMaquina(lava);

    // --- Mostrar Resumen ---
    cout << "\n=============================\n";
    cout << "  Configuracion inicial de la planta\n";
    cout << "=============================\n";
    cout << "Nombre de la planta: " << nombrePlanta << "\n";
    cout << "Capital inicial total: $" << capitalInicial << "\n";
    cout << "Agua disponible: " << aguaLitros << " litros\n";

    // Si deseas, mostrar las frutas, empleados y máquinas desde el gestor:
    gestor.ListarFrutas();
    gestor.listarEmpleados();
    gestor.VerEstadoMaquina();
}

// ---------------------------------------------------------
//    Ejecuta las etapas de la simulación usando el gestor
//    con esperas de 15s (3 días) entre cada paso  (ESTO LO PODEMOS CAMBIAR LUEGO)
// ---------------------------------------------------------
void EjecutarSimulacionPasoAPaso(Gestor_De_Planta &gestor) {
    using namespace std::chrono_literals;

    cout << "\n--- Iniciando simulación paso a paso ---\n\n";

    // PASO 1: Lavar Frutas
    cout << "[PASO 1] Lavado de frutas (3 días ~ 15s)...\n";
    gestor.lavarFrutas();
    this_thread::sleep_for(15s);
    cout << "Finalizó la etapa de Lavado.\n\n";

    // PASO 2: Extracción
    cout << "[PASO 2] Extracción del jugo (3 días ~ 15s)...\n";
    gestor.extraerJugo();
    this_thread::sleep_for(15s);
    cout << "Finalizó la etapa de Extracción.\n\n";

    // PASO 3: Pasteurización
    cout << "[PASO 3] Pasteurización (3 días ~ 15s)...\n";
    gestor.pasteurizar();
    this_thread::sleep_for(15s);
    cout << "Finalizó la etapa de Pasteurización.\n\n";

    // PASO 4: Empacado
    cout << "[PASO 4] Empacado (3 días ~ 15s)...\n";
    gestor.empacar();
    this_thread::sleep_for(15s);
    cout << "Finalizó la etapa de Empacado.\n\n";

    cout << "--- Simulación completada ---\n";
}


void MiniMenu(Gestor_De_Planta &gestor) {
    int opcionmini = 0;
    while(opcionmini != 5) {
        cout << "\n----- Mini Menu -----\n";
        cout << "1. Listar Empleados\n";
        cout << "2. Eliminar Empleados\n";
        cout << "3. Listar Frutas\n";
        cout << "4. (Futuro) Eliminar Frutas\n";
        cout << "5. Volver menu Principal\n";
        cout << "Seleccione: ";
        cin >> opcionmini;

        switch(opcionmini) {
            case 1:
                gestor.listarEmpleados();
                break;
            case 2: {
                int idEmpleado = NumeroValido("Ingrese ID del empleado a eliminar: ", 1, 9999);
                gestor.eliminarEmpleado(idEmpleado);
                break;
            }
            case 3:
                gestor.ListarFrutas();
                break;
            case 4:
                // No implementado
                cout << "Eliminar frutas no implementado.\n";
                break;
            case 5:
                cout << "Retornando al menu principal...\n";
                break;
            default:
                cout << "Opcion invalida.\n";
        }
    }
}

// ---------------------------------------------------------
//    Menu Principal
// ---------------------------------------------------------
void MenuPrincipal() {
    // Creamos un Gestor para administrar todo
    Gestor_De_Planta gestor;

    int opcion = 0;
    while (opcion != 6) {
        cout << "\n**Menu**\n";
        cout << "1. Configurar parametros iniciales para la simulacion\n";
        cout << "2. Ejecutar simulacion paso a paso continua\n";
        cout << "3. Generar reportes del estado de la planta\n";
        cout << "4. Guardar y Cargar simulaciones desde archivos\n";
        cout << "5. Ir al MiniMenu (listar/eliminar)\n";
        cout << "6. Salir del programa\n";
        cout << "Escoja una opcion: ";
        cin >> opcion;

        if (opcion == 1) {
            ConfigurarParametrosIniciales(gestor);
        }
        else if (opcion == 2) {
            // Llamamos a la simulacion "paso a paso"
            EjecutarSimulacionPasoAPaso(gestor);
        }
        else if (opcion == 3) {
            // Generar reportes (esto requiere que tengas gestor.generarReporte())
            gestor.generarReporte();
        }
        else if (opcion == 4) {
            // Para guardar/cargar (no implementado en este ejemplo)
            cout << "(Pendiente implementar guardado/carga a archivo)\n";
        }
        else if (opcion == 5) {
            // Llamamos al mini menu
            MiniMenu(gestor);
        }
        else if (opcion == 6) {
            cout << "Proyecto terminado\n";
        }
        else {
            cout << "Opcion no valida\n";
        }
    }
}

// ---------------------------------------------------------
//    main
// ---------------------------------------------------------
int main() {
    MenuPrincipal();
    return 0;
}
