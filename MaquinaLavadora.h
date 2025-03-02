#ifndef LAVADORA_H
#define LAVADORA_H
#include "Maquina.h"
#include "Frutas.h"
#include <vector>
#include <thread>
#include <chrono>
#include <mutex>
#include "Empleado.h"


class MaquinaLavadora : public Maquina {

    private:    

        mutable std::mutex mtx;

        std::vector<std::string> logProgreso;
        std::vector<Frutas> FRUTAS;
        std::vector<Maquina*> maquinas;
       
        void MostrarCronometro(int segundos,const std::string& frutaNombre )const;

        void LavarFruta(const std::string& frutaNombre);

        bool VerificarFallo();

        

    public:

        
        void MenuMaquinaLavadora(std::vector<Frutas>& inventarioFrutas,std::vector<Empleado*>& empleados);

        MaquinaLavadora():Maquina("Lava frutas") {}
             
        ~MaquinaLavadora() override; 

        
    };

#endif //LAVADORA_H