#include <iostream>
#include <vector>
#include "Maquina.h"
#include "MaquinaLavadora.h"
#include <sstream>
#include "Gestor_De_Planta.h"
#include "EmpleadoTecnico.h"
#include "NumeroValido.h"


using namespace std;


void Maquina::MenuMaquinas(Gestor_De_Planta& gestor){

    int opcion;
    

    cout<<"\nMenu de maquinas\n";
    cout<<"1. Maquina Lavadora\n";
    cout<<"2. Extractor\n";
    cout<<"3. Pasteurizador\n";
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

            lavadora->MenuMaquinaLavadora(gestor.getInventarioFrutas(),gestor.getEmpleados());

        }else{

            cout<<"No se encontro la lavadora en el sistema.\n";

        }


    }else if (opcion==2){
        
        //PENDIENTEEEEEEEEEEEEEEEEEE
        //PENDIENTEEEEEEEEEEEEEEEEEE
        //PENDIENTEEEEEEEEEEEEEEEEEE
        //PENDIENTEEEEEEEEEEEEEEEEEE

    }else if(opcion==3){

        //PENDIENTEEEEEEEEEEEEEEEEEE
        //PENDIENTEEEEEEEEEEEEEEEEEE
        //PENDIENTEEEEEEEEEEEEEEEEEE
        //PENDIENTEEEEEEEEEEEEEEEEEE

    }else if(opcion==4){

        return;

    }
    


}