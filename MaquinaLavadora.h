#ifndef LAVADORA_H
#define LAVADORA_H
#include "Maquina.h"
#include "Frutas.h"
#include <vector>


class MaquinaLavadora : public Maquina {

    private:    

        std::vector<std::string> logProgreso;
        std::vector<Frutas> FRUTAS;
        void LavarFrutas(); 
        std::vector<Maquina*> maquinas;
        

    public:

        MaquinaLavadora():Maquina("Lava frutas") {}
             
        ~MaquinaLavadora() override; 

        
    };

#endif //LAVADORA_H