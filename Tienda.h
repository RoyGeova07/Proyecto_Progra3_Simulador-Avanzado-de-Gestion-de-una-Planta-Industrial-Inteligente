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
    Tienda() = default;
    ~Tienda() = default;

    void MenuTienda(Gestor_De_Planta &gestor, double &capital);

private:
    
    void ComprarFrutas(Gestor_De_Planta &gestor, double &capital);
    void ComprarConservantes(Gestor_De_Planta &gestor, double &capital);

    void ComprarEnvases(Gestor_De_Planta &gestor, double &capital);
    void ComprarAgua(Gestor_De_Planta &gestor, double &capital);
};

#endif // TIENDA_H
