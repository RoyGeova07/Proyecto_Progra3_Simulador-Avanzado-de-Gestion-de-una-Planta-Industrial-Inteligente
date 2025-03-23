#include <iostream>
#include <vector>
#include "Maquina.h"
#include "Frutas.h"
#include "ProcesadorFrutas.h"
#include <thread>
#include <mutex>
#include <chrono>
#include "NumeroValido.h"
#include "EmpleadoTecnico.h"

using namespace std;


ProcesadorFrutas::~ProcesadorFrutas(){}


void ProcesadorFrutas::MostrarCronometro(int segundos,const string&Frutanombre)const{

    for (int i=1;i<segundos;i++)
    {

        this->mtx.lock();
        cout<<Frutanombre<<" - Proceso en curso: "<<i<<" segundos\r";
        cout.flush();
        this->mtx.unlock();
        this_thread::sleep_for(chrono::seconds(1));

    }
    this->mtx.lock();
    cout<<Frutanombre<<" - Proceso completado en "<<segundos<<" segundos\n";
    this->mtx.unlock();
    
}

void ProcesadorFrutas::TriturarFruta(int segundos,const string&Frutanombre)const{

    this->mtx.lock();
    cout<<"\nIniciando trituracion de "<<Frutanombre<<"...\n";
    this->mtx.unlock();

    MostrarCronometro(segundos, " Triturando: "+Frutanombre);

    this->mtx.lock();
    cout<<Frutanombre<<" ha sido triturada correctamente.\n";
    this->mtx.unlock();
    

}

void ProcesadorFrutas::ExtraerJugo(int segundos,const string&FrutaNombre)const{


    this->mtx.lock();
    cout<<"\nIniciando Extracion de jugo de "<<FrutaNombre<<"...\n";
    this->mtx.unlock();

    MostrarCronometro(segundos," Extraendo Jugo de: "+FrutaNombre);

    this->mtx.lock();
    cout<<"Jugo de la fruta"<<FrutaNombre<<" extraido exitosamente.\n";
    this->mtx.unlock();

}

bool ProcesadorFrutas::VerificarFallo(){

    return (rand()%5==0);//20 porciento de fallarrrr

}

void ProcesadorFrutas::MenuProcesadorFrutas(std::vector<Frutas>&inventarioFrutas,std::vector<Empleado*>&empleados,Gestor_De_Planta& gestor){

    int opcion;
    int FrutaSeleccionada;

    do
    {
        cout<<"=============================================================\n";
        cout<<"\n --- Menu Procesador de Frutas --- \n";
        cout<<"1. Procesar Frutas (Triturar y extraer Jugo)\n";
        cout<<"2. Reparar Maquina\n";
        cout<<"3. Regresar\n";
        opcion=NumeroValido("Ingrese una opcion: ",1,3);
        

        if(opcion==1)
        {
            
            if(!getEstado())
            {

                cout<<"\nLa maquina procesadora de frutas eta en mal estado. Debe repararse antes de usar\n";
                continue;
                
            }
            
            if(inventarioFrutas.empty())
            {
                
                cout<<"El inventario de frutas esta vacio\n";
                continue;

            }

            cout<<"--\n Frutas disponibles para procesar (solo lavadas) -- \n";
            bool HayFrutasLavadas=false;
            for (size_t i=0;i<inventarioFrutas.size();i++)
            {
                //si la fruta esta lavada se mostran las disponibles
                if (inventarioFrutas[i].hayFrutasLavadas())
                {

                    cout<<i+1<<". "<<inventarioFrutas[i].getNombre()<<" - Cantidad: "<<inventarioFrutas[i].getCantidadLavada()<<"\n";
                    HayFrutasLavadas=true;
                    
                }
            

            }
            if (!HayFrutasLavadas)
            {
                
                cout<<"No hay frutas lavadas disponibles para procesar.\n";
                return;

            }
                
            FrutaSeleccionada=NumeroValido("Seleccione una fruta para procesar (numero): ",1,inventarioFrutas.size());    
                
            Frutas& fruta=inventarioFrutas[FrutaSeleccionada-1];

            if (fruta.getCantidadLavada()<=0) {

                cout << "ERROR: La fruta seleccionada no ha sido lavada aun. Seleccione otra.\n";
                continue;

            }

            int CantidadAProcesar=fruta.getCantidadLavada();

            cout<<"\nIniciando proceso de "<<CantidadAProcesar<<" uniades de "<<fruta.getNombre()<<"..\n";

            if(gestor.getConservantes()<CantidadAProcesar){

                cout<<"\nERROR: No hay suficiente conservantes para procesar "<<CantidadAProcesar<<" unidades\n";
                continue;

            }
            if(gestor.getEnvases()<CantidadAProcesar){

                cout<<"\nERROR: No hay suficiente envases para procesar "<<CantidadAProcesar<<" unidades\n";

            }

            //hilo que tritura la fruta
            thread HiloTritura(&ProcesadorFrutas::TriturarFruta,this,5,fruta.getNombre());  
            HiloTritura.join();

            //hilo para extraer el jugo despues de la trituracion
            thread HiloExtraeJuguito(&ProcesadorFrutas::ExtraerJugo,this,5,fruta.getNombre());
            HiloExtraeJuguito.join();
            IncrementarUso();

            //aqui se convierte la fruta en jugo y se almacena en el vector de jugos sin ingredientes y envases
            Producto::Jugos TipoJugo;
            double PrecioJugo;

            if(fruta.getNombre()=="Limon") {TipoJugo=Producto::Limonada; PrecioJugo=17.0;}
            else if(fruta.getNombre()=="Naranja"){TipoJugo=Producto::JugoNaranja; PrecioJugo=15.0;}
            else if(fruta.getNombre()=="Piña"){TipoJugo=Producto::JugoPilla; PrecioJugo=12.0;}
            else if(fruta.getNombre()=="Sandia"){TipoJugo=Producto::JugoSandia; PrecioJugo=11.0;}
            else if(fruta.getNombre()=="Fresa"){TipoJugo=Producto::JugoFresa; PrecioJugo=22.0;}
            else if(fruta.getNombre()=="Tamarindo"){TipoJugo=Producto::JugoTamarindo; PrecioJugo=24.0;}
            else if(fruta.getNombre()=="Coco"){TipoJugo=Producto::AguaCoco; PrecioJugo=30.0;}
            
            //AQUI DEFINIMOS EL NOMBRE DEL JUGO SU CANTIDAD Y SU NUEVO PRECIO
            Producto Jugo(fruta.getNombre(),CantidadAProcesar,PrecioJugo);
            Jugo.setCantidadSinIngredientes(CantidadAProcesar);//aqui se asegura que la cantidad es la correcta
            
            cout<<"=========================================================\n";
            gestor.AgregarJugosSinIngredientesYEnvases(Jugo);
            cout<<"Se ha creado "<<CantidadAProcesar<<" jugos de "<<fruta.getNombre()<<"\n";

            fruta.DecrementarLavada(CantidadAProcesar);
            fruta.setCantidad(fruta.getCantidad()-CantidadAProcesar);

            if (fruta.getCantidad()<=0)
            {
                
                inventarioFrutas.erase(inventarioFrutas.begin()+FrutaSeleccionada-1);
                cout<<"Se han agotado las frutas seleccionadaas.\n";

            }
            if (VerificarFallo())
            {
                
                cout<<"EL PROCESADOR DE FRUTAS SUFRIO UN DESPERFECTO. DEBE REPARASEEE";
                setEnUso(false);

            }else{

                double ConsumoAgua=2.0;
                gestor.ReducirAgua(ConsumoAgua);
                cout<<"Proceso completado sin problemas\n";
                cout<<"Se han consumido "<< ConsumoAgua <<" litros de agua en el procesamiento.\n";

            }

        }else if (opcion==2){
            
            if (getEstado())
            {
                
                cout<<"El procesador ya esta en buen estado, no necesita reparacion\n";

            }else{

                vector<EmpleadoTecnico*>tecnicos;

                for(auto& ToroMecanico:empleados){

                    //el dynamic cast me ayuda hacer conversionesde tipos de forma segura
                    if(auto tecnico=dynamic_cast<EmpleadoTecnico*>(ToroMecanico)){

                        tecnicos.push_back(tecnico);

                    }

                }
                EmpleadoTecnico::RepararMaquina(*this,tecnicos,gestor);

            }
            

        }else if(opcion==3){
            
            return;

        }
        

    } while (opcion!=3);
        

}
