#include <iostream>
#include <vector>
#include "Maquina.h"
#include "Frutas.h"
#include "Envasadora.h"
#include <mutex>
#include "NumeroValido.h"
#include <thread>
#include "Empleado.h"
#include "EmpleadoTecnico.h"

using namespace std;

Envasadora::~Envasadora(){}


void Envasadora::MostrarCronometro(int segundos,const string& JugoNombre)const{

    for (int i=1;i<segundos;i++)
    {
        
        this->mtx.lock();
        cout<<JugoNombre<<" - Proceso en curso: "<<i<<" segundos\r";
        cout.flush();
        this->mtx.unlock();
        this_thread::sleep_for(chrono::seconds(1));

    }
    this->mtx.lock();
    cout<<JugoNombre<<" - Proceso completado en "<<segundos<<" segundos\n";
    this->mtx.unlock();
}

void Envasadora::AgregarIngredientes(const string& JugoNombre,Gestor_De_Planta& gestor,int cantidad)const{

    this->mtx.lock();
    cout<<"\nIniciando el agregado de conservantes a jugo de "<<JugoNombre<<"...\n";
    this->mtx.unlock();

    MostrarCronometro(3,"Agregando conservantes en el jugo de "+JugoNombre);

    if (gestor.getConservantes()>=cantidad)
    {
        
        gestor.AgregarMasConservantes(-cantidad);//se resta los conservantes
        this->mtx.lock();
        cout<<JugoNombre<<" se le a agredo los conservantes correctamente ("<<cantidad<<" unidades).\n";
        this->mtx.unlock();

    }else{

        this->mtx.lock();
        cout<<"ERROR: No hay conservantes disponibles para agregar a "<<cantidad<<"unidades de "<<JugoNombre<<"\n";
        this->mtx.unlock();

    }  

}

void Envasadora::EnvasarJugos(const std::string& JugoNombre,Gestor_De_Planta& gestor,int cantidad)const{

    this->mtx.lock();
    cout<<"\nEmpezando a envasar "<<cantidad<<" unidades de "<<JugoNombre<<"..\n";
    this->mtx.unlock();

    MostrarCronometro(3,"Envasando el "+to_string(cantidad)+" unidades de "+JugoNombre);

    if (gestor.getEnvases()>=cantidad)
    {
        
        gestor.AgregarMasEnvases(-cantidad);
        this->mtx.lock();
        cout<<JugoNombre<<" ha sido envasado correctamente ("<<cantidad<<" unidades).\n";
        this->mtx.unlock();

    }else{

        this->mtx.lock();
        cout<<"ERROR: no hay suficientes envases para poder envasar "<<cantidad<<" unidades de "<<JugoNombre<<"\n.";
        this->mtx.unlock();

    }
    
    this->mtx.lock();
    cout<<JugoNombre<<" Envasado exitosamente\n";
    this->mtx.unlock();

}

bool Envasadora::VerificarFallo(){

    return (rand()%5==0);

}

void Envasadora::MenuMaquinaEnvasadora(std::vector<Producto>& InventarioJugos,std::vector<Empleado*>&Empleados,Gestor_De_Planta& gestor){

    int opcion;
    int JugoSeleccionado;
    
    do
    {
        
        cout<<"\n -- Menu de Maquina Envadora -- \n";
        cout<<"1. Envasar y agregar ingredientes\n";
        cout<<"2. Reparar Maquina\n";
        cout<<"3. Regresar\n";
        opcion=NumeroValido("Ingrese una opcion: ",1,3);
        
        if(opcion==1)
        {
            
            if (!getEstado())
            {

                cout<<"\nLa maquina envasadora de frutas eta en mal estado. Debe repararse antes de usar\n";
                continue;
                
            }

            if (gestor.getInventarioJugosSinIngredientes().empty())
            {
                
                cout<<"No hay jugos hechos aun\n";
                continue;  

            }

            cout<<"\n -- Jugos disponibles para envasar e agregar conservantes -- \n";
            bool HayJugosDisponibles=false;

            auto& JugosDisponibles=gestor.getInventarioJugosSinIngredientes();

            for (size_t i=0;i<JugosDisponibles.size();i++)
            {
                
                //aqui si esta hecho el jugo se mostraran
                if (JugosDisponibles[i].hayJugosSinIngredientes())
                {
                    
                    cout<<i+1<<". "<<JugosDisponibles[i].getNombre()<<" - Cantidad: "<<JugosDisponibles[i].getCantidadSinIngredientes()<<"\n";
                    HayJugosDisponibles=true;

                }
                
            }
            if(!HayJugosDisponibles)
            {
                
                cout<<"No hay jugos dispnibles para envasar e agregar ingredientes";
                return;

            }

            JugoSeleccionado=NumeroValido("Seleccione un jugo disponible (numero):",1,gestor.getInventarioJugosSinIngredientes().size());

            if (JugoSeleccionado<1||JugoSeleccionado>JugosDisponibles.size()) {
                cout << "ERROR: Seleccion invalida.\n";
                return;
            }

            Producto& producto=JugosDisponibles[JugoSeleccionado-1];//aqui se aseguar el acceso valido

            if (!producto.hayJugosSinIngredientes())
            {
                
                cout<<"ERROR: El jugo seleccionado no existe o ya tiene ingredientes.\n";
                continue;

            }
            
            int CantidadAProcesar=producto.getCantidadSinIngredientes();
            /*
            
            if (producto.getCantidadSinIngredientes())
            {
                
                cout<<"ERROR: el jugo seleccionado no existe aun\n";
                continue;

            } 

            */
           
            cout<<"\nIniciando proceso de "<<CantidadAProcesar<<" unidades de "<<producto.getNombre()<<"..\n";

            //aqui creacion de hilo
            thread HiloIngrediente(&Envasadora::AgregarIngredientes,this,producto.getNombre(),ref(gestor),CantidadAProcesar);
            HiloIngrediente.join();

            //aqui hilo para evasar
            //se pasa referencia al gestor, permitiendo reducir los consevantes correctamente
            thread HiloEnvasar(&Envasadora::EnvasarJugos,this,producto.getNombre(),ref(gestor),CantidadAProcesar);
            HiloEnvasar.join();

            gestor.AgregarJugosDisponibles(producto,CantidadAProcesar);
            producto.DecrementarJugosSinIngredientes(CantidadAProcesar);//aqui se restan los jugos procesados

            /*
                // Si ya no quedan jugos sin ingredientes, eliminarlos del vector
                if(producto.getCantidadSinIngredientes() <= 0) {

                    gestor.EliminarJugoSinIngredientes(producto.getNombre());

                  }
            */
           //aqui si ya no quedan jugos sin ingredientes, se eliminaran del vector
           if (producto.getCantidadSinIngredientes()<=0)
           {
            
            gestor.EliminarJugoSinIngredientes(producto.getNombre());

           }
           
            cout<<"Se ha envasado y agregado conservantes a  "<<CantidadAProcesar<<" unidades de "<<producto.getNombre();
            
        }else if (opcion==2){
            
            if (getEstado())
            {
                
                cout<<"La envasadora ya esta en buen estado, no necesita reparacion\n";

            }else{

                vector<EmpleadoTecnico*>tecnicos;

                for(auto& HitlerMecanico:Empleados){

                    //el dynamic cast me ayuda hacer conversionesde tipos de forma segura
                    if(auto tecnico=dynamic_cast<EmpleadoTecnico*>(HitlerMecanico)){

                        tecnicos.push_back(tecnico);

                    }

                }
                EmpleadoTecnico::RepararMaquina(*this,tecnicos);

            }

        }else if(opcion==3){
            
            return;

        }
        

    } while (opcion!=3);
    

}
