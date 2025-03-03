#include <iostream>
#include <vector>
#include "Maquina.h"
#include "MaquinaLavadora.h"
#include <sstream>
#include "Gestor_De_Planta.h"
#include "EmpleadoTecnico.h"
#include "NumeroValido.h"


using namespace std;

MaquinaLavadora::~MaquinaLavadora(){}


void MaquinaLavadora::MostrarCronometro(int segundos,const string& frutaNombre)const {

    for(int i=1;i<=segundos;++i){

        mtx.lock();
        cout<<"Lavando: "<<frutaNombre<<" - Tiempo transcurrido: "<<i<<" segundos\r";
        cout.flush();
        mtx.unlock();
        this_thread::sleep_for(chrono::seconds(1));

    }
    mtx.lock();
    cout<<"Lavando: "<<frutaNombre<<" - Tiempo transcurrido: "<<segundos<<" segundos\n";
    mtx.unlock();

}

void MaquinaLavadora::LavarFruta(const string& frutaNombre){

    MostrarCronometro(5,frutaNombre);

}

bool MaquinaLavadora::VerificarFallo(){

    return (rand()%4==0);

}

void MaquinaLavadora::MenuMaquinaLavadora(std::vector<Frutas>& inventarioFrutas,std::vector<Empleado*>& empleados){

    int opcion;
    int frutaSeleccionada;

    do{

        cout<<"\n --Menu Maquina Lavadora-- \n";
        cout<<"1. Lavar Frutas\n";
        cout<<"2. Reparar Maquina\n";
        cout<<"3. Regresar\n";
        opcion=NumeroValido("Ingrese una opcion: ",1,3);
    
        if (opcion==1)
        {
    
            if(!getEstado()){
    
                cout<<"\nLa maquina lavadora esta en mal estado. Debe repararse antes de usar.\n";
                continue;
    
            }

            if(inventarioFrutas.empty()){

                cout<<"El inventario de frutas esta vacio.\n";
                continue;

            }

            cout<<"Frutas Diponibles para lavar:\n";
            for (size_t i=0; i<inventarioFrutas.size(); i++)
            {
                
                cout<<i+1<<". "<<inventarioFrutas[i].getNombre()<<"- Cantidad: "<<inventarioFrutas[i].getCantidad()<<"\n";

            }

            frutaSeleccionada=NumeroValido("Selecciona una fruta para lavar (numero):  ",1,inventarioFrutas.size());
            Frutas& fruta=inventarioFrutas[frutaSeleccionada-1];

            cout<<"Iniciando lavado de: "<<fruta.getNombre()<<"\n";

            //aqui se crea un hilo para lavar esta fruta
            thread HiloLavadoFruta(&MaquinaLavadora::LavarFruta,this,fruta.getNombre());
            HiloLavadoFruta.join();

            //aqui se resta la fruta del inventario, se simula que se lava una por llamada
            fruta.setCantidad(fruta.getCantidad()-1);
            if(fruta.getCantidad()<=0){

                inventarioFrutas.erase(inventarioFrutas.begin()+frutaSeleccionada-1);

            }

            if(VerificarFallo()){

                cout<<"LA LAVADORA SUFRIO UN DESPERFECTO. DEBE REPARASE.\n";
                setEnUso(false);

            }else{

                cout<<"Lavado completado correctamente.\n";

            }

    
        }else if (opcion==2){
    
            if(getEstado()){

                cout<<"La lavadora ya esta en buen estado, No necesita reparacion\n";

            }else{

                vector<EmpleadoTecnico*> tecnicos;

                for(auto& MessiMecanico:empleados){

                    if(auto tecnico=dynamic_cast<EmpleadoTecnico*>(MessiMecanico)){

                        tecnicos.push_back(tecnico);

                    }

                }
                EmpleadoTecnico::RepararMaquina(*this,tecnicos);

            }
    
        }else if(opcion==3){
    
            return;
    
        }
        

    }while(opcion!=3);
    
   


}