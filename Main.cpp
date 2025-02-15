#include <iostream>
#include <conio.h>
#include <string>
#include <string.h>
#include <limits>
#include <stdlib.h>

using namespace std;

void MenuPrincipal(){

    int opcion;

    while (opcion!=5)
    {
        cout<<"\n**Menu**"<<endl;
        cout<<"1. Configurar parametros iniciales para la simulacion"<<endl;
        cout<<"2. Ejecutar simulacion paso a paso continua"<<endl;
        cout<<"3. Generar reportes del estado de la planta"<<endl;
        cout<<"4. Guardar y Cargar simulaciones desde archivos"<<endl;
        cout<<"5. Salir del programa"<<endl;
        cout<<"Escoja una opcion: ";
        cin>>opcion;

        if (opcion==1)
        {
            


        }else if(opcion==2){
            


        }else if(opcion==3){
            


        }else if(opcion==4){



        }else if(opcion==5){

            cout<<"Proyecto terminado"<<endl;

        }else{

            cout<<"Opcion no valida"<<endl;

        }
        
        
    }
    

    

}

void Menu_De_Planta(){

    int opcion1;

    cout << "\n=============================\n";
    cout << "  MEnu de la planta\n";
    cout << "=============================\n";
    cout << "1. Agregar Ingrediente\n";
    cout << "2. Agregar Producto\n";
    cout << "3. Agregar Empleado\n";
    cout << "4. Agregar Maquina\n";
    cout << "5. Ver Ingredientes\n";
    cout << "6. Ver Productos\n";
    cout << "7. Ver Empleados\n";
    cout << "8. Ver Maquinas\n";
    cout << "9. Salir\n";
    cout << "Seleccione una opcion: ";
    cin>>opcion1;

    if (opcion1==1)
    {
        


    }else if(opcion1==2){
        


    }else if(opcion1==3){
        


    }else if(opcion1==4){



    }else if(opcion1==5){

        

    }else if(opcion1==6){


    }else if(opcion1==7){



    }else if(opcion1==8){



    }else if(opcion1==9){

        cout<<"Saliendo del menu de la planta"<<endl;

    }else{

        cout<<"Opcion no valida"<<endl;

    }

}



int main(){

    MenuPrincipal();

    return 0;
}