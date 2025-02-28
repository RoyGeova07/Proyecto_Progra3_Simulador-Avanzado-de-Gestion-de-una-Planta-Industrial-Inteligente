#include <iostream>
#include <vector>
#include "Maquina.h"
#include "MaquinaLavadora.h"


using namespace std;

MaquinaLavadora::~MaquinaLavadora(){



}

void MaquinaLavadora::LavarFrutas(){

    bool LavadoraOperativa=false;
    for(auto &m:maquinas){

        if(m->getNombre()=="Lava frutas"&&m->isEnUso()){

            LavadoraOperativa=true;
            break;

        }

    }

    if(!LavadoraOperativa){

        logProgreso.push_back("[Lavar Frutas] Fallo: No hay lavadora operativa.");
        return;

    }

    int TotalFrutas=0;
    for(auto &f:FRUTAS){

        TotalFrutas+=f.getCantidad();

    }

    //aqui registramos el log 
    logProgreso.push_back("Se lavaron "+to_string(TotalFrutas)+" frutas");


}