#include <iostream>
#include <vector>
#include "Maquina.h"
#include "MaquinaLavadora.h"
#include <sstream>
#include "Gestor_De_Planta.h"
#include "EmpleadoTecnico.h"
#include "NumeroValido.h"
#include "ProcesadorFrutas.h"
#include "Envasadora.h"


using namespace std;


void Maquina::MenuMaquinas(Gestor_De_Planta& gestor){

    int opcion;
    
    cout<<"==========================================================\n";
    cout<<"\nMenu de maquinas\n";
    cout<<"1. Maquina Lavadora\n";
    cout<<"2. ProcesadorFrutas\n";
    cout<<"3. Envasadora\n";
    cout<<"4. Volver\n";
    opcion=NumeroValido("Ingrese una opcion: ",1,4);


    if (opcion==1)
    {
        
        //aqui buscamos la lavadora que cree en el gestor
        MaquinaLavadora* lavadora=nullptr;

        for(auto& maquina:gestor.getMaquinas()){

            lavadora=dynamic_cast<MaquinaLavadora*>(maquina);
            if(lavadora)break;//se encontroooooo

        }

        if(lavadora){

            lavadora->MenuMaquinaLavadora(gestor.getInventarioFrutas(),gestor.getEmpleados(),gestor);

        }else{

            cout<<"No se encontro la lavadora en el sistema.\n";

        }


    }else if (opcion==2){
        
        ProcesadorFrutas* procesador=nullptr;

        for(auto& maquina:gestor.getMaquinas()){

            procesador=dynamic_cast<ProcesadorFrutas*>(maquina);
            if(procesador)break;

        }

        if (procesador)
        {
            
            procesador->MenuProcesadorFrutas(gestor.getInventarioFrutas(),gestor.getEmpleados(),gestor);

        }else{

            cout<<"No se encontro el procesador de frutas en el sistema.\n";

        }
        

    }else if(opcion==3){

        Envasadora* Envasador=nullptr;

        for(auto& maquina:gestor.getMaquinas()){

            Envasador=dynamic_cast<Envasadora*>(maquina);
            if(Envasador){

                break;

            }
            
        }
        
        if(Envasador){

            Envasador->MenuMaquinaEnvasadora(gestor.getInventarioJugos(),gestor.getEmpleados(),gestor);

        }else{

            cout<<"No se encontro el envasador de jugos de frutas en el sistema.\n";

        }

    }else if(opcion==4){

        return;

    }
    


}