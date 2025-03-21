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
    std::vector<Producto> JUGOS_SIN_INGREDIENTES;
    std::vector<Producto> JUGOS_DISPONIBLES;
    std::vector<Maquina*> maquinas;
    std::vector<Empleado*> empleado;
    double CapitalInicial=100000;
    double AguaLitros=100;
    int Envases=50;
    int Conservantes=50;

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
    void ListaJugosDisponibles()const;
    void AgregarFruta(const Frutas& fruta);
    void AgregarJugosSinIngredientesYEnvases(const Producto& jugo);
    void AgregarJugosDisponibles(const Producto& jugo,int cantidad);
    void mostrarEstadoInicial(const std::string& nombrePlanta) const;
    double getCapital() const { return CapitalInicial; }
    void agregarCapital(double adicional) { CapitalInicial += adicional; }
    void AgregarMasEnvases(int MasEnvases){Envases+=MasEnvases;}
    void AgregarMasConservantes(int MasConservantes){Conservantes+=MasConservantes;}
    void setAgua(int litros) { AguaLitros = litros; }
    int getAgua()const{return AguaLitros;}
    int getEnvases()const{return Envases;}
    int getConservantes()const {return Conservantes;}
    void MiniMenuGestor();
    void ReducirAgua(double litros);
    void AgregarAwuita(double MasAwuita){AguaLitros+=MasAwuita;}

    void EliminarJugoSinIngredientes(const std::string& nombreJugo);

    std::vector<Maquina*>& getMaquinas() { return maquinas; }
    std::vector<Frutas>& getInventarioFrutas() { return FRUTAS; }
    std::vector<Producto>& getInventarioJugosSinIngredientes() {return JUGOS_SIN_INGREDIENTES;}
    std::vector<Producto>& getInventarioJugos() {return JUGOS_DISPONIBLES;}
    std::vector<Empleado*>& getEmpleados() { return empleado; }
    

    void empacar();

    void generarReporte() const;
    
    

};


#endif //GESTOR_DE_PLANTA_H