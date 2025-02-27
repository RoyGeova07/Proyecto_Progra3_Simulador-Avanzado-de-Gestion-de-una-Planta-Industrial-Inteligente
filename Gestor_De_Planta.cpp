#include "Gestor_De_Planta.h"
#include <iostream>
#include <string>
using namespace std;


Gestor_De_Planta::~Gestor_De_Planta()
{
    // Eliminar empleados
    for (auto emp : empleado) {
        delete emp;
    }
    empleado.clear();

    // Eliminar máquinas
    for (auto m : maquinas) {
        delete m;
    }
    maquinas.clear();
}


void Gestor_De_Planta::agregarFruta(const Frutas &f) {
    FRUTAS.push_back(f);
}

void Gestor_De_Planta::agregarEmpleado(Empleado* emp) {
    empleado.push_back(emp);
}

void Gestor_De_Planta::agregarMaquina(Maquina* m) {
    maquinas.push_back(m);
}

// -----------------------------------------------------
//   LISTAR
// -----------------------------------------------------
void Gestor_De_Planta::listarEmpleados() const {
    if (empleado.empty()) {
        cout << "NO HAY EMPLEADOS EN LA PLANTA\n";
        return;
    }
    cout << "\n--- Lista de Empleados ---\n";
    for (const auto &emp : empleado) {
        emp->MostrarInfo();
    }
}

void Gestor_De_Planta::listarProductos() const {
    if (productos.empty()) {
        cout << "No hay productos en el inventario.\n";
        return;
    }
    cout << "\n--- Lista de Productos ---\n";
    for (const auto &p : productos) {
        p.mostrarInfo();
    }
}

void Gestor_De_Planta::ListarFrutas() const {
    if (FRUTAS.empty()) {
        cout << "No hay frutas en el inventario.\n";
        return;
    }
    cout << "\n--- Lista de Frutas ---\n";
    for (const auto &fruta : FRUTAS) {
        cout << "Nombre: " << fruta.getNombre()
             << " | Cantidad: " << fruta.getCantidad()
             << " | Precio: $" << fruta.getCosto() << endl;
    }
}

void Gestor_De_Planta::VerEstadoMaquina() const {
    if (maquinas.empty()) {
        cout << "No hay maquinas en la planta.\n";
        return;
    }
    cout << "\n--- Estado de las Maquinas ---\n";
    for (const auto &maquina : maquinas) {
        cout << "Máquina: " << maquina->getNombre()
             << " | Estado: "
             << (maquina->isEnUso() ? "Operativa" : "No operativa") << endl;
    }
}

// -----------------------------------------------------
//   ELIMINAR Empleado por ID

void Gestor_De_Planta::eliminarEmpleado(int id) {
    for (auto it = empleado.begin(); it != empleado.end(); ++it) {
        if ((*it)->getId() == id) {
            cout << "Empleado " << (*it)->getNombre() << " eliminado.\n";
            delete *it;           // liberamos memoria
            empleado.erase(it);   // quitamos del vector
            return;
        }
    }
    cout << "No se encontro ningun empleado con ID " << id << ".\n";
}

// -----------------------------------------------------
//   ETAPAS DEL PROCESO PRODUCTIVO

void Gestor_De_Planta::lavarFrutas() {
    // Busca "MaquinaLavadora de Frutas" y revisa si está operativa
    bool lavadoraOperativa = false;
    for (auto &m : maquinas) {
        if (m->getNombre() == "MaquinaLavadora de Frutas" && m->isEnUso()) {
            lavadoraOperativa = true;
            break;
        }
    }
    if (!lavadoraOperativa) {
        logProgreso.push_back("[lavarFrutas] Falló: No hay lavadora operativa.");
        return;
    }

    // Contamos la cantidad de frutas
    int totalFrutas = 0;
    for (auto &f : FRUTAS) {
        totalFrutas += f.getCantidad();
    }
    // Registramos en el log
    logProgreso.push_back("Se lavaron " + to_string(totalFrutas) + " frutas.");
}

void Gestor_De_Planta::extraerJugo() {
    // Busca "Extractor de Jugo"
    bool extractorOperativo = false;
    for (auto &m : maquinas) {
        if (m->getNombre() == "Extractor de Jugo" && m->isEnUso()) {
            extractorOperativo = true;
            break;
        }
    }
    if (!extractorOperativo) {
        logProgreso.push_back("[extraerJugo] Falló: No hay extractor operativo.");
        return;
    }

    // Sumamos cuántas frutas hay
    int totalFrutas = 0;
    for (auto &f : FRUTAS) {
        totalFrutas += f.getCantidad();
        // Opcional: si quieres "consumir" la fruta, haz f.setCantidad(0)
    }
    if (totalFrutas > 0) {
        // Creamos un Producto "JugoMixto" (por ejemplo)
        productos.push_back(Producto("JugoMixto", totalFrutas, 2.0));
        logProgreso.push_back(
            "Se extrajo jugo de " + to_string(totalFrutas) + " frutas."
        );
    } else {
        logProgreso.push_back("No hay frutas para extraer jugo.");
    }
}

void Gestor_De_Planta::pasteurizar() {
    // Busca "Pasteurizador"
    bool pasteurizadorOperativo = false;
    for (auto &m : maquinas) {
        if (m->getNombre() == "Pasteurizador" && m->isEnUso()) {
            pasteurizadorOperativo = true;
            break;
        }
    }
    if (!pasteurizadorOperativo) {
        logProgreso.push_back("[pasteurizar] Falló: No hay pasteurizador operativo.");
        return;
    }

    // Cuenta cuántas unidades de "JugoMixto" hay
    int totalJugo = 0;
    for (auto &prod : productos) {
        if (prod.getNombre() == "JugoMixto") {
            totalJugo += prod.getCantidad();
        }
    }
    if (totalJugo > 0) {
        logProgreso.push_back("Se pasteurizaron " + to_string(totalJugo) + " unidades de jugo.");
    } else {
        logProgreso.push_back("No hay jugo para pasteurizar.");
    }
}

void Gestor_De_Planta::empacar() {
    // Busca cuántas unidades de "JugoMixto" tenemos
    int totalJugo = 0;
    for (auto &prod : productos) {
        if (prod.getNombre() == "JugoMixto") {
            totalJugo += prod.getCantidad();
        }
    }
    if (totalJugo > 0) {
        // Generamos un nuevo Producto "JugoEmpacado"
        productos.push_back(Producto("JugoEmpacado", totalJugo, 3.5));
        logProgreso.push_back("Se empacaron " + to_string(totalJugo) + " unidades de jugo.");
    } else {
        logProgreso.push_back("No hay jugo que empacar.");
    }
}


void Gestor_De_Planta::generarReporte() const {
    if (logProgreso.empty()) {
        cout << "\n[Reporte] No hay acciones registradas.\n";
        return;
    }
    cout << "\n--- Reporte de Actividades ---\n";
    for (const auto &accion : logProgreso) {
        cout << accion << endl;
    }
    cout << "-----------------------------\n";
}
