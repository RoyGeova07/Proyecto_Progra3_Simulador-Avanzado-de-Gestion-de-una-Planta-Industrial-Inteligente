#include "EmpleadoTecnico.h"
#include <iostream>
#include <chrono>

using namespace std;
mutex mtx;

void MostrarCronoMetroTecnico(int segundos,const std::string& mensaje){

    for (int i=1;i<=segundos;++i) {

        mtx.lock();
        cout<<mensaje<<" - Tiempo transcurrido: " <<i<< " segundos\r";
        cout.flush();
        mtx.unlock();
        this_thread::sleep_for(chrono::seconds(1));

    }
    mtx.lock();
    cout<<mensaje<<" - Completado en "<<segundos<<" segundos              \n";
    mtx.unlock();

}

//aqui funcion estatica para repara una maquina  usando multiples tecnicossssss
void EmpleadoTecnico::RepararMaquina(Maquina& maquina, const vector<EmpleadoTecnico*>& tecnicos){

    int TiempoBase=15;
    int TiempoPorTenico=max(TiempoBase/(int)tecnicos.size(),3);//cada empleado se tardara al menos 3 segunditossss

    if(tecnicos.empty()){

        cout<<"No hay tecnicos disponibles para repara la maquina.\n";
        return;

    }

    cout<<"\nTecnicos disponibles para la reparacion:\n";
    for(const auto& tecnico:tecnicos){

        cout<<" - "<<tecnico->getNombre()<<"\n";

    }
    vector<thread> hilosReparacion;
    for(const auto& tecnico:tecnicos){

        hilosReparacion.emplace_back([&,TiempoPorTenico](){

        MostrarCronoMetroTecnico(TiempoPorTenico,tecnico->getNombre()+" esta reparando ");

        });

    }

    for(auto& hiloEntra:hilosReparacion){

        hiloEntra.join();

    }

    mtx.lock();
    cout<<"La maquina "<<maquina.getNombre()<<" ha sido reparada y esta en buen estado.\n";
    maquina.setEnUso(true);
    mtx.unlock();

}