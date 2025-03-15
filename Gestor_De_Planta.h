#ifndef GESTOR_DE_PLANTA_H
#define GESTOR_DE_PLANTA_H

#include <iostream>
#include <vector>
#include <string>
#include <string.h>
#include "Frutas.h"
#include "Producto.h"
#include "Maquina.h"
#include "Empleado.h"

//declaro esta clase aqui porque tenia un error de circulo de dependencias (circular dependency) entre Maquina.h y Gestor_De_Planta.h.
//pasa porque Gestor_De_Planta.h incluye a Maquina.h porque tiene un vector<Maquina*>.
//Maquina.h incluye a Gestor_De_Planta.h porque MenuMaquinas tiene un parametro Gestor_De_Planta& gestor.
//Maquina.h necesita Gestor_De_Planta.h
//Gestor_De_Planta.h necesita Maquina.h
//Esto hace que el compilador no sepa que archivo incluir primero.
//la solucion es Declarar class Maquina; en Gestor_De_Planta.h para que el compilador sepa que Maquina es una clase, sin necesidad de incluir toda la definicion de Maquina.
class Maquina;

//Gestor_De_Planta ya no incluye directamente Maquina.h.
//Maquina.h ya no incluye directamente Gestor_De_Planta.h.
//Se resuelve el conflicto circular usando class Maquina; y class Gestor_De_Planta;.

class Gestor_De_Planta
{
private:
  
    std::vector<Producto> productos;
    std::vector<Frutas> FRUTAS;
    std::vector<Frutas> FRUTAS_LAVADAS;
    std::vector<Maquina*> maquinas;
    std::vector<Empleado*> empleado;
    double CapitalInicial=100000;
    int AguaLitros=100;

public:

    Gestor_De_Planta()=default;
    ~Gestor_De_Planta();    

    void AgregarEmpleado(Empleado* emp);
    void AgregarMaquina(Maquina* maq);
    void listarEmpleados() const;
    void listarProductos() const;
    void ListarFrutas() const;
    void VerEstadoMaquina() const;
    void eliminarEmpleado(int id);
    Empleado* BuscarEmpleadoPorId(int id);
    int CantidadEmpleados() const;
    
    void TransferirFrutaLavada(const Frutas& fruta);
    void ListarFrutasLavadas()const;
    void ListaJugosFaltanIngredientesYEnvases()const;
    void AgregarFruta(const Frutas& fruta);
    void mostrarEstadoInicial(const std::string& nombrePlanta) const;
    double getCapital() const { return CapitalInicial; }
    void agregarCapital(double adicional) { CapitalInicial += adicional; }
    void setAgua(int litros) { AguaLitros = litros; }
    int getAgua()const{ return AguaLitros;}
    void MiniMenuGestor();
    void ReducirAgua(double litros);

    std::vector<Maquina*>& getMaquinas() { return maquinas; }
    std::vector<Frutas>& getInventarioFrutas() { return FRUTAS; }
    std::vector<Empleado*>& getEmpleados() { return empleado; }
    

    void empacar();

    void generarReporte() const;
    
    

};


#endif //GESTOR_DE_PLANTA_H