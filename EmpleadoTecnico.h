#ifndef TECNICO_H
#define TECNICO_H
#include "Empleado.h"
#include <thread>
#include <mutex>
#include <vector>
#include <string>
#include "Maquina.h"
#include "Gestor_De_Planta.h"

class EmpleadoTecnico : public Empleado {
    public:

        EmpleadoTecnico(std::string nombre) : Empleado(nombre, "Tecnico de Mantenimiento") {}

        void RealizarTarea() override{

            std::cout<<nombre<<" esta realizando la tarea de mantenimiento tecnico.\n";

        }

        static void RepararMaquina(Maquina& maquina, const std::vector<EmpleadoTecnico*>& tecnicos,Gestor_De_Planta& gestor);
        //void MostrarCronoMetroTecnico(int segundos,const std::string& mensaje);

        //****inveestigar que es el uint******

    };
    

#endif //TECNICO_H