#ifndef GESTOR_DE_PLANTA_H
#define GESTOR_DE_PLANTA_H

#include <iostream>
#include <vector>
#include <string>
#include "Frutas.h"
#include "Producto.h"
#include "Maquina.h"
#include "Empleado.h"

class Gestor_De_Planta
{
private:

    std::vector<Producto> productos;
    std::vector<Frutas>   FRUTAS;
    std::vector<Maquina*> maquinas;
    std::vector<Empleado*> empleado;


    std::vector<std::string> logProgreso;

public:

    Gestor_De_Planta() = default;
    ~Gestor_De_Planta();


    void agregarFruta(const Frutas &f);
    void agregarEmpleado(Empleado* emp);
    void agregarMaquina(Maquina* m);


    void listarEmpleados() const;
    void listarProductos() const;
    void ListarFrutas() const;
    void VerEstadoMaquina() const;


    void eliminarEmpleado(int id);


    void lavarFrutas();
    void extraerJugo();
    void pasteurizar();
    void empacar();


    void generarReporte() const;
};

#endif // GESTOR_DE_PLANTA_H