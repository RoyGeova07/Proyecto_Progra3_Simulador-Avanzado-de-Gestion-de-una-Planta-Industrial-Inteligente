#include <iostream>
#include <vector>
#include "Maquina.h"
#include "Frutas.h"
#include "Pasteurizador.h"

using namespace std;

Pasteurizador::~Pasteurizador(){




}


void Pasteurizador::pasteurizar() {
    
    bool pasteurizadorOperativo=false;
    for(auto&m:maquinas){
        if(m->getNombre()=="Pasteurizador" && m->isEnUso()){

            pasteurizadorOperativo=true;
            break;
            
        }
    }
    if(!pasteurizadorOperativo){

        logProgreso.push_back("[pasteurizar] Fallo: No hay pasteurizador operativo.");
        return;

    }

    
    int totalJugo=0;
    for(auto&prod:productos){
        if(prod.getNombre()=="JugoMixto"){

            totalJugo+=prod.getCantidad();

        }
    }
    
    if(totalJugo>0){

       logProgreso.push_back("Se lavaron "+to_string(totalJugo)+" unidades de jugo");

    }else{
        
        logProgreso.push_back("No hay jugo para pasteurizar.");

    }

    
}
