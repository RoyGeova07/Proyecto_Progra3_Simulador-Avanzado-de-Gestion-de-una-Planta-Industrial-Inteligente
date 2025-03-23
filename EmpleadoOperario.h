#ifndef OPERARIO_H
#define OPERARIO_H
#include "Empleado.h"
#include "Gestor_De_Planta.h"
#include <thread>

class Gestor_De_Planta;

class EmpleadoOperario : public Empleado
{
public:

    EmpleadoOperario(std::string nombre) : Empleado(nombre, "EmpleadoOperario") {}

    void RealizarTarea() override{

        std::cout<<nombre<<" esta realizando la tarea de generar los reportes de la planta.\n";

    }

    void GenerarReportePlanta(Gestor_De_Planta& gestor);
    void GenerarReportePlantaConHilos(Gestor_De_Planta& gestor, std::vector<Empleado*> empleado);



};

#endif //OPERARIO_H