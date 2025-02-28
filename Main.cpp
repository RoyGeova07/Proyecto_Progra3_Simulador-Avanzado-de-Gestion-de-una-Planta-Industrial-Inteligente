#include <iostream>
#include <conio.h>
#include <string>
#include <string.h>
#include <limits>
#include <stdlib.h>
#include <ctime>
#include <cstdlib>//para seed random
#include "Empleado.h"
#include "EmpleadoTecnico.h"
#include "EmpleadoOperario.h"
#include "EmpleadoSupervisor.h"
#include "Maquina.h"
#include "MaquinaLavadora.h"
#include "Pasteurizador.h"
#include "Extractor.h"
#include "Frutas.h"
#include "Gestor_De_Planta.h"
#include <set>
#include <sstream>
#include <chrono>




using namespace std;

vector<Frutas> inventarioFrutas;
vector<Empleado*> empleados;//se usa como tipo puntero porque se usara polimorfismo, tambien para no 
//perder informacion, facilita el gestion dinamica de memoria
vector<Maquina*> maquinas;

int NumeroValido(string mensaje, int minimo, int maximo) {

    int valor;
    string entrada;
    char extra;
    while (true) {

        cout << mensaje;
        getline(cin, entrada);
        istringstream iss(entrada);

        //aqui se extraer el entero
        if (!(iss>>valor)) {

            cout << "Error: Entrada no valida. Intente de nuevo.\n";
            continue;

        }
        //aqui verificamos que no haya caracteres adicionales (por ejemplo, el ".4" de "3.4")

        if (iss>>extra) {

            cout<<"Error: Entrada no valida. Intente de nuevo.\n";
            continue;

        }
        if (valor<minimo||valor>maximo) {

            cout<<"Error: Entrada fuera de rango. Intente de nuevo.\n";
            continue;

        }
        return valor;

    }
}

template <typename T>
T NumeroTemplate(string mensaje, T minimo, T Maximo){

    T valor;
    string auxiliar;
    char extra;
    while (true){

        cout << mensaje;
        getline(cin, auxiliar);
        istringstream iss(auxiliar);

        //aqui se  extrae el valor del tipo T
        if(!(iss>>valor)){

            cout << "Error: Entrada no valida. Intente de nuevo.\n";
            continue;

        }
        // Verificamos si quedaron caracteres adicionales usando 'iss' y no 'cin'
        if(iss>>extra){

            cout<<"Error: Entrada no valida. Intente de nuevo.\n";
            continue;

        }
        if(valor<minimo||valor>Maximo){

            cout << "Error: Entrada fuera de rango. Intente de nuevo.\n";
            continue;

        }
        return valor;
    }
}

vector<string> ObtenerListaDeNombres(){
    return {

        "Carlos Gonzalez", "Maria Lopez", "Juan Martinez", "Ana Rodriguez", "Luis Perez",
        "Elena Sanchez", "Pedro Diaz", "Carmen Vega", "Jose Ruiz", "Sofia Fernandez",
        "Andres Castro", "Raquel Navarro", "Diego Mendoza", "Victoria Jimenez", "Fernando Rojas",
        "Paula Silva", "Jorge Acosta", "Natalia Herrera", "Manuel Morales", "Rosa Torres",
        "Ismael Gutierrez", "Gloria Figueroa", "Roberto Ortega", "Beatriz Paredes", "Daniel Escobar",
        "Gabriela Miranda", "Rodrigo Cabrera", "Martina Castillo", "Sebastian Fuentes", "Clara Rivas",
        "Hugo Salazar", "Valeria Villanueva", "Oscar Delgado", "Lucia Guzman", "Ramiro Peña",
        "Adriana Cardenas", "Victor Solis", "Daniela Campos", "Ricardo Espinoza", "Margarita Montoya",
        "Emilio Nunez", "Estefania Tapia", "Raul Olivares", "Patricia Bermudez", "Julian Serrano",
        "Melissa Duarte", "Alberto Valenzuela", "Lorena Meza", "Francisco Arce", "Renata Ibarra"
        
    };
}

vector<string> ObtenerNombresAleatorios(int cantidad){

    vector<string> NombresBase=ObtenerListaDeNombres();//desde aqui se obtienen la lista de los 50 nombres
    set<int> IndiceSeleccionado;//aqui se usa un set para guardar los indices unicos
    vector<string> nombresAleatorios;//aqui la lista final de nombres aleatorios

    // Se usa un while para asegurarse de que se seleccionen exactamente cantidad nombres sin repeticiones
    while (IndiceSeleccionado.size()<cantidad)
    {
        
        int index=rand()%NombresBase.size();//aqui se selecciona un indice aleatorio entre 0 y 49

        if (IndiceSeleccionado.find(index)==IndiceSeleccionado.end())//aqui se verifica si el indice ya fue usado
        {
            
            IndiceSeleccionado.insert(index);//aqui se agrega el indice set para evitar repetidos
            nombresAleatorios.push_back(NombresBase[index]);//y aqui agrega el nombre

        }
        

    }
    
    return nombresAleatorios;//finalmente aqui retona los nombres aleatorios sin repetir


}

char obtenerRespuestaSN(string mensaje){

    string auxiliar;
    char respuesta;
    while(true){

        cout<<mensaje;
        getline(cin,auxiliar);
        if(auxiliar.empty())continue;
        respuesta = tolower(auxiliar[0]);  
        if(respuesta=='s'||respuesta=='n')return respuesta;
        cout << "Entrada invalida. Ingrese 's' para si o 'n' para no.\n";   

    }

}

void ConfigurarParametrosIniciales()
{

    srand(time(0));//aqui se inicializa el random

    string nombrePlanta;
    double capitalInicial=10000;
    double capitalAdicional;
    int cantidadEmpleados;

    int aguaLitros=100; // Agua por defecto
    char respuesta;
    int tipoEmpleado;

    cout << "\nIngrese el nombre de la planta: \n";
    cin.ignore();
    getline(cin, nombrePlanta);

    int opcion, cantidad;
    double precio;
    string NombreEmpleado;


    while (true)
    {

        respuesta=obtenerRespuestaSN("\n¿Desea agregar frutas a la planta? (s/n): ");


        if (respuesta=='n'||respuesta=='N')break;

        if (respuesta=='s'|| respuesta=='S')
        {

            opcion=NumeroValido("\nSeleccione una fruta para agregar:\n"
                                         "1. Limon\n2. Naranja\n3. Piña\n4. Sandia\n5. Fresa\n6. Tamarindo\n7. Coco\n8. Terminar\n"
                                    "Opcion: ", 1, 8);

            if(opcion==8)break;

            cantidad=NumeroValido("Ingrese la cantidad de la fruta: ", 1, 1000);
            precio=NumeroTemplate("Ingrese el precio por unidad de la fruta: ", 1.0, 100.0);

            inventarioFrutas.push_back(Frutas(static_cast<Frutas::Fruta>(opcion),precio,cantidad));
            cout<<"Se agregaron "<<cantidad<<" unidades de la fruta "<<opcion<<" aun precio de $"<<precio;

          
        }
    }

    respuesta=obtenerRespuestaSN("\nEl capital inicial de la planta es de $10,000. ¿Desea agregar mas dinero? (s/n): ");
    if(respuesta=='s'||respuesta=='S')
    {

        capitalAdicional=NumeroTemplate("Ingrese la cantidad a adicionar: ",1.0,50000.0);
        capitalInicial+=capitalAdicional;

    }

    //aqui se agregan los empleados
    cantidadEmpleados=NumeroValido("\nIngrese la cantidad de empleados a contratar (maximo de planta 50): ",1,50);

    vector<string> nombresGenerados=ObtenerNombresAleatorios(cantidadEmpleados);

    for(int i=0;i<cantidadEmpleados;i++)
    {
        
        NombreEmpleado=nombresGenerados[i];
        tipoEmpleado=rand()%3;
        Empleado* NuevoEmpleado;//Puntero

        if (tipoEmpleado==0)
        {
            
            NuevoEmpleado=new EmpleadoTecnico(NombreEmpleado);
            NuevoEmpleado->setSalario(2500);

        }else if (tipoEmpleado==1){
         
            NuevoEmpleado=new EmpleadoSuperVisor(NombreEmpleado);
            NuevoEmpleado->setSalario(3500);

        }else if(tipoEmpleado==2){

            NuevoEmpleado=new EmpleadoOperario(NombreEmpleado);
            NuevoEmpleado->setSalario(1800);
            
        }
        
        empleados.push_back(NuevoEmpleado);// con el pushbac se agrega nuevos elementos

    }

    //aqui se confuiguran las maquinas
    maquinas.push_back(new Extractor());
    maquinas.push_back(new Pasteurizador());
    maquinas.push_back(new MaquinaLavadora());

    //aqui se asigna el estado aleatorio si esta bien o mal
    //auto sirve para la deduccion de autamtica de tipo ejem maquinas, se el "&" porque maquina no es una
    //copia, si no una referencia al elemento del vector
    for(auto &maquina : maquinas){ 

        bool estado=rand()%2;//50% de probabilidad de estar operativa o no
        maquina->setEnUso(estado);

    }
    
    

    // Mostrar configuracion final
    cout << "\n=============================\n";
    cout << "Configuracion inicial de la planta\n";
    cout << "=============================\n";
    cout << "Nombre de la planta: " << nombrePlanta << "\n";
    cout << "Capital inicial: $" << capitalInicial << "\n";
    cout << "Agua disponible: " << aguaLitros << " litros\n";
    // MOSTRAR EL ESTADO DE LAS MAQUINAS

    cout << "\nFrutas en inventario:\n";
    if(inventarioFrutas.empty())
    {

        cout << "No se agregaron frutas.\n";

    }else{

        for(const auto &fruta : inventarioFrutas)
        {

            cout << " " <<fruta.getNombre()<<" - Cantidad: "<<fruta.getCantidad()<<"\n";

        }
    }

    //aqui se muestran los empleados contratados
    cout<<"\nEmpleados contratados:\n ";
    for(const auto &empleadosfab : empleados)
    {
        
        empleadosfab->MostrarInfo();

    }

   
    cout<<"\nEstado de las maquinaaaaaas:\n ";
    cout<<"\nMaquinas agregadas\n";
    cout<<"Total: "<<maquinas.size()<<"\n";
    for(const auto &maquinasfab : maquinas ){

        cout<<" "<<maquinasfab->getNombre()<<" - Estado: "<<(maquinasfab->isEnUso()? "En BUEN estado" : "En MAL estado")<<"\n";

    }
    

}

void MiniMenu(){

    int opcionmini=0;
    //Gestor_De_Planta gestor; no me ejecuta la instancia por el compilador 
  
    while (opcionmini!=5)
    {
        
        cout<<"1. Listar Planta";
        cout<<"2. Eliminar Empleados";
        cout<<"3. Espacio de Maquinas";
        cout<<"4. Comprar Frutas";
        cout<<"5. Ver pedidos";
        cout<<"6. Volver";
        cout<<"Ingrese una opcion: ";
        cin>>opcionmini;
        
    
        if(opcionmini==1)
        {
            
            //listar empleados contratados
            cout<<"\nEmpleados activos:\n ";
            for(const auto &empleadosfab : empleados)
            {
        
                empleadosfab->MostrarInfo();

            }

    
        }else if (opcionmini==2){
    
            //AGREGAR FUNCION
            
        }else if(opcionmini==3){
        
            //AGREGAR FUNCION
            
        }else if(opcionmini==4){
    
            //AGREGAR FUNCION
    
        }else if(opcionmini==5){
    
            //AGREGAR FUNCION

        }else{
    
            cout<<"Opcion invalida";
    
        }

    }
        
    
    

}

void MenuPrincipal()
{

    int opcion;

    while (opcion != 5)
    {
        cout << "\n**Menu**" << endl;
        cout << "1. Configurar parametros iniciales para la simulacion" << endl;
        cout << "2. Ejecutar simulacion paso a paso continua" << endl;
        cout << "3. Generar reportes del estado de la planta" << endl;
        cout << "4. Guardar y Cargar simulaciones desde archivos" << endl;
        cout << "5. Salir del programa" << endl;
        cout << "Escoja una opcion: ";
        cin >> opcion;

        if (opcion == 1)
        {

            ConfigurarParametrosIniciales();

        }else if (opcion == 2){

            MiniMenu();
           

        }else if (opcion == 3){

            //AGREGAR FUNCION

        }else if (opcion == 4){

            //AGREGAR FUNCION

        }else if (opcion == 5){

            cout << "Proyecto terminado" << endl;

        }else{

            cout << "Opcion no valida" << endl;
        }
    }
}


int main()
{

    MenuPrincipal();

    return 0;
}
