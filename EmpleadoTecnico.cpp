#include "EmpleadoTecnico.h"
#include <iostream>
#include <chrono>

using namespace std;

//este mts es un mecanismo que evita que varios hilos accedan al mismo recurso al mismo tiempo
//en este caso, se usa para que solo un hilo a la vez pueda escrbir en consola
mutex mtx;

//esta funcion mostrara un cronometro que simula que un tecnico esta trabajand
void MostrarCronoMetroTecnico(int segundos,const std::string& mensaje){

    //este for es un contador que representa el paso del tiempo, cada iteracion del ciclo es
    //equivalente a un segundo
    for (int i=1;i<=segundos;++i) {

        mtx.lock();//este evita que varios hilos impriman al mismo tiempo, manteniendo limpio el mensaje
        cout<<mensaje<<" - Tiempo transcurrido: " <<i<< " segundos\r";//esta funcion se actualiza con \r para que el mensaje se sobreescriba
        cout.flush();//este almacena los mensajes del buffer en un buffer interno antes de mostrarlos en pantalla. Este buffer solo se vacia 
        mtx.unlock();// hace la misma funcion que el lock 
        this_thread::sleep_for(chrono::seconds(1));//este hace que el hilo se duerma 1 segundo entre casa impresion
        //asi se simula el tiempo

    }
    mtx.lock();
    cout<<mensaje<<" - Completado en "<<segundos<<" segundos              \n";
    mtx.unlock();

}

//aqui funcion estatica para repara una maquina  usando multiples tecnicossssss
void EmpleadoTecnico::RepararMaquina(Maquina& maquina, const vector<EmpleadoTecnico*>& tecnicos,Gestor_De_Planta& gestor){

    int TiempoBase=15;//aqui se define el tiempo base  que tardaria en reparar la maquina con un solo tecnico
    //el tiempo se divide entre el numero de tecnicos, porque mas tecnicos significan reparacion mas rapida
    int TiempoPorTenico=max(TiempoBase/(int)tecnicos.size(),3);//cada empleado se tardara al menos 3 segunditossss
    //la funcion max() asegura que, aunque haya mucho mas tecnics, cada uno trabajara al menos 3 segundos

    if(tecnicos.empty()){

        cout<<"No hay tecnicos disponibles para repara la maquina.\n";
        return;

    }

    //aqui utilizo for each para listar los tecnicos disponibles
    cout<<"\nTecnicos disponibles para la reparacion:\n";
    for(const auto& tecnico:tecnicos){

        cout<<" - "<<tecnico->getNombre()<<"\n";

    }

    //aqui se verifica si hay suficiente capital 
    double TotalSalarios=0;
    for(const auto& tecnico:tecnicos){

        TotalSalarios+=tecnico->getSalario();

    }
    if(gestor.getCapital()<TotalSalarios){

        cout<<"\n No hay suficiente capital para pagar a todos los tecnicos\n";
        cout<<"Capital disponible: $"<<gestor.getCapital()<<" | Capital requerido: $"<<TotalSalarios<<"\n";
        return;

    }

    int totalPagado=0;
    vector<thread> hilosReparacion;//aqui se crea un nuevo hilo
    for(const auto& tecnico:tecnicos){

        hilosReparacion.emplace_back([&,TiempoPorTenico](){//aqui agrega un nuevo hilo al vector

        //aqui cada hilo ejecuta una funcion lambda (bloque el codigo anonimo) que llama a MostrarCronoMetroTecnico()
        //pasando el tiempo calculado y el mensaje personalizado para ese tecnico

        //[&, TiempoPorTecnico]: Esta es la captura de la lambda. Quiere decir que:
        //& captura todo por referncia,(incluye mtx y el resto de variables del contexto)
        //tiempoPorTecnico se captura por copia (cada hilo tiene su propia copia del tiempo que le toca trabajar).

        MostrarCronoMetroTecnico(TiempoPorTenico,tecnico->getNombre()+" esta reparando");

            //aqui se le pagara al empleado despeus de reparar la maquina
            tecnico->AgregarPago(tecnico->getSalario());
            gestor.agregarCapital(-tecnico->getSalario());//se le resta la capital
            
            mtx.lock();
            cout<<"se ha pagado $"<<tecnico->getSalario()<<" a "<<tecnico->getNombre()<<" \n";
            mtx.unlock();

            //aqui suma total (fuera del lock para no bloquear mucho)
            totalPagado+=tecnico->getSalario();

        });

    }

    //join() hace que el programa espera cada hilo q termine antes de continuar 
    //sin join(), el programa podria avanzar antes de que los tecnicos terminene su trabajo
    for(auto& hiloEntra:hilosReparacion){

        hiloEntra.join();

    }

    mtx.lock();//protegido con mtx para evitar que otro hilo interfiera al escribir
    cout<<"La maquina "<<maquina.getNombre()<<" ha sido reparada y esta en buen estado.\n";
    cout<<"Capital restante: $"<<gestor.getCapital()<<" \n";    
    cout << "\nSe pagaron $" << totalPagado << " en total a los tecnicos.\n";
    maquina.setEnUso(true);
    maquina.IncrementarReparacion();
    mtx.unlock();

}