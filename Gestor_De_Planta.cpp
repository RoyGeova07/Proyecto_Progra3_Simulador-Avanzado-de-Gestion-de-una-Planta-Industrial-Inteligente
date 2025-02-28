#include <iostream>
#include "Gestor_De_Planta.h"
#include "Producto.h"
#include <vector>

using namespace std;

//aqui se usa un destructor para liberar la memmoria de los vectores de puntero
Gestor_De_Planta::~Gestor_De_Planta(){



    for(auto emp : empleado){

        delete emp;

    }
    empleado.clear();


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
             << " | Estado: " << (maquina->isEnUso() ? "Operativa" : "No operativa") << endl;
    }
}
//aqui funcion para eliminar un empleado por el id
void Gestor_De_Planta::eliminarEmpleado(int id) {

    //con begin apunta al primer vector y 
    for(auto limpiar=empleado.begin(); limpiar!=empleado.end();++limpiar){

        if ((*limpiar)->getId()==id)
        {
            
            cout<<"Empleado "<<(*limpiar)->getNombre()<<" eliminado.\n";
            delete *limpiar;//delete aqui para eliminar memoria 
            empleado.erase(limpiar);//aqui quitamos el vector
            return ;

        }
        

    }

    cout<<"No se encontro ningun empleado con ID"<<id<<".\n";

}

void Gestor_De_Planta::generarReporte()const{

    //AQUI FUNCIONAR MEDIANTE ARCHIVOSSSSS

}

