#include <iostream>
#include <vector>
#include "Maquina.h"
#include "Frutas.h"
#include "Extractor.h"

using namespace std;

Extractor::~Extractor(){



}

void Extractor::extraerJugo(){

    bool extractorOperativo=false;
    for(auto&m:maquinas){

        if (m->getNombre()=="Extractor de Jugo" && m->getEstado()){

            extractorOperativo=true;
            break;

        }

    }

    if(!extractorOperativo){

        logProgreso.push_back("[extraerJugo] Fallo: No hay extractor operativo.");
        return;

    }

    
    int totalFrutas=0;
    for(auto&f:FRUTAS){

        totalFrutas+=f.getCantidad();
        // Opcional: si quieres "consumir" la fruta, haz f.setCantidad(0)

    }
    if(totalFrutas>0){

        //MODIFICAR DESPUES
        // Creamos un Producto "JugoMixto" (por ejemplo)
        productos.push_back(Producto("JugoMixto",totalFrutas,2.0));
        logProgreso.push_back("Se extrajo jugo de " + to_string(totalFrutas) + " frutas.");

    }else{

        logProgreso.push_back("No hay frutas para extraer jugo.");

    }

}