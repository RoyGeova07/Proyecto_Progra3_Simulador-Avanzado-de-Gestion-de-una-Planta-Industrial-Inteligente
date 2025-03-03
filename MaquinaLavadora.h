#ifndef LAVADORA_H
#define LAVADORA_H
#include "Maquina.h"
#include "Frutas.h"
#include <vector>
#include <thread>
#include <chrono>
#include <mutex>
#include "Empleado.h"

using namespace std;


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

        //aplicando polimorfismo
        void VerEstadoMaquina() const override{

            cout<<"Maquina lavadora: "<<(getEstado()?"En buena estado":"En mal estado")<<endl;

        }
             
        ~MaquinaLavadora() override; 

        
    };

#endif //LAVADORA_H