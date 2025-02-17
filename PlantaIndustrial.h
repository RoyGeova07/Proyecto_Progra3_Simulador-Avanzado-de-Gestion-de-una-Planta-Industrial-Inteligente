#ifndef PLANTA_H
#define PLANTA_H

#include <iostream>
#include <string>
#include <vector>



class PlantaIndustrial
{
private:
    
    int cantidadEmpleados;
    int Dinero_De_la_Planta;
    int dia;
    std::string nombrePlanta;


public:

    //Aqui el constructor de la clase
    PlantaIndustrial(std::string nombre, int empleados,int Dinero, int diaActual) 
    : nombrePlanta(nombre),cantidadEmpleados(empleados),Dinero_De_la_Planta(Dinero),dia(diaActual){

        std::cout<<"Planta Industrial creada: "<<nombrePlanta<<"\n";

    }

    //getter
    int getCantidadEmpleados() const {return cantidadEmpleados;}
    int getDineroDeLaPlanta() const {return Dinero_De_la_Planta;}
    int dia() const {return dia;}
    std::string getNombrePlanta() const {return nombrePlanta;}

    
};


#endif //PLANTA_H
