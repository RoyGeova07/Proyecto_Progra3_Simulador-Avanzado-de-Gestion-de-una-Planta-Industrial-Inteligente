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
#include "NumeroValido.h"


using namespace std;

bool ParametrosConfigurados=false;


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

void MiniMenuDos(Gestor_De_Planta& gestor){

    int opcion;
    

    cout<<"\nMenu de maquinas\n";
    cout<<"1. Maquina Lavadora\n";
    cout<<"2. Extractor\n";
    cout<<"3. Pasteurizador\n";
    cout<<"4. Volver\n";
    opcion=NumeroValido("Ingrese una opcion: ",1,4);


    if (opcion==1)
    {
        
        //aqui buscamos la lavadora que cree en el gestor
        MaquinaLavadora* lavadora=nullptr;

        for(auto& maquina:gestor.getMaquinas()){

            lavadora=dynamic_cast<MaquinaLavadora*>(maquina);
            if(lavadora)break;//se encontroooooo

        }

        if(lavadora){

            lavadora->MenuMaquinaLavadora(gestor.getInventarioFrutas(),gestor.getEmpleados());

        }else{

            cout<<"No se encontro la lavadora en el sistema.\n";

        }


    }else if (opcion==2){
        


    }else if(opcion==3){



    }else if(opcion==4){

        return;

    }
    

}

void ConfigurarParametrosIniciales(Gestor_De_Planta& gestor)
{

    srand(time(0));//aqui se inicializa el random
    

    string nombrePlanta;
    double capitalAdicional;
    int cantidadEmpleados;

    char respuesta;
    int tipoEmpleado;

    cout << "\nIngrese el nombre de la planta: \n";
    cin.ignore();
    getline(cin, nombrePlanta);

    int opcion, cantidad;
    double precio;


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

    //aqui se agregan los empleados
    cantidadEmpleados=NumeroValido("\nIngrese la cantidad de empleados a contratar (maximo de planta 50): ",1,50);

    vector<string> nombresGenerados=ObtenerNombresAleatorios(cantidadEmpleados);

    for(const auto& nombre:nombresGenerados)
    {

        tipoEmpleado=rand()%3;
        Empleado* NuevoEmpleado;//Puntero

        if (tipoEmpleado==0)
        {
            
            NuevoEmpleado=new EmpleadoTecnico(nombre);
            NuevoEmpleado->setSalario(2500);

        }else if (tipoEmpleado==1){
         
            NuevoEmpleado=new EmpleadoSuperVisor(nombre);
            NuevoEmpleado->setSalario(3500);

        }else if(tipoEmpleado==2){

            NuevoEmpleado=new EmpleadoOperario(nombre);
            NuevoEmpleado->setSalario(1800);
            
        }
        gestor.AgregarEmpleado(NuevoEmpleado);
      
    }

    MaquinaLavadora* lavadora=new MaquinaLavadora();
    lavadora->setEnUso(rand()%2==0);
    gestor.AgregarMaquina(lavadora);

    //HACER LO MISMO CON LAS 2 MAQUINAS, DESPUES DE AGREGAR SU RESPECTIVO ARCHIVO CPP
    //HACER LO MISMO CON LAS 2 MAQUINAS, DESPUES DE AGREGAR SU RESPECTIVO ARCHIVO CPP
    //HACER LO MISMO CON LAS 2 MAQUINAS, DESPUES DE AGREGAR SU RESPECTIVO ARCHIVO CPP
    //HACER LO MISMO CON LAS 2 MAQUINAS, DESPUES DE AGREGAR SU RESPECTIVO ARCHIVO CPP
    gestor.AgregarMaquina(new Extractor());
    gestor.AgregarMaquina(new Pasteurizador());
    
    // Mostrar configuracion final
    cout << "\n=============================\n";
    cout << "Configuracion inicial de la planta\n";
    cout << "=============================\n";
    cout << "Nombre de la planta: " << nombrePlanta << "\n";
    cout << "Capital inicial: $" << gestor.getCapital() << "\n";
    cout << "Agua disponible: " << gestor.getAgua() << " litros\n";
    // MOSTRAR EL ESTADO DE LAS MAQUINAS

    cout << "\nFrutas en inventario:\n";
    gestor.ListarFrutas();


    //aqui se muestran los empleados contratados
    cout<<"\nEmpleados contratados:\n ";
    gestor.listarEmpleados();

   
    cout<<"\nEstado de las maquina:\n ";
    gestor.VerEstadoMaquina();
    

}

void MiniMenu(Gestor_De_Planta& gestor){

    int opcionmini=0;
  
    while (opcionmini!=5)
    {
        cout<<"\n**Menu de la planta**\n";
        cout<<"1. Listar Planta\n";
        cout<<"2. Despedir Empleados\n";
        cout<<"3. Espacio de Maquinas\n";
        cout<<"4. Comprar Frutas\n";
        cout<<"5. Ver pedidos\n";
        cout<<"6. Volver\n";
        cout<<"Ingrese una opcion: ";
        cin>>opcionmini;
        
    
        if(opcionmini==1)
        {
            
            //listar empleados contratados
            cout<<"\nEmpleados activos:\n ";
            gestor.listarEmpleados();

            //aqui se listas las frutas
            cout<<"\nFrutas en inventario:\n";
            gestor.ListarFrutas();

            cout<<"\nAgua disponible: "<<gestor.getAgua()<<" litros\n";
            
            cout<<"\nEstado de las maquinas actualmente:\n";
            gestor.VerEstadoMaquina();
    
        }else if (opcionmini==2){
            int id;
    
           //listar empleados contratados
           cout<<"\nEmpleados activos:\n ";
            gestor.listarEmpleados();


           
           id=NumeroValido("Ingrese el ID del empleado a despedir: ",1,50);
           
           gestor.eliminarEmpleado(id);

           gestor.listarEmpleados();

            
        }else if(opcionmini==3){
        
            MiniMenuDos(gestor);
            
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
    Gestor_De_Planta gestor;

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

            ConfigurarParametrosIniciales(gestor);
            ParametrosConfigurados=true;

        }else if (opcion == 2){

            if (!ParametrosConfigurados)
            {
                
                cout<<"\nERROR: Debe configurar los parametros iniciales antes de ejecutar la simuacion\n";

            }else{

                MiniMenu(gestor);

            }
            

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
