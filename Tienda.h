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

    void MenuTienda(Gestor_De_Planta &gestor);

private:
    
    void ComprarFrutas(Gestor_De_Planta &gestor);
    void ComprarConservantes(Gestor_De_Planta &gestor);

    void ComprarEnvases(Gestor_De_Planta &gestor);
    void ComprarAgua(Gestor_De_Planta &gestor);
};

#endif // TIENDA_H