#include <iostream>
#include "Gestor_De_Planta.h"
#include "Producto.h"
#include <vector>
#include <algorithm>
#include "Empleado.h"
#include "EmpleadoOperario.h"
#include "EmpleadoSupervisor.h"
#include "EmpleadoTecnico.h"

using namespace std;


//aqui se usa un destructor para liberar la memmoria de los vectores de puntero
Gestor_De_Planta::~Gestor_De_Planta(){



    for(auto emp : empleado){

        delete emp;

    }
    empleado.clear();


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
        cout << "Maquina: " << maquina->getNombre()
             << " | Estado: " << (maquina->isEnUso() ? "En Mal estado" : "En buen estado") << endl;
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

    FRUTAS.push_back(fruta);

}

void Gestor_De_Planta::AgregarMaquina(Maquina* maq){

    maquinas.push_back(maq);

}



void Gestor_De_Planta::generarReporte()const{

    //AQUI FUNCIONAR MEDIANTE ARCHIVOSSSSS

}

