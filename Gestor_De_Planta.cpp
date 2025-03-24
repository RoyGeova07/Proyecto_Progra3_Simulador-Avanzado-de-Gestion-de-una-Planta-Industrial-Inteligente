#include <iostream>
#include <fstream>
#include <algorithm>
#include <sstream>
#include <vector>
#include <string>
#include <iosfwd>
#include <filesystem>  // <-- Para crear la carpeta y manipular archivos
#include "Gestor_De_Planta.h"
#include "Producto.h"
#include "Empleado.h"
#include "EmpleadoOperario.h"
#include "EmpleadoTecnico.h"
#include "NumeroValido.h"
#include "Maquina.h"
#include "Distribucion.h"
#include "Tienda.h"

namespace fs = std::filesystem;
using namespace std;

// Constructor
Gestor_De_Planta::Gestor_De_Planta()
{
    distribucion = new Distribucion();
    distribucion->setGestor(this);
    tiendita = new Tienda();
}

// Destructor
Gestor_De_Planta::~Gestor_De_Planta()
{
    delete distribucion;
    delete tiendita;
    for (auto emp : empleado) delete emp;
    empleado.clear();
}

//------------------------------------------------------------------------------

void Gestor_De_Planta::ReducirAgua(double litros)
{
    if (AguaLitros >= litros) {
        AguaLitros -= litros;
    } else {
        AguaLitros = 0;  // evita que sea negativo
    }
}

void Gestor_De_Planta::AgregarEmpleado(Empleado* emp)
{
    empleado.push_back(emp);
}

void Gestor_De_Planta::listarEmpleados() const
{
    if (empleado.empty()) {
        cout << "NO HAY EMPLEADOS EN LA PLANTA\n";
        return;
    }

    cout << "\n--- Lista de Empleados ---\n";
    for (const auto &emp : empleado) {
        emp->MostrarInfo();
    }
}

void Gestor_De_Planta::listarProductos() const
{
    if (productos.empty()) {
        cout << "No hay productos en el inventario." << endl;
        return;
    }

    cout << "\n--- Lista de Productos ---\n";
    for (const auto &producto : productos) {
        producto.mostrarInfo();
    }
}

void Gestor_De_Planta::ListarFrutas() const
{
    if (FRUTAS.empty()) {
        cout << "No hay frutas en el inventario." << endl;
        return;
    }

    cout << "\n--- Lista de Frutas ---\n";
    for (const auto &fruta : FRUTAS) {
        cout << "Nombre: " << fruta.getNombre()
             << " | Cantidad: " << fruta.getCantidad()
             << " | Precio: $" << fruta.getCosto() << endl;
    }
}

void Gestor_De_Planta::VerEstadoMaquina() const
{
    if (maquinas.empty()) {
        cout << "No hay maquinas en la planta." << endl;
        return;
    }

    cout << "\n--- Estado de las Maquinas ---\n";
    for (const auto &maquina : maquinas) {
        maquina->VerEstadoMaquina();  // Polimórfica
    }
}

void Gestor_De_Planta::TransferirFrutaLavada(const Frutas& frutaLavada)
{
    for (auto &fruta : FRUTAS_LAVADAS) {
        if (fruta.getNombre() == frutaLavada.getNombre()) {
            fruta.setCantidad(fruta.getCantidad() + frutaLavada.getCantidad());
            // Podemos actualizar costo si se requiere
            fruta.setCosto(frutaLavada.getCosto());
            return;
        }
    }
    // Si no está, la añadimos
    FRUTAS_LAVADAS.push_back(frutaLavada);
}

void Gestor_De_Planta::ListarFrutasLavadas() const
{
    if (FRUTAS_LAVADAS.empty()) {
        cout << "No hay frutas lavadaaaas\n";
        return;
    }

    cout << "\n--- Lista de Frutas Lavadas ---\n";
    for (const auto &fruta : FRUTAS_LAVADAS) {
        cout << "Nombre: " << fruta.getNombre()
             << " | Cantidad Lavada: " << fruta.getCantidad()
             << " | Precio: $" << fruta.getCosto() << endl;
    }
}

void Gestor_De_Planta::eliminarEmpleado(int id)
{
    auto es = find_if(empleado.begin(), empleado.end(), [id](Empleado* emp) {
        return emp->getId() == id;
    });

    if (es != empleado.end()) {
        cout << "\n**Empleado " << (*es)->getNombre() << " ha sido despedido.**\n";
        EMPLEADOS_DESPEDIDOS.push_back((*es)->getNombre());  // Registramos nombre del despedido
        delete *es;
        empleado.erase(es);
    } else {
        cout << "No se encontro ningun empleado con el ID " << id << ".\n";
    }
}

Empleado* Gestor_De_Planta::BuscarEmpleadoPorId(int id)
{
    for (Empleado* emp : empleado) {
        if (emp->getId() == id) {
            return emp;
        }
    }
    return nullptr;
}

int Gestor_De_Planta::CantidadEmpleados() const
{
    return empleado.size();
}

void Gestor_De_Planta::AgregarFruta(const Frutas& fruta)
{
    for (auto &EstaDuplicadoEl : FRUTAS) {
        if (EstaDuplicadoEl.getNombre() == fruta.getNombre()) {
            // Si ya existe, sumamos cantidades
            EstaDuplicadoEl.setCantidad(EstaDuplicadoEl.getCantidad() + fruta.getCantidad());
            // Actualizamos el costo
            EstaDuplicadoEl.setCosto(fruta.getCosto());
            return;
        }
    }
    // Si no está, se agrega
    FRUTAS.push_back(fruta);
}

void Gestor_De_Planta::AgregarMaquina(Maquina* maq)
{
    maquinas.push_back(maq);
}

void Gestor_De_Planta::AgregarJugosSinIngredientesYEnvases(const Producto &jugo)
{
    for (auto &JugoCreado : JUGOS_SIN_INGREDIENTES) {
        if (JugoCreado.getNombre() == jugo.getNombre()) {
            JugoCreado.setCantidadSinIngredientes(
                JugoCreado.getCantidadSinIngredientes() + jugo.getCantidadSinIngredientes()
            );
            return;
        }
    }
    // Si no existe en la lista, lo agregamos
    Producto NuevoJugo(jugo.getNombre(), jugo.getCantidadProducida(), jugo.getPrecio());
    NuevoJugo.setCantidadSinIngredientes(jugo.getCantidadProducida());
    JUGOS_SIN_INGREDIENTES.push_back(NuevoJugo);
}

void Gestor_De_Planta::AgregarJugosDisponibles(const Producto &jugo, int cantidad)
{
    for (auto &JugoFinal : JUGOS_DISPONIBLES) {
        if (JugoFinal.getNombre() == jugo.getNombre()) {
            JugoFinal.setCantidadProducida(JugoFinal.getCantidadProducida() + cantidad);
            return;
        }
    }
    // Si no existe, creamos uno nuevo
    Producto NuevoJugo(jugo.getNombre(), cantidad, jugo.getPrecio());
    JUGOS_DISPONIBLES.push_back(NuevoJugo);
}

void Gestor_De_Planta::ListaJugosDisponibles() const
{
    if (JUGOS_DISPONIBLES.empty()) {
        cout << "\nNo hay jugos disponibles para la venta.\n";
        return;
    }

    cout << "\n -- Jugos Disponibles para la venta -- \n";
    for (const auto &jugo : JUGOS_DISPONIBLES) {
        cout << "Jugo: " << jugo.getNombre()
             << " - Cantidad Disponible: " << jugo.getCantidad()
             << " - Precio: $" << jugo.getPrecio() << "\n.";
    }
}

void Gestor_De_Planta::ListaJugosFaltanIngredientesYEnvases() const
{
    if (JUGOS_SIN_INGREDIENTES.empty()) {
        cout << "No hay jugos sin ingredientes aun\n";
        return;
    }
    cout << "\n -- Jugos sin Ingredientes -- \n";
    for (const auto &JugosSinSabor : JUGOS_SIN_INGREDIENTES) {
        cout << "Jugo: " << JugosSinSabor.getNombre()
             << " Cantidad: " << JugosSinSabor.getCantidadProducida()
             << " - Sin Ingredientes\n";
    }
}

void Gestor_De_Planta::EliminarJugoSinIngredientes(const string &NombreJugo)
{
    auto messi = remove_if(
        JUGOS_SIN_INGREDIENTES.begin(),
        JUGOS_SIN_INGREDIENTES.end(),
        [&NombreJugo](const Producto &j) {
            return j.getNombre() == NombreJugo;
        }
    );
    if (messi != JUGOS_SIN_INGREDIENTES.end()) {
        JUGOS_SIN_INGREDIENTES.erase(messi, JUGOS_SIN_INGREDIENTES.end());
    }
}

// Función auxiliar
char ObtenerCocaCola(string mensaje)
{
    string cocacola;
    char respuestagod;
    while (true) {
        cout << mensaje;
        getline(cin, cocacola);
        if (cocacola.empty()) continue;
        respuestagod = tolower(cocacola[0]);
        if (respuestagod == 's' || respuestagod == 'n') return respuestagod;
        cout << "Entrada invalida. Ingrese 's' para si o 'n' para no.\n";
    }
}

template <typename T>
T NumeroTypename(string mensaje, T minimoComumMultiplo, T MaximoComunMultiplo)
{
    T valorEquis;
    string hitler;
    char variableExtra;
    while (true) {
        cout << mensaje;
        getline(cin, hitler);
        istringstream iss(hitler);

        if (!(iss >> valorEquis)) {
            cout << "Error: Entrada no valida. Intente de nuevo.\n";
            continue;
        }
        if (iss >> variableExtra) {
            cout << "Error: Entrada no valida. Intente de nuevo.\n";
            continue;
        }
        if (valorEquis < minimoComumMultiplo || valorEquis > MaximoComunMultiplo) {
            cout << "Error: Entrada fuera de rango. Intente de nuevo.\n";
            continue;
        }
        return valorEquis;
    }
}

void Gestor_De_Planta::MiniMenuGestor(Gestor_De_Planta &gestor)
{
    int opcionmini = 0;

    // Cambiamos la condición y el rango de opciones para que podamos tener hasta la 11.
    while (opcionmini != 11)
    {
        cout << "\n====================Menu de la planta====================\n";
        cout << "1. Listar Planta\n";
        cout << "2. Despedir Empleados\n";
        cout << "3. Espacio de Maquinas\n";
        cout << "4. Comprar Frutas\n";
        cout << "5. Ver pedidos\n";
        cout << "6. Generar reporte de la planta de " << gestor.getNombrePLanta() << "\n";
        cout << "7. Ver reporte de la planta de " << gestor.getNombrePLanta() << "\n";
        cout << "8. Pedir billete\n";
        cout << "9. Guardar Simulacion\n";
        cout << "10. Cargar Simulacion\n";
        cout << "11. Salir de mi planta\n";

        // Ahora permitimos opciones del 1 al 11
        opcionmini = NumeroValido("Ingrese una opcion: ", 1, 11);

        if (opcionmini == 1)
        {
            cout << "===============================================================\n";
            cout << "\nEmpleados activos:\n ";
            listarEmpleados();

            cout << "----------------------------------------------------------------\n";
            cout << "\nNombre de la planta: " << getNombrePLanta() << "\n";
            cout << "----------------------------------------------------------------\n";

            cout << "\nFrutas en inventario:\n";
            ListarFrutas();

            cout << "----------------------------------------------------------------\n";
            cout << "\nCapital: $" << getCapital() << "\n";
            cout << "----------------------------------------------------------------\n";

            cout << "\nFrutas lavadas en general:\n";
            ListarFrutasLavadas();

            cout << "----------------------------------------------------------------\n";
            cout << "\nJugos sin Ingredientes y envases por Agregar:\n";
            ListaJugosFaltanIngredientesYEnvases();

            cout << "----------------------------------------------------------------\n";
            cout << "\nJugos Disponibles:\n";
            ListaJugosDisponibles();

            cout << "----------------------------------------------------------------\n";
            cout << "\nAgua disponible: " << getAgua() << " litros\n";
            cout << "----------------------------------------------------------------\n";
            cout << "\nConservantes disponibles: " << getConservantes() << " unidades\n";
            cout << "----------------------------------------------------------------\n";
            cout << "\nEnvases disponibles: " << getEnvases() << " unidades\n";
            cout << "----------------------------------------------------------------\n";
            cout << "\nEstado de las maquinas actualmente:\n";
            VerEstadoMaquina();
            cout << "====================================================================\n";
        }
        else if (opcionmini == 2)
        {
            cout << "======================================================================\n";
            cout << "***seleccione 51 para salir****\n";
            cout << "\nEmpleados activos:\n ";
            listarEmpleados();
            cout << "---Nota-- Presione 51 para volver al menu\n";
            int id = NumeroValido("Ingrese el ID del empleado a despedir: ", 1, 51);

            if (id == 51) {
                // Vuelves al menú principal
                continue;
            }

            eliminarEmpleado(id);
            listarEmpleados();
        }
        else if (opcionmini == 3)
        {
            // Menú de Maquinas
            Maquina::MenuMaquinas(*this);
        }
        else if (opcionmini == 4)
        {
            // Menú de compras en la Tienda
            getTienda().MenuTienda(*this);
        }
        else if (opcionmini == 5)
        {
            // Pedidos pendientes de Distribución
            if (!distribucion) {
                distribucion = new Distribucion();
                distribucion->setGestor(this);
            }
            distribucion->mostrarMenuPedidos(*this);
        }
        else if (opcionmini == 6)
        {
            // Generar Reporte
            EmpleadoOperario dummy(""); 
            dummy.GenerarReportePlantaConHilos(*this, this->getEmpleados());
        }
        else if (opcionmini == 7)
        {
            // Ver Reporte en pantalla
            string carpeta = "Plantas Industriales";
            string archivo = carpeta + "/" + gestor.getNombrePLanta() + ".txt";
            ifstream reporte(archivo);

            if (!reporte.is_open()) {
                cout << "\n No se encontrado un reporte de esta planta.\n";
            } else {
                cout << "\n==========  CONTENIDO DEL REPORTE ==========\n";
                string linea;
                while (getline(reporte, linea)) {
                    cout << linea << "\n";
                }
                cout << "\n==========  FIN DEL REPORTE ==========\n";
                reporte.close();
            }
        }
        else if (opcionmini == 8)
        {
            // Agregar capital manualmente
            char respuestagod;
            double CapitalAdicional;
            respuestagod = ObtenerCocaCola("\nDesea agregar mas dinero? (s/n): ");
            if (respuestagod == 's' || respuestagod == 'S') {
                CapitalAdicional = NumeroTypename("Ingrese la cantidad a adicionar: ", 1.0, 50000.0);
                gestor.agregarCapital(CapitalAdicional);
            }
        }
        else if (opcionmini == 9)
        {
            // Guardar Simulación
            string archivoBin;
            cout << "\nIngrese el nombre del archivo binario (ej: miplanta.bin): ";
            getline(cin, archivoBin);
            if (archivoBin.empty()) {
                archivoBin = "SimulacionPlanta.bin";
            }
            GuardarSimulacionBinario(archivoBin);
        }
        else if (opcionmini == 10)
        {
            // Cargar Simulación
            string archivoBin;
            cout << "\nIngrese el nombre del archivo binario a cargar (ej: miplanta.bin): ";
            getline(cin, archivoBin);
            if (archivoBin.empty()) {
                archivoBin = "SimulacionPlanta.bin";
            }
            CargarSimulacionBinario(archivoBin);
        }
        else if (opcionmini == 11)
        {
            // Salir
            cout << "Saliendo de mi planta\n";
        }
        else
        {
            cout << "opcion no valida\n";
        }
    }
}


//------------------------------------------------------------------------------
// NUEVAS FUNCIONES PARA GUARDAR Y CARGAR LA SIMULACIÓN EN BINARIO
//------------------------------------------------------------------------------

void Gestor_De_Planta::GuardarSimulacionBinario(const std::string &nombreArchivo)
{
    // 1) Crear/verificar la carpeta
    std::string carpeta = "Plantas Industriales guardadas";
    if(!fs::exists(carpeta)) {
        fs::create_directory(carpeta);
    }

    // 2) Construir la ruta completa (carpeta + archivo)
    std::string ruta = carpeta + "/" + nombreArchivo;

    // 3) Abrir archivo binario
    std::ofstream archivo(ruta, std::ios::binary);
    if(!archivo.is_open()) {
        std::cerr << "Error al abrir el archivo binario para guardar la simulacion.\n";
        return;
    }

    // a) Guardar nombre de la planta
    {
        size_t len = NombreDelaPlanta.size();
        archivo.write(reinterpret_cast<const char*>(&len), sizeof(len));
        archivo.write(NombreDelaPlanta.c_str(), len);
    }

    // b) Guardar capital, agua, conservantes, envases
    archivo.write(reinterpret_cast<const char*>(&CapitalInicial), sizeof(CapitalInicial));
    archivo.write(reinterpret_cast<const char*>(&AguaLitros),     sizeof(AguaLitros));
    archivo.write(reinterpret_cast<const char*>(&Conservantes),   sizeof(Conservantes));
    archivo.write(reinterpret_cast<const char*>(&Envases),        sizeof(Envases));

    // c) Guardar FRUTAS
    {
        size_t totalFrutas = FRUTAS.size();
        archivo.write(reinterpret_cast<const char*>(&totalFrutas), sizeof(totalFrutas));
        for(const auto &f : FRUTAS)
        {
            // Necesitamos mapear getNombre() a un int enum
            int tipoInt = -1;
            // Ejemplo de mapeo básico:
            if(f.getNombre() == "Agua")       tipoInt = 0;
            else if(f.getNombre() == "Limon") tipoInt = 1;
            else if(f.getNombre() == "Naranja") tipoInt = 2;
            else if(f.getNombre() == "Piña")  tipoInt = 3;
            else if(f.getNombre() == "Sandia") tipoInt = 4;
            else if(f.getNombre() == "Fresa")  tipoInt = 5;
            else if(f.getNombre() == "Tamarindo") tipoInt = 6;
            else if(f.getNombre() == "Coco")  tipoInt = 7;

            archivo.write(reinterpret_cast<const char*>(&tipoInt), sizeof(tipoInt));
            double costo = f.getCosto();
            archivo.write(reinterpret_cast<const char*>(&costo), sizeof(costo));
            int cantidad = f.getCantidad();
            archivo.write(reinterpret_cast<const char*>(&cantidad), sizeof(cantidad));
            int cLavada = f.getCantidadLavada();
            archivo.write(reinterpret_cast<const char*>(&cLavada), sizeof(cLavada));
        }
    }

    // d) Guardar Empleados
    {
        size_t totalEmp = empleado.size();
        archivo.write(reinterpret_cast<const char*>(&totalEmp), sizeof(totalEmp));
        for(auto *emp : empleado)
        {
            if(dynamic_cast<EmpleadoOperario*>(emp)) {
                int tipoEmp = 0; // operario
                archivo.write(reinterpret_cast<const char*>(&tipoEmp), sizeof(tipoEmp));
            }
            else if(dynamic_cast<EmpleadoTecnico*>(emp)) {
                int tipoEmp = 1; // tecnico
                archivo.write(reinterpret_cast<const char*>(&tipoEmp), sizeof(tipoEmp));
            }
            else {
                int tipoEmp = 9; // desconocido
                archivo.write(reinterpret_cast<const char*>(&tipoEmp), sizeof(tipoEmp));
            }

            // Guardar nombre
            std::string nom = emp->getNombre();
            size_t lenNom = nom.size();
            archivo.write(reinterpret_cast<const char*>(&lenNom), sizeof(lenNom));
            archivo.write(nom.c_str(), lenNom);

            // Guardar cargo
            std::string cargo = emp->getCargo();
            size_t lenCargo = cargo.size();
            archivo.write(reinterpret_cast<const char*>(&lenCargo), sizeof(lenCargo));
            archivo.write(cargo.c_str(), lenCargo);

            // Guardar id, salario, dineroGanado
            int id = emp->getId();
            archivo.write(reinterpret_cast<const char*>(&id), sizeof(id));

            int salario = emp->getSalario();
            archivo.write(reinterpret_cast<const char*>(&salario), sizeof(salario));

            int dineroGanado = emp->getDineroGanado();
            archivo.write(reinterpret_cast<const char*>(&dineroGanado), sizeof(dineroGanado));
        }
    }


    archivo.close();
    cout << "\nSimulacion guardada exitosamente en: " << ruta << "\n";
}

void Gestor_De_Planta::CargarSimulacionBinario(const std::string &nombreArchivo)
{
    std::string carpeta = "Plantas Industriales guardadas";
    std::string ruta = carpeta + "/" + nombreArchivo;

    std::ifstream archivo(ruta, std::ios::binary);
    if(!archivo.is_open()) {
        std::cerr << "Error al abrir el archivo binario para cargar la simulacion.\n";
        return;
    }

    // Limpiamos para no mezclar con datos anteriores
    empleado.clear();
    FRUTAS.clear();
    FRUTAS_LAVADAS.clear();
    JUGOS_SIN_INGREDIENTES.clear();
    JUGOS_DISPONIBLES.clear();
    // Maquinas y demas, segun si quieres re-crearlas desde cero

    // a) Leer nombre planta
    {
        size_t len = 0;
        archivo.read(reinterpret_cast<char*>(&len), sizeof(len));
        std::string nombrePlanta;
        nombrePlanta.resize(len);
        archivo.read(&nombrePlanta[0], len);
        NombreDelaPlanta = nombrePlanta;
    }

    // b) Leer capital, agua, etc.
    archivo.read(reinterpret_cast<char*>(&CapitalInicial), sizeof(CapitalInicial));
    archivo.read(reinterpret_cast<char*>(&AguaLitros),     sizeof(AguaLitros));
    archivo.read(reinterpret_cast<char*>(&Conservantes),   sizeof(Conservantes));
    archivo.read(reinterpret_cast<char*>(&Envases),        sizeof(Envases));

    // c) Leer FRUTAS
    {
        size_t totalFrutas = 0;
        archivo.read(reinterpret_cast<char*>(&totalFrutas), sizeof(totalFrutas));
        for(size_t i=0; i<totalFrutas; i++) {
            int tipoInt;
            archivo.read(reinterpret_cast<char*>(&tipoInt), sizeof(tipoInt));

            double costo;
            archivo.read(reinterpret_cast<char*>(&costo), sizeof(costo));

            int cantidad;
            archivo.read(reinterpret_cast<char*>(&cantidad), sizeof(cantidad));

            int cLavada;
            archivo.read(reinterpret_cast<char*>(&cLavada), sizeof(cLavada));

            // Reconstruimos la fruta según tu enum
            // Por simplicidad, lo mapeamos al constructor: Frutas(Fruta tipo, double costo, int cantidad)
            // Y su setCantidadLavada(cLavada)
            Frutas::Fruta enumTipo = (Frutas::Fruta)tipoInt;
            Frutas f(enumTipo, costo, cantidad);
            f.setCantidadLavada(cLavada);

            FRUTAS.push_back(f);
        }
    }

    // d) Leer Empleados
    {
        size_t totalEmp = 0;
        archivo.read(reinterpret_cast<char*>(&totalEmp), sizeof(totalEmp));
        for(size_t i=0; i<totalEmp; i++) {
            int tipoEmp = 0;
            archivo.read(reinterpret_cast<char*>(&tipoEmp), sizeof(tipoEmp));

            size_t lenNom;
            archivo.read(reinterpret_cast<char*>(&lenNom), sizeof(lenNom));
            std::string nom; nom.resize(lenNom);
            archivo.read(&nom[0], lenNom);

            size_t lenCargo;
            archivo.read(reinterpret_cast<char*>(&lenCargo), sizeof(lenCargo));
            std::string cargo; cargo.resize(lenCargo);
            archivo.read(&cargo[0], lenCargo);

            int id, salario, dineroGanado;
            archivo.read(reinterpret_cast<char*>(&id),         sizeof(id));
            archivo.read(reinterpret_cast<char*>(&salario),    sizeof(salario));
            archivo.read(reinterpret_cast<char*>(&dineroGanado), sizeof(dineroGanado));

            Empleado* nuevo = nullptr;
            if(tipoEmp == 0) {
                nuevo = new EmpleadoOperario(nom);  // cargo = "EmpleadoOperario"
            }
            else if(tipoEmp == 1) {
                nuevo = new EmpleadoTecnico(nom);   // cargo = "Tecnico de Mantenimiento"
            }
            else {
                // si tuvieras mas subclases, etc.
                cerr << "Tipo de empleado desconocido: " << tipoEmp << "\n";
                // Podrías continuar o hacer break
                continue;
            }

            // Rellenamos info extra
            // Ojo: no tenemos setId() en tu clase. 
            // Podrías ignorar ID o bien hacer un setId si lo implementas.
            nuevo->setSalario(salario);
            nuevo->AgregarPago(dineroGanado);

            empleado.push_back(nuevo);
        }
    }

    archivo.close();
    cout << "\nSimulacion cargada exitosamente desde: " << ruta << "\n";
}
