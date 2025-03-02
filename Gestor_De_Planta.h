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


class Gestor_De_Planta
{
private:
  
    std::vector<Producto> productos;
    std::vector<Frutas> FRUTAS;
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
    
    void AgregarFruta(const Frutas& fruta);
    void mostrarEstadoInicial(const std::string& nombrePlanta) const;
    double getCapital() const { return CapitalInicial; }
    void agregarCapital(double adicional) { CapitalInicial += adicional; }
    void setAgua(int litros) { AguaLitros = litros; }
    int getAgua() const { return AguaLitros; }

    std::vector<Maquina*>& getMaquinas() { return maquinas; }
    std::vector<Frutas>& getInventarioFrutas() { return FRUTAS; }
    std::vector<Empleado*>& getEmpleados() { return empleado; }

    void empacar();

    void generarReporte() const;
    
    

};


#endif //GESTOR_DE_PLANTA_H