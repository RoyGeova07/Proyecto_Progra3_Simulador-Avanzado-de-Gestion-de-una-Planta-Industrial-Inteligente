#include <iostream>
#include <conio.h>
#include <string>
#include <string.h>
#include <limits>
#include <stdlib.h>
#include <Frutas.h>
#include <ctime>
#include <cstdlib>//para seed random
#include "Empleado.h"
#include <EmpleadoTecnico.h>
#include <EmpleadoOperario.h>
#include <EmpleadoSupervisor.h>
#include <Maquina.h>
#include <MaquinaLavadora.h>
#include <Pasteurizador.h>
#include <Extractor.h>


using namespace std;

int NumeroValido(string mensaje,int minimo,int maximo){

    int valor;
    while (true)
    {

        cout<<mensaje;
        cin>>valor;

        if (cin.fail() ||valor<minimo||valor>maximo)
        {
            
            cin.clear();
            cin.ignore(10000,'\n');
            cout<<"Error: Entrada no valida. Intente de nuevo: \n";

        }else{

            return valor;

        }
        

    }
    

}

string GenerarNombreAleatorio(){

    vector<string> nombres = {"Carlos", "Maria", "Juan", "Ana", "Luis", "Elena", "Pedro", "Carmen", "Jose", "Sofia"};
    vector<string> apellidos = {"Gonzalez", "Fernandez", "Lopez", "Martinez", "Rodriguez", "Perez", "Sanchez", "Diaz", "Vega", "Ruiz"};

    return nombres[rand()%nombres.size()]+ " "+apellidos[rand()%apellidos.size()];

}

char obtenerRespuestaSN(string mensaje) {

    char respuesta;
    while (true) {

        cout << mensaje;
        cin >> respuesta;
        respuesta = tolower(respuesta);  
        if (respuesta == 's' || respuesta == 'n') return respuesta;
        cout << "Entrada invalida. Ingrese 's' para si o 'n' para no.\n";

    }

}

void ConfigurarParametrosIniciales()
{

    srand(time(0));//aqui se inicializa el random

    string nombrePlanta;
    double capitalInicial = 10000;
    double capitalAdicional;
    vector<Frutas> inventarioFrutas;
    vector<Empleado*> empleados;
    vector<Maquina*> maquinas;
    int cantidadEmpleados;

    int aguaLitros = 100; // Agua por defecto
    char respuesta;
    int tipoEmpleado;

    cout << "\nIngrese el nombre de la planta: \n";
    cin.ignore();
    getline(cin, nombrePlanta);

    int opcion, cantidad;
    double precio;
    char respuesta2;
    string NombreEmpleado;


    while (true)
    {
        respuesta=obtenerRespuestaSN("\n¿Desea agregar frutas a la planta? (s/n): ");


        if (respuesta =='n'||respuesta=='N')break;

        if (respuesta=='s'|| respuesta=='S')
        {

            opcion=NumeroValido("\nSeleccione una fruta para agregar:\n"
                                         "1. Limon\n2. Naranja\n3. Piña\n4. Sandia\n5. Fresa\n6. Tamarindo\n7. Coco\n8. Terminar\n"
                                    "Opcion: ", 1, 8);
            cin >> opcion;

            if (opcion==8) break;

            cantidad=NumeroValido("Ingrese la cantidad de la fruta: ", 1, 1000);
            precio=NumeroValido("Ingrese el precio por unidad de la fruta: ", 1, 100);

            inventarioFrutas.push_back(Frutas(static_cast<Frutas::Fruta>(opcion),precio,cantidad));
            cout<<"Se agregaron "<<cantidad<<"unidades de la fruta seleccionada aun precio de $";

          
        }
    }

    respuesta2=obtenerRespuestaSN("\nEl capital inicial de la planta es de $10,000. ¿Desea agregar mas dinero? (s/n): ");
    cin >> respuesta;
    if (respuesta == 's' || respuesta == 'S')
    {

        capitalAdicional=NumeroValido("Ingrese la cantidad a adicionar: ",0,50000);
        capitalInicial+=capitalAdicional;

    }

    //aqui se agregan los empleados
    cantidadEmpleados=NumeroValido("\nIngrese la cantidad de empleados a contratar (maximo de planta 50): ",1,50);

    for (int i = 0; i < cantidadEmpleados; i++)
    {
        
        NombreEmpleado=GenerarNombreAleatorio();
        tipoEmpleado=rand()%3;
        Empleado* NuevoEmpleado;//Puntero

        if (tipoEmpleado==0)
        {
            
            NuevoEmpleado = new EmpleadoTecnico(NombreEmpleado);
            NuevoEmpleado->setSalario(2500);

        }else if (tipoEmpleado==1){
         
            NuevoEmpleado=new EmpleadoSuperVisor(NombreEmpleado);
            NuevoEmpleado->setSalario(3500);

        }else if(tipoEmpleado==2){

            NuevoEmpleado=new EmpleadoOperario(NombreEmpleado);
            NuevoEmpleado->setSalario(1800);
            
        }
        
        empleados.push_back(NuevoEmpleado);

    }

    //aqui se confuiguran las maquinas
    maquinas.push_back(new Extractor());
    maquinas.push_back(new Pasteurizador());
    maquinas.push_back(new MaquinaLavadora());

    //aqui se asigna el estado aleatorio si esta bien o mal
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

    cout << "Frutas en inventario:\n";
    if (inventarioFrutas.empty())
    {

        cout << "No se agregaron frutas.\n";

    }else{

        for (const auto &fruta : inventarioFrutas)
        {

            cout << " " << fruta.getNombre() << " - Cantidad: " << fruta.getCosto() << "\n";
        }
    }

    //aqui se muestran los empleados contratados
    cout<<"\nEmpleados contratados:\n ";
    for (const auto &empleadosfab : empleados)
    {
        
        empleadosfab->MostrarInfo();

    }

    cout<<"\nEstado de las maquins:\n ";
    for(const auto &maquinasfab : maquinas ){

        cout<<" "<<maquinasfab->getNombre()<<" - Estado: "<<(maquinasfab->isEnUso()? "En BUEN estado" : "En MAL estado")<<"\n";

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

            //AGREGAR FUNCION

        }
        else if (opcion == 2)
        {

            //AGREGAR FUNCION

        }
        else if (opcion == 3)
        {

            //AGREGAR FUNCION

        }
        else if (opcion == 4)
        {

            //AGREGAR FUNCION

        }
        else if (opcion == 5)
        {

            cout << "Proyecto terminado" << endl;
        }
        else
        {

            cout << "Opcion no valida" << endl;
        }
    }
}

void Menu_De_Planta()
{

    int opcion1;

    cout << "\n=============================\n";
    cout << "  Menu de la planta\n";
    cout << "=============================\n";
    cout << "1. Agregar Empleado\n";
    cout << "2. Ver Ingredientes\n";
    cout << "3. Ver Productos\n";
    cout << "4. Ver Empleados\n";
    cout << "5. Ver estado de las Maquinas\n";
    cout << "6. Salir\n";
    cout << "Seleccione una opcion: ";
    cin >> opcion1;

    if (opcion1 == 1)
    {
    }
    else if (opcion1 == 2)
    {
    }
    else if (opcion1 == 3)
    {
    }
    else if (opcion1 == 4)
    {
    }
    else if (opcion1 == 5)
    {
    }
    else if (opcion1 == 6)
    {
    }
    else if (opcion1 == 7)
    {
    }
    else if (opcion1 == 8)
    {
    }
    else if (opcion1 == 9)
    {

        cout << "Saliendo del menu de la planta" << endl;
    }
    else
    {

        cout << "Opcion no valida" << endl;
    }
}

int main()
{

    MenuPrincipal();

    return 0;
}