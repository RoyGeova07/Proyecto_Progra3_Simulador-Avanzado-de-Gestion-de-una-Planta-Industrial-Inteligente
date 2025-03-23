#include <iostream>
#include "Gestor_De_Planta.h"
#include "Producto.h"
#include <vector>
#include <algorithm>
#include "Empleado.h"
#include "EmpleadoOperario.h"
#include "EmpleadoTecnico.h"
#include "NumeroValido.h"
#include "Maquina.h"
#include "Tienda.h"
#include "Distribucion.h"

using namespace std;


//aqui se usa un destructor para liberar la memmoria de los vectores de puntero
Gestor_De_Planta::Gestor_De_Planta(){

    distribucion=new Distribucion();
    distribucion->setGestor(this);

}

Gestor_De_Planta::~Gestor_De_Planta() {
    delete distribucion;
    for (auto emp : empleado) delete emp;
    empleado.clear();
}

void Gestor_De_Planta::ReducirAgua(double litros){

    if (AguaLitros>=litros)
    {
        
        AguaLitros-=litros;

    }else{

        AguaLitros=0;//aqui evita que el agua sea negativa
        
    }
    

}

void Gestor_De_Planta::AgregarEmpleado(Empleado* emp) {

    empleado.push_back(emp);

}


void Gestor_De_Planta::listarEmpleados()const {

    if (empleado.empty())
    {
        
        cout<<"NO HAY EMPLEADOS EN LA PLANTA\n";
        return;

    }


    cout<<"\n--- Lista de Empleados ---\n" ;   
    for(const auto &emp : empleado)
    {

        emp->MostrarInfo();

    }

}

void Gestor_De_Planta::listarProductos() const{

    if (productos.empty()) {
        cout << "No hay productos en el inventario." << endl;
        return;
    }

    cout << "\n--- Lista de Productos ---\n";
    for (const auto &producto : productos) {
       
        producto.mostrarInfo();

    }

}

void Gestor_De_Planta::ListarFrutas()const {

    if (FRUTAS.empty()) {
        cout << "No hay frutas en el inventario." << endl;
        return;
    }

    cout << "\n--- Lista de Frutas ---\n";
    for (const auto &fruta : FRUTAS) {
        cout << "Nombre: " << fruta.getNombre()
             << " | Cantidad: " << fruta.getCantidad()
             << " | Precio: $" << fruta.getCosto() << endl;
    }

}

void Gestor_De_Planta::VerEstadoMaquina() const {
    if (maquinas.empty()) {
        cout << "No hay maquinas en la planta." << endl;
        return;
    }

    cout << "\n--- Estado de las Maquinas ---\n";
    for (const auto &maquina : maquinas) {

        maquina->VerEstadoMaquina();//aqui se llama la funcion polimorfica.

    }
}

void Gestor_De_Planta::TransferirFrutaLavada(const Frutas& frutaLavada){

    for(auto& fruta:FRUTAS_LAVADAS){

        if (fruta.getNombre()==frutaLavada.getNombre())
        {
            
            fruta.setCantidad(fruta.getCantidad()+frutaLavada.getCantidad());

            //aqui si el costo cambio, puedes decidir si actualizarlo o mantener el anterior:
            fruta.setCosto(frutaLavada.getCosto());  // Opcional


            return;

        }
        
    }
    //aqui si la fruta no esta en la lista de lavadas, se agrega
    FRUTAS_LAVADAS.push_back(frutaLavada);

}

void Gestor_De_Planta::ListarFrutasLavadas()const{

    if (FRUTAS_LAVADAS.empty())
    {

        cout<<"No hay frutas lavadaaaas\n";
        return;
        
    }
    

    cout<<"\n--- Lista de Frutas Lavadas ---\n";
    for(const auto& fruta : FRUTAS_LAVADAS){
        cout << "Nombre: " << fruta.getNombre()
             << " | Cantidad Lavada: " << fruta.getCantidad()
             << " | Precio: $" << fruta.getCosto() << endl;
    }

}

//aqui funcion para eliminar un empleado por el id
//el find_id me ayuda a recorrer el vector empleado, buscando el primer elemento que cumpla con una condiciion
//begin apunta al primer elemento del vector y end al final

// el [id](Empleado* emp) es una funcion lambda que recibe un puntero a empleado y compara el id
// de ese empleado con el id que se esta buscando

//Que devuelve?
//find_if devuelve un iterador que apunta al primer Empleado* que tiene ese id.
//Si no lo encuentra, devuelve empleado.end(), lo que significa "no encontrado".

//Validacion (empleado encontrado o no)
//if (es != empleado.end()) {
//Si es no es end(), significa que find_if encontro un empleado con el ID buscado.
//Si es == end(), significa que el empleado no existe.

//"*es" es el puntero del empleado no encontrado
//(*es)->getNombre() accede al nombre del empleado

//Eliminar el puntero del vector
//Una vez eliminado el empleado, se debe quitar el puntero del vector para que el vector este limpio.
//empleado.erase(es);
//erase elimina el elemento en la posicion del iterador "*es".
//Es como ArrayList.remove(index) en Java, pero aqui se trabaja con punteros e iteradores.


void Gestor_De_Planta::eliminarEmpleado(int id) {

   auto es=find_if(empleado.begin(),empleado.end(),[id](Empleado* emp){

     return emp->getId()==id;

   });

   if(es!=empleado.end()){

        cout<<"\n**Empleado "<<(*es)->getNombre()<<" ha sido despedido.**\n";
        EMPLEADOS_DESPEDIDOS.push_back((*es)->getNombre());//aqui se guarda el nombre del empleado despedido
        delete *es;
        empleado.erase(es);

    }else{

        cout<<"No se encontro ningun empleado con el ID "<<id<<".\n";

    }

}

Empleado* Gestor_De_Planta::BuscarEmpleadoPorId(int id){

    for(Empleado* emp:empleado){

        if(emp->getId()==id){

            return emp;

        }

    }
    return nullptr;

}


int Gestor_De_Planta::CantidadEmpleados() const{

    return empleado.size();

}



void Gestor_De_Planta::AgregarFruta(const Frutas& fruta) {

    for(auto& EstaDuplicadoEl:FRUTAS){

        if(EstaDuplicadoEl.getNombre()==fruta.getNombre())
        {
           
            //aqui si la fruta ya existe, sumamos la cantidad y actulizamos el precio al ultimo valor
            EstaDuplicadoEl.setCantidad(EstaDuplicadoEl.getCantidad()+fruta.getCantidad());
            EstaDuplicadoEl.setCosto(fruta.getCosto());//aqui se actualiza el precio al nuevo ingresado
            return;
           
        } 

    }
    //aqui si no se encontro una fruta con el mismo nombre lo agrega
    FRUTAS.push_back(fruta);

}


void Gestor_De_Planta::AgregarMaquina(Maquina* maq){

    maquinas.push_back(maq);

}

void Gestor_De_Planta::AgregarJugosSinIngredientesYEnvases(const Producto& jugo){

    for(auto&JugoCreado:JUGOS_SIN_INGREDIENTES){

        if (JugoCreado.getNombre()==jugo.getNombre())
        {
            
            JugoCreado.setCantidadSinIngredientes(JugoCreado.getCantidadSinIngredientes()+jugo.getCantidadSinIngredientes());
            //JugoCreado.setNombre(jugo.getNombre());
            return;//aqui evita los duplicados  

        }
        

    }
    Producto NuevoJugo(jugo.getNombre(),jugo.getCantidadProducida(),jugo.getPrecio());
    NuevoJugo.setCantidadSinIngredientes(jugo.getCantidadProducida());//aqui se asegura que la cantidad sin ingredientes se refleje
    JUGOS_SIN_INGREDIENTES.push_back(NuevoJugo);//aqui si no existe lo agrega

}

// estos son los que  ya se pueden vender 
void Gestor_De_Planta::AgregarJugosDisponibles(const Producto& jugo,int cantidad){

    for(auto& JugoFinal:JUGOS_DISPONIBLES){

        if (JugoFinal.getNombre()==jugo.getNombre())
        {
            
            JugoFinal.setCantidadProducida(JugoFinal.getCantidadProducida()+cantidad);
            return;

        }
        
    }
    Producto NuevoJugo(jugo.getNombre(),cantidad,jugo.getPrecio());
    JUGOS_DISPONIBLES.push_back(NuevoJugo);

}

void Gestor_De_Planta::ListaJugosDisponibles()const{

    if(JUGOS_DISPONIBLES.empty())
    {
        
        cout<<"\nNo hay jugos disponibles para la venta.\n";
        return;

    }

    cout<<"\n -- Jugos Disponibles para la venta -- \n";
    for(const auto& jugo:JUGOS_DISPONIBLES){

        cout<<"Jugo: "<<jugo.getNombre()<<" - Cantidad Disponible: "<<jugo.getCantidad()<<" - Precio: $"<<jugo.getPrecio()<<"\n.";

    }
    
}

void Gestor_De_Planta::ListaJugosFaltanIngredientesYEnvases()const{

    if(JUGOS_SIN_INGREDIENTES.empty())
    {

       cout<<"No hay jugos sin ingredientes aun\n";
       return;
        
    }
    cout<<"\n -- Jugos sin Ingredientes -- \n";
    for(const auto& JugosSinSabor: JUGOS_SIN_INGREDIENTES){

        std::cout<<"Jugo: "<<JugosSinSabor.getNombre()<<" Cantidad: "<<JugosSinSabor.getCantidadProducida()<<" - Sin Ingredientes\n";

    }

}

//ESTA FUNCION POR SI ACASO LO NECESITE A FUTURO
//EXPLICARE LA FUNCIONALIDAD DE ESTA FUNCION DESPUESSSSSS
//EXPLICARE LA FUNCIONALIDAD DE ESTA FUNCION DESPUESSSSSS
//EXPLICARE LA FUNCIONALIDAD DE ESTA FUNCION DESPUESSSSSS
//EXPLICARE LA FUNCIONALIDAD DE ESTA FUNCION DESPUESSSSSS
//EXPLICARE LA FUNCIONALIDAD DE ESTA FUNCION DESPUESSSSSS
void Gestor_De_Planta::EliminarJugoSinIngredientes(const string& NombreJugo){

    auto messi=remove_if(JUGOS_SIN_INGREDIENTES.begin(),JUGOS_SIN_INGREDIENTES.end(),[&NombreJugo](const Producto& jugo){return jugo.getNombre()==NombreJugo;});

    if(messi!=JUGOS_SIN_INGREDIENTES.end()){

        JUGOS_SIN_INGREDIENTES.erase(messi,JUGOS_SIN_INGREDIENTES.end());

    }

}

void Gestor_De_Planta::MiniMenuGestor(){

    int opcionmini=0;
  
    while (opcionmini!=5)
    {
        cout<<"\n**Menu de la planta**\n";
        cout<<"1. Listar Planta\n";
        cout<<"2. Despedir Empleados\n";
        cout<<"3. Espacio de Maquinas\n";
        cout<<"4. Comprar Frutas\n";
        cout<<"5. Ver pedidos\n";
        cout<<"6. Generar reporte de esta planta\n";
        cout<<"7. Salir de mi planta\n";
        opcionmini=NumeroValido("Ingrese una opcion: ",1,7);
        
    
        if(opcionmini==1)
        {
            cout<<"===============================================================\n";
            //listar empleados contratados
            cout<<"\nEmpleados activos:\n ";
            listarEmpleados();

            cout<<"----------------------------------------------------------------\n";

            cout<<"\nNombre de la planta: "<<getNombrePLanta()<<"\n";

            cout<<"----------------------------------------------------------------\n";
            //aqui se listas las frutas
            cout<<"\nFrutas en inventario:\n";
            ListarFrutas();

            cout<<"----------------------------------------------------------------\n";

            cout<<"\nCapital: $"<<getCapital()<<"\n";

            cout<<"----------------------------------------------------------------\n";

            cout<<"\nFrutas lavadas en general:\n";
            ListarFrutasLavadas();

            cout<<"----------------------------------------------------------------\n";

            cout<<"\nJugos sin Ingredientes y envases por Agregar:\n";
            ListaJugosFaltanIngredientesYEnvases();

            cout<<"----------------------------------------------------------------\n";

            cout<<"\nJugos Disponibles:\n";
            ListaJugosDisponibles();

            cout<<"----------------------------------------------------------------\n";

            cout<<"\nAgua disponible: "<<getAgua()<<" litros\n";

            cout<<"----------------------------------------------------------------\n";

            cout<<"\nConservantes disponibles: "<<getConservantes()<<" unidades\n";

            cout<<"----------------------------------------------------------------\n";

            cout<<"\n Envases disponibles: "<<getEnvases()<<" unidades\n";

            cout<<"----------------------------------------------------------------\n";
            
            cout<<"\nEstado de las maquinas actualmente:\n";
            VerEstadoMaquina();

            cout<<"====================================================================\n";
    
        }else if (opcionmini==2){
            int id;
    
            cout<<"======================================================================\n";
            cout<<"***seleccione 51 para salir****\n";
           //listar empleados contratados
           cout<<"\nEmpleados activos:\n ";
            listarEmpleados();
           cout<<"---Nota-- Presione 51 para volver al menu\n";
           id=NumeroValido("Ingrese el ID del empleado a despedir: ",1,51);

           if(id==51){

            return;

           }
           
           eliminarEmpleado(id);

           listarEmpleados();

            
        }else if(opcionmini==3){
        
            Maquina::MenuMaquinas(*this);
            
        }else if(opcionmini==4){
    
            Tienda tienda;
            tienda.MenuTienda(*this);
            //Tienda::MenuTienda(*this);
    
        }else if(opcionmini==5){
    
            if(!distribucion){

                distribucion=new Distribucion();
                distribucion->setGestor(this);


            }
            distribucion->mostrarMenuPedidos(*this);

        }else if(opcionmini==6){
    
            //GENERAR REPORTES DE LA PARTIDA DE LA PLANTA CON ARCHIVOS
            //GENERAR REPORTES DE LA PARTIDA DE LA PLANTA CON ARCHIVOS
            //GENERAR REPORTES DE LA PARTIDA DE LA PLANTA CON ARCHIVOS
            //GENERAR REPORTES DE LA PARTIDA DE LA PLANTA CON ARCHIVOS
            //GENERAR REPORTES DE LA PARTIDA DE LA PLANTA CON ARCHIVOS
            EmpleadoOperario dummy(""); // No se usa directamente, pero sirve para invocar el metodo estatico
            dummy.GenerarReportePlantaConHilos(*this, this->getEmpleados());

            
    
        }else if(opcionmini==7){

            //SALIR DE LA PARTIDAAAAAAAA

        }else{

            cout<<"Opcion no valida\n";

        }

    }
        

}

