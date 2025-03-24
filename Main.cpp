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
#include "Maquina.h"
#include "MaquinaLavadora.h"
#include "Envasadora.h"
#include "ProcesadorFrutas.h"
#include "Frutas.h"
#include "Gestor_De_Planta.h"
#include <set>
#include <sstream>
#include <chrono>
#include "NumeroValido.h"
#include "filesystem"

namespace fs=std::filesystem;

using namespace std;

bool ParametrosConfigurados=false;
bool PrimerConfiguracion=true;

void AsegurarCarpetaReportes(){

    std::string carpeta = "Plantas Industriales";
    if(!fs::exists(carpeta)){

        fs::create_directory(carpeta);
        std::cout << "\n Carpeta 'Plantas Industriales' creada exitosamente.\n";

    }

}

//Clase template para obtener un numero de tipo T
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


void ConfigurarParametrosIniciales(Gestor_De_Planta& gestor)
{

    srand(time(0));//aqui se inicializa el random
    PrimerConfiguracion=false;

    string nombrePlanta;
    double capitalAdicional ;
    int cantidadEmpleados;
    int Envases=0;
    int Conservantes=0;
    int Agua=0;

    char respuesta;
    char respuesta2;
    char respuesta3;
    char respuesta4;
    int tipoEmpleado;

    cout << "\nIngrese el nombre de la planta: \n";
    getline(cin, nombrePlanta);
    gestor.setNombrePlanta(nombrePlanta);

    int opcion, cantidad;
    double precio;


    while (true)
    {

        respuesta=obtenerRespuestaSN("\n¿Desea agregar frutas a la planta? (s/n): ");


        if (respuesta=='n'||respuesta=='N')break;

        if (respuesta=='s'|| respuesta=='S')
        {

            opcion=NumeroValido("\nSeleccione una fruta para agregar:\n" "1. Limon\n2. Naranja\n3. Piña\n4. Sandia\n5. Fresa\n6. Tamarindo\n7. Coco\n8. Terminar\n""Opcion: ", 1, 8);

            if(opcion==8)break;

            cantidad=NumeroValido("Ingrese la cantidad de la fruta: ", 1, 1000);
            precio=NumeroTemplate("Ingrese el precio por unidad de la fruta: ", 1.0, 100.0);

            Frutas fruta(Frutas(static_cast<Frutas::Fruta>(opcion),precio,cantidad));
            gestor.AgregarFruta(fruta);
            cout<<"Se agregaron "<<cantidad<<" unidades de la fruta "<<opcion<<" aun precio de $"<<precio;

          
        }
    }

    respuesta=obtenerRespuestaSN("\nEl capital inicial de la planta es de $10,000. ¿Desea agregar mas dinero? (s/n): ");
    if(respuesta=='s'||respuesta=='S')
    {

        capitalAdicional=NumeroTemplate("Ingrese la cantidad a adicionar: ",1.0,50000.0);
        
    }
    gestor.agregarCapital(capitalAdicional);

    respuesta2=obtenerRespuestaSN("\nDisponemos con 50 envases. Quiere agregar mas? (s/n): ");
    if (respuesta2=='s'||respuesta2=='S')
    {
        
        Envases=NumeroValido("\nIngrese la cantidad de envases que quiere agregar (Maximo 100): ",1,100);

    }
    gestor.AgregarMasEnvases(Envases);

    respuesta3=obtenerRespuestaSN("\nTenemos 50 conservantes. Quieres agregar mas? (s/n): ");
    if(respuesta3=='s'||respuesta3=='S')
    {
        
        Conservantes=NumeroValido("\nIngrese la cantidad de conservantes a agregar (Maximo 50): ",1,50);

    }
    gestor.AgregarMasConservantes(Conservantes);

    respuesta4=obtenerRespuestaSN("\n Tenenemos 100 litros de agua. Quieres agregar mas? (s/n): ");
    if (respuesta4=='s'||respuesta4=='S')
    {
        
        Agua=NumeroTemplate("\nIngrese la cantidad agregar (Maximo: 1,000 litros ): ",1.0,1000.0);

    }
    gestor.AgregarAwuita(Agua);
    

    //aqui se agregan los empleados
    cantidadEmpleados=NumeroValido("\nIngrese la cantidad de empleados a contratar (maximo de planta 50): ",1,50);

    vector<string> nombresGenerados=ObtenerNombresAleatorios(cantidadEmpleados);

    for(const auto& nombre:nombresGenerados)

    {

        tipoEmpleado=rand()%2;
        Empleado* NuevoEmpleado;//Puntero

        if (tipoEmpleado==0)
        {
            
            NuevoEmpleado=new EmpleadoTecnico(nombre);
            NuevoEmpleado->setSalario(2500);

        }else if (tipoEmpleado==1){
         
            
            NuevoEmpleado=new EmpleadoOperario(nombre);
            NuevoEmpleado->setSalario(1800);

        }
        gestor.AgregarEmpleado(NuevoEmpleado);
      
    }

    MaquinaLavadora* lavadora=new MaquinaLavadora();
    lavadora->setEnUso(true);
    gestor.AgregarMaquina(lavadora);

    ProcesadorFrutas* procesarFrutas=new ProcesadorFrutas();
    procesarFrutas->setEnUso(true);
    gestor.AgregarMaquina(procesarFrutas);    

    Envasadora* envasadora=new Envasadora();
    envasadora->setEnUso(true);
    gestor.AgregarMaquina(envasadora);
    
    
    // Mostrar configuracion final
    cout<<"\n=============================\n";
    cout<<"Configuracion inicial de la planta\n";
    cout<<"=============================\n";
    cout<<"Nombre de la planta: " << gestor.getNombrePLanta() << "\n";
    cout<<"Capital inicial: $" << gestor.getCapital() << "\n";
    cout<<"Agua disponible: " << gestor.getAgua() << " litros\n";
    cout<<"Envases disponibles: "<<gestor.getEnvases()<<" Unidades \n";
    cout<<"Conservantes disponibles: "<<gestor.getConservantes()<<" Unidades \n";

    gestor.ListarFrutas(); 

    gestor.listarEmpleados();

    gestor.VerEstadoMaquina();

    gestor.MiniMenuGestor(gestor);

    cout<<"=================================================================================\n";

    gestor.MiniMenuGestor(gestor);
    
}


void MenuPrincipal()
{

    int opcion;
    Gestor_De_Planta gestor;

    while (opcion != 5)
    {
        cout << "\n**Menu**" << endl;
        cout << "1. Configurar parametros iniciales para la simulacion (Nueva Planta)" << endl;
        cout << "2. Cargar simulaciones desde archivos" << endl;
        cout << "3. Salir del programa" << endl;
        opcion=NumeroValido("Escoja una opcion: ",1,4);

        if (opcion == 1)
        {
            if (!PrimerConfiguracion)
            {
                
                cout<<"\nNo puedes volver a acceder a configurar los parametros\n";

            }else{

                ConfigurarParametrosIniciales(gestor);
                ParametrosConfigurados=true;

            }

        }else if (opcion==2){

            string nombre;
            cout<<"\nIngrese el nombre del archivo a cargar (ej: miplanta.bin): ";
            getline(cin,nombre);
            if(nombre.empty()){

                cout<<"Nombre invalido\n";
                continue;

            }

            string ruta = "Plantas Industriales guardadas/" + nombre;
            if(!fs::exists(ruta)){

                cout << "\nEl archivo '" << nombre << "' no existe en la carpeta de guardado.\n";
                continue;

            }
        
           gestor.CargarSimulacionBinario(nombre);
           ParametrosConfigurados = true;
           PrimerConfiguracion = false; // evita volver a configurar

           gestor.MiniMenuGestor(gestor);

        }else if (opcion == 3){

            cout << "Proyecto terminado" << endl;

        }else{

            cout << "Opcion no valida" << endl;
        }
    }
}

void AsegurarCarpetaGuardado() {
    string carpeta="Plantas Industriales guardadas";
    if(!fs::exists(carpeta)){

        fs::create_directory(carpeta);

    }
}

int main()
{

    AsegurarCarpetaGuardado();
    AsegurarCarpetaReportes();
    MenuPrincipal();

    return 0;
}
