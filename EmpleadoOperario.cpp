#include "EmpleadoOperario.h"
#include "Distribucion.h"
#include "Tienda.h"
#include <fstream>
#include <filesystem>
#include <thread>
#include <chrono>
#include <sstream>
#include <iomanip>
#include <mutex>
#include "EmpleadoTecnico.h"

std::mutex coutMutex;// mutex global para controlar el acceso a la consola

using namespace std;
namespace fs = filesystem;

void EmpleadoOperario::GenerarReportePlantaConHilos(Gestor_De_Planta& gestor,std::vector<Empleado*> empleado){

    std::vector<std::thread> hilos;
    std::vector<EmpleadoOperario*> operarios;

    for (auto& emp : empleado) {
        if (auto op = dynamic_cast<EmpleadoOperario*>(emp)) {
            operarios.push_back(op);
        }
    }

    if(operarios.empty()){

        std::cout << "\nNo hay empleados operarios para generar el reporte.\n";
        return;

    }

    double TotalXavi=0;
    for(const auto& operario:operarios){

        TotalXavi+=operario->getSalario();

    }
    if(gestor.getCapital()<TotalXavi){

        cout<<"\n No hay suficiente capital para pagar a todos los operarios\n";
        cout<<"Capital disponible: $"<<gestor.getCapital()<<" | Capital requerido: $"<<TotalXavi<<"\n";
        return;

    }

    std::cout << "\n== Generando reporte de la planta con " << operarios.size() << " empleados operarios ==\n\n";

    //EXPLICAR ESTA FUNCION FESPUESSS
    //EXPLICAR ESTA FUNCION FESPUESSS
    //EXPLICAR ESTA FUNCION FESPUESSS
    //EXPLICAR ESTA FUNCION FESPUESSS
    //EXPLICAR ESTA FUNCION FESPUESSS
    //EXPLICAR ESTA FUNCION FESPUESSS
    for (auto& op : operarios) {
        hilos.emplace_back([&, op]() {
            {
                std::lock_guard<std::mutex> lock(coutMutex);
                std::cout << " " << op->getNombre() << " esta generando el reporte...\n";
            }

            std::this_thread::sleep_for(std::chrono::seconds(2));

            double pago = op->getSalario();
            gestor.agregarCapital(-pago);

            {
                std::lock_guard<std::mutex> lock(coutMutex);
                std::cout << "\n Se ha pagado $" << pago << " a " << op->getNombre() << " por su trabajo.\n";
            }
        });
    }

    for (auto& hilo : hilos) {
        if (hilo.joinable()) hilo.join();
    }

    std::cout << "\n>> Todos los operarios han completado la tarea. Generando archivo de reporte...\n";

    // Crea el reporte desde el primer operario (puedes elegir cualquiera)
    operarios[0]->GenerarReportePlanta(gestor);

    std::cout << " Reporte generado correctamente en la carpeta 'Plantas Industriales'.\n";

}

void EmpleadoOperario::GenerarReportePlanta(Gestor_De_Planta& gestor) {

    string nombrePlanta=gestor.getNombrePLanta();
    string carpeta="Reportes de Plantas Industriales";
    if (!fs::exists(carpeta)) fs::create_directory(carpeta);

   // ¿Que hace ios::trunc?
    //ios::trunc (de truncate) borra todo el contenido previo del archivo si ya existe, y lo reemplaza
    //por el nuevo contenido cada vez que se genera el reporte.
    string ruta = carpeta + "/" + nombrePlanta + ".txt";
    ofstream reporte(ruta, ios::out | ios::trunc);//ahora sobreescribe el archivo 
    if (!reporte.is_open()) {
        cerr << "Error al crear el archivo de Reporte.\n";
        return;
    }
    

    // Encabezado
    reporte << "\n==========  REPORTE DE LA PLANTA ==========\n";
    reporte << " Planta: " << nombrePlanta << "\n";
    reporte << " Fecha y Hora: " << __TIMESTAMP__ << "\n\n";

    // Empleados
    reporte << " >> Empleados Activos:\n";
    for (const auto& emp : gestor.getEmpleados())
        reporte << "   - " << emp->getNombre() << " (" << emp->getCargo() << ")\n";

    // Frutas
    reporte << "\n >> Frutas en inventario:\n";
    for (const auto& fruta : gestor.getInventarioFrutas())
        reporte << "   - " << fruta.getNombre() << ": " << fruta.getCantidad() 
                << " unidades ($" << fruta.getCosto() << " c/u)\n";

    // Jugos
    reporte << "\n >> Jugos listos para la venta:\n";
    for (const auto& jugo : gestor.getInventarioJugos())
        reporte << "   - " << jugo.getNombre() << ": " << jugo.getCantidad() 
                << " unidades ($" << jugo.getPrecio() << " c/u)\n";

    // Recursos
    reporte << "\n >> Recursos disponibles:\n";
    reporte << "   - Agua: " << gestor.getAgua() << " litros\n";
    reporte << "   - Conservantes: " << gestor.getConservantes() << "\n";
    reporte << "   - Envases: " << gestor.getEnvases() << "\n";

    // Estado de máquinas
    reporte << "\n >> Estado de las Maquinas:\n";
    for (const auto& maquina : gestor.getMaquinas()) {
        reporte << "\n=============================================================================\n";
        reporte << " Maquina: " << maquina->getNombre() << "\n";
        reporte << "   Estado: " << (maquina->getEstado() ? "En buen estado" : "En mal estado") << "\n";
        reporte << "   Veces usada: " << maquina->getVecesUsadas() << "\n";
        reporte << "   Veces reparada: " << maquina->getVecesReparada() << "\n";
        reporte << "   Ultimo uso: " << maquina->getUltimaFechaUso() << "\n";
    }

    // Frutas compradas desde la tienda
    reporte << "\n >> Reporte de compras en la Tienda:\n";
    Tienda& tienda=gestor.getTienda(); 
    reporte << "   - Frutas totales compradas: " << tienda.getFrutasCompradas() << "\n";
    reporte << "     * Limon: " << tienda.getLimon() << "\n";
    reporte << "     * Naranja: " << tienda.getNaranja() << "\n";
    reporte << "     * Piña: " << tienda.getPilla() << "\n";
    reporte << "     * Sandia: " << tienda.getSandia() << "\n";
    reporte << "     * Fresa: " << tienda.getFresa() << "\n";
    reporte << "     * Tamarindo: " << tienda.getTamarindo() << "\n";
    reporte << "     * Coco: " << tienda.getCoco() << "\n";
    reporte << "   - Conservantes comprados: " << tienda.getConservantesComprados() << "\n";
    reporte << "   - Envases comprados: " << tienda.getEnvasesComprados() << "\n";
    reporte << "   - Agua comprada: " << tienda.getAguaComprada() << " litros\n";
    reporte << " Total gastado en la tienda: $" << fixed << setprecision(2) 
            << tienda.getDineroGastadoEnTodaLatienda() << "\n";

    // Ranking de jugos vendidos
    if(gestor.getDistribucion()!=nullptr){
        gestor.getDistribucion()->MostrarRanking(reporte);
    }else{

        reporte << "   No hay datos de distribucion registrados.\n";

    }

    // Empleados Despedidos
    const auto& despedidos=gestor.getEmpleadosDespedidos();
    if(!despedidos.empty()){

        reporte << "\n >> Empleados que han sido despedidos:\n";

        for(const auto& nombre : despedidos){

            reporte << "   - " << nombre << "\n";

        }
    }else{

        reporte << "\n >> No se ha despedido a ningun empleado aun.\n";

    }

    // PAGOS A LOS EMPLEADOS OPERARIOS
    //EXPLICAR DESPUESSS
    reporte << "\n >> Sueldos pagados por la generacion del reporte:\n";
    double totalPagado = 0.0;
    for (const auto& emp : gestor.getEmpleados()) {
        if (auto op = dynamic_cast<EmpleadoOperario*>(emp)) {
            double salario = op->getSalario();
            reporte << "   - " << op->getNombre() << ": $" << fixed << setprecision(2) << salario << "\n";
            totalPagado += salario;
        }
    }
    reporte << "Total pagado a operarios: $" << fixed << setprecision(2) << totalPagado << "\n";

    //AGREGAR A LOS EMPLEADOS TECNICOS
    //--------------------------------------------
    reporte<<"\n >> Sueldo pagados por la reparacion de maquinas:\n";
    double totalMaquina;
    for(const auto& maqui:gestor.getEmpleados()){

        if(auto meca=dynamic_cast<EmpleadoTecnico*>(maqui)){

            double otrosalario=maqui->getSalario();
            reporte<<"  - "<<maqui->getNombre()<<": $"<<fixed<<setprecision(2)<<otrosalario<<"\n";
            totalMaquina+=otrosalario;

        }

    }
    reporte<<"Total Pagado a empleados tecnicos: $"<<fixed<<setprecision(2)<<totalMaquina<<"\n";

}
