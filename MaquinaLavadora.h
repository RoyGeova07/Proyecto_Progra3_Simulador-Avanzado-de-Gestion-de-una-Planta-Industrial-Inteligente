#ifndef LAVADORA_H
#define LAVADORA_H
#include "Maquina.h"
#include "Frutas.h"
#include <vector>
#include <thread>
#include <chrono>
#include <mutex>
#include "Empleado.h"
#include "Gestor_De_Planta.h"

using namespace std;


class MaquinaLavadora : public Maquina {

    private:    

        mutable std::mutex mtx;

        std::vector<std::string> logProgreso;
        std::vector<Frutas> FRUTAS;
        std::vector<Maquina*> maquinas;
       
        void MostrarCronometro(int segundos,const std::string& frutaNombre )const;

        void LavarFruta(Frutas& fruta,Gestor_De_Planta& gestor);

        bool VerificarFallo();

        

    public:

        
        void MenuMaquinaLavadora(std::vector<Frutas>& inventarioFrutas,std::vector<Empleado*>& empleados,Gestor_De_Planta& gestor);

        MaquinaLavadora():Maquina("Lava frutas") {}

       
             
        ~MaquinaLavadora() override; 

        
    };

#endif //LAVADORA_H