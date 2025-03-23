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

void MaquinaLavadora::LavarFruta(Frutas& fruta,Gestor_De_Planta& gestor){

    
    int CantidadSinLavar=fruta.getCantidad()-fruta.getCantidadLavada();
    if (CantidadSinLavar<=0)
    {
        
        cout<<"No hay frutas sin lavar de este tipo\n";
        return;

    }
    
    double ConsumoAgua=0.5*CantidadSinLavar;//aqui consumo de agua proporcional
    if (gestor.getAgua()<ConsumoAgua)
    {
        
        cout<<"\nNo hay suficiente agua para lavar todas las frutas. Se lavaran las posibles\n";
        CantidadSinLavar=gestor.getAgua()/0.5;//aqui se ajusta la cantidad de frutas lavadas
        ConsumoAgua=CantidadSinLavar*0.5;

    }
    MostrarCronometro(5,fruta.getNombre());

    gestor.ReducirAgua(ConsumoAgua);
    fruta.setCantidadLavada(fruta.getCantidadLavada()+CantidadSinLavar);
    
    //aqui se crea una nuev fruta lavadacon la misma info se transfieren 
    Frutas frutaLavada(fruta);
    frutaLavada.setCantidad(CantidadSinLavar);
    gestor.TransferirFrutaLavada(frutaLavada);

    
    cout << fruta.getNombre() << " ha sido lavada y ahora esta lista para ser procesada. "
         << "(Unidades lavadas: " << fruta.getCantidadLavada() << ")\n";
    cout << "Se han consumido " << ConsumoAgua << " litros de agua en el lavado.\n";

}

bool MaquinaLavadora::VerificarFallo(){

    return (rand()%4==0);//25 porciento de probabilidaddddd 

}

void MaquinaLavadora::MenuMaquinaLavadora(std::vector<Frutas>& inventarioFrutas, std::vector<Empleado*>& empleados, Gestor_De_Planta& gestor) {
    int opcion;
    int frutaSeleccionada;
    const double AguaPorFruta=0.5;

    do{
        cout<<"=========================================================\n";
        cout<<"\n --Menu Maquina Lavadora-- \n";
        cout<<"1. Lavar Frutas\n";
        cout<<"2. Reparar Maquina\n";
        cout<<"3. Regresar\n";
        opcion=NumeroValido("Ingrese una opcion: ",1,3);
    
        if(opcion==1){
            if(!getEstado()){

                cout << "\nLa maquina lavadora esta en mal estado. Debe repararse antes de usar.\n";
                continue;

            }

            if(inventarioFrutas.empty()){

                cout << "El inventario de frutas esta vacio.\n";
                continue;

            }

            cout << "\nFrutas Disponibles para lavar:\n";
            bool HayFrutasParaLavar=false;

            for(size_t i=0;i<inventarioFrutas.size();i++){

                int CantidadSinLavar=inventarioFrutas[i].getCantidad()-inventarioFrutas[i].getCantidadLavada();

                if(CantidadSinLavar>0){

                    cout<<i+1<< ". " <<inventarioFrutas[i].getNombre()<<"- Cantidad sin lavar: "<<CantidadSinLavar<<"\n";
                    HayFrutasParaLavar=true;

                }

            }
            if(!HayFrutasParaLavar){

                cout << "\nNo hay frutas para lavar\n";
                return;

            }

            do{

                frutaSeleccionada=NumeroValido("Selecciona una fruta para lavar (numero):  ",1,inventarioFrutas.size());
                Frutas& fruta=inventarioFrutas[frutaSeleccionada-1];
                int CantidadSinLavar=fruta.getCantidad()-fruta.getCantidadLavada();
                if(CantidadSinLavar>0){

                    cout << "\nIniciando lavado de todas las " << fruta.getNombre() << " disponibles...\n";
                    break;

                }

                cout<<"Error: La fruta seleccionada ya ha sido lavada completamente. Seleccione otra.\n";
            }while(true);

            Frutas& fruta=inventarioFrutas[frutaSeleccionada-1];

            cout<<"\nLavando "<< fruta.getNombre() << "...\n";
            //aqui inicia el hilo
            thread HiloLavadoFruta(&MaquinaLavadora::LavarFruta, this, ref(fruta), ref(gestor));
            HiloLavadoFruta.join();

          

            if(!getEstado()){

                cout<<"\n¡La maquina lavadora se ha dañado! Debe repararse antes de continuar.\n";
                break;

            }
            if(gestor.getAgua()<AguaPorFruta){

                cout << "\nNo hay suficiente agua para continuar el lavado. Debe reabastecer agua.\n";
                break;

            }

            if(VerificarFallo()){

                cout << "LA LAVADORA SUFRIO UN DESPERFECTO. DEBE REPARARSE.\n";
                setEnUso(false);
                break;

            }
            if(fruta.getCantidadLavada()==fruta.getCantidad()) {

                cout << "\nTodas las " << fruta.getNombre() << " han sido lavadas y marcadas como listas para procesar.\n";

            }

        }else if(opcion==2){

            if(getEstado()){

                cout<< "La lavadora ya esta en buen estado, No necesita reparacion\n";

            }else{

                vector<EmpleadoTecnico*> tecnicos;
                for(auto& MessiMecanico : empleados){

                    if(auto tecnico=dynamic_cast<EmpleadoTecnico*>(MessiMecanico)) {

                        tecnicos.push_back(tecnico);

                    }
                }
                EmpleadoTecnico::RepararMaquina(*this, tecnicos);
            }
        }else if(opcion==3){

            return;

        }
    }while(opcion!=3);
    


}