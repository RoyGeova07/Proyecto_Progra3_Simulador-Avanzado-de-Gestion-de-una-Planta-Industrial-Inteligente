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

void MaquinaLavadora::LavarFruta(Frutas& fruta){

    MostrarCronometro(5,fruta.getNombre());
    //aqui se marca la fruta como lavada
    fruta.setLavada(true);
    cout << fruta.getNombre() << " ha sido lavada y ahora esta lista para ser procesada.\n";

}

bool MaquinaLavadora::VerificarFallo(){

    return (rand()%4==0);//25 porciento de probabilidaddddd 

}

void MaquinaLavadora::MenuMaquinaLavadora(std::vector<Frutas>& inventarioFrutas,std::vector<Empleado*>& empleados,Gestor_De_Planta& gestor){

    int opcion;
    int frutaSeleccionada;
    const double AguaPorFruta=0.5;

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
            //size_t es un tipo de dato que se usa para almacenar tamaños e indices 
            //Sirve para especificar la longitud de una cadena, la cantidad de bytes que ocupa un puntero, 
            //o el tamaño de un elemento. 
            for (size_t i=0; i<inventarioFrutas.size(); i++)
            {
                
                cout<<i+1<<". "<<inventarioFrutas[i].getNombre()<<"- Cantidad: "<<inventarioFrutas[i].getCantidad()<<"\n";

            }

            frutaSeleccionada=NumeroValido("Selecciona una fruta para lavar (numero):  ",1,inventarioFrutas.size());
            Frutas& fruta=inventarioFrutas[frutaSeleccionada-1];

            cout<<"\nIniciando lavado de todas las "<<fruta.getNombre()<<" disponibles...\n";

            // Lavar todas las frutas de esta categoría en un bucle
            while (fruta.getCantidad() > 0) {
                if (!getEstado()) {
                    cout << "\n¡La maquina lavadora se ha dañado! Debe repararse antes de continuar.\n";
                    break;
                }

                if(gestor.getAgua()<AguaPorFruta) {
                    cout << "\nNo hay suficiente agua para continuar el lavado. Debe reabastecer agua.\n";
                    break;
                }

                cout<<"\nLavando una "<<fruta.getNombre()<<"...\n";
                //aqui se crea un hilo para lavar esta fruta    ref pasa por referencia ala fruta
                thread HiloLavadoFruta(&MaquinaLavadora::LavarFruta,this,ref(fruta));
                HiloLavadoFruta.join();

                //aqui se resta la fruta del inventario, se simula que se lava una por llamada
                fruta.setCantidad(fruta.getCantidad()-1);

                gestor.ReducirAgua(AguaPorFruta);
                cout << "Se han consumido " << AguaPorFruta << " litros de agua en el lavado.\n";

                if(VerificarFallo()){

                    cout<<"LA LAVADORA SUFRIO UN DESPERFECTO. DEBE REPARASE.\n";
                    setEnUso(false);
                    break;

                }else{

                    cout<<"Lavado completado correctamente. Quedan "<<fruta.getCantidad()<<" "<<fruta.getNombre()<<" por lavar.\n";

                }
            }
            if (fruta.getCantidad()<=0) {

                cout<<"\nTodas las " << fruta.getNombre() << " han sido lavadas y removidas del inventario.\n";
                fruta.setCantidad(0);
                //inventarioFrutas.erase(inventarioFrutas.begin() + frutaSeleccionada - 1);

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