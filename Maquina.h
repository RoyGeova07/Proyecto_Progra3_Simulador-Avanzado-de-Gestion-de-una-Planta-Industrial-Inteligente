#ifndef MAQUINA_H
#define MAQUINA_H

#include <string.h>
#include <string>
#include <iostream>
#include "Gestor_De_Planta.h"

using String = std::string;

using namespace std;

// ya explique porque agrego esto xd ve a -> Gestor_De_Planta.h
class Gestor_De_Planta;

class Maquina
{
private:

    int id;
    String nombre;
    String tipo;
    bool EstadoMaquina=true;

public:
    Maquina(std::string nombre) : nombre(nombre), EstadoMaquina(true){}

    int getId() const { return id; }
    String getNombre() const { return nombre; }
    String getTipo() const { return tipo; }
    bool getEstado() const { return EstadoMaquina; }

    void setNombre(const String &Nuevonombre) { this->nombre = Nuevonombre; }
    void setTipo(const String &NuevoTipo) {  this->tipo = NuevoTipo; }
    void setEnUso(bool estado) {  this->EstadoMaquina = estado; }
    static void MenuMaquinas(Gestor_De_Planta& gestor);
    virtual void VerEstadoMaquina() const{ 

        cout<<"Maquina: "<<nombre<<" | Estado: "<<(EstadoMaquina? "En buen estado": "En mal estado")<<endl;

    };

    virtual ~Maquina() {}
};


#endif // MAQUINA_H