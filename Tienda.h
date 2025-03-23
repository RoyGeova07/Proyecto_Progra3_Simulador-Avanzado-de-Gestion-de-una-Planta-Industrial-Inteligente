#ifndef TIENDA_H
#define TIENDA_H

#include <iostream>
#include <string>
#include <vector>
#include "Gestor_De_Planta.h"
#include "Frutas.h"
#include "Producto.h"


class Tienda
{
public:
    Tienda()=default;
    ~Tienda()=default;
    int FrutasCompradas=0;
    int Pilla=0;
    int Fresa=0;
    int Coco=0;
    int Tamarindo=0;
    int Naranja=0;
    int Sandia=0;
    int Limon=0;
    int ConservantesComprados=0;
    int EnvasesComprados=0;
    int AguaComprada=0;
    double DineroGastadoEnTodaLaTienda=0.0;


    void MenuTienda(Gestor_De_Planta &gestor);
    
    int getPilla()const{return Pilla;}
    int getNaranja()const{return Naranja;}
    int getSandia()const{return Sandia;}
    int getFresa()const{return Fresa;}
    int getCoco()const{return Coco;}
    int getLimon()const{return Limon;}
    int getTamarindo()const{return Tamarindo;}
    int getConservantesComprados()const{return ConservantesComprados;}
    int getEnvasesComprados()const{return EnvasesComprados;}
    int getAguaComprada()const{return  AguaComprada;}
    int getFrutasCompradas()const{return FrutasCompradas;}
    double getDineroGastadoEnTodaLatienda()const{return DineroGastadoEnTodaLaTienda;}

private:
    
    void ComprarFrutas(Gestor_De_Planta &gestor);
    void ComprarConservantes(Gestor_De_Planta &gestor);

    void ComprarEnvases(Gestor_De_Planta &gestor);
    void ComprarAgua(Gestor_De_Planta &gestor);


};

#endif // TIENDA_H