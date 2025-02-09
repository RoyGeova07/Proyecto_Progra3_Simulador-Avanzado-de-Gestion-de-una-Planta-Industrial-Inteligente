#include <iostream>
#include <conio.h>
#include <string>
#include <string.h>
#include <limits>
#include <stdlib.h>

using namespace std;

void Menu(){

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

int main(){

    Menu();

    return 0;
}