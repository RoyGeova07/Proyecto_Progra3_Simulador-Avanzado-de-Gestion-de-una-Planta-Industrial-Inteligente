#ifndef MAQUINA_H
#define MAQUINA_H

#include <string.h>
#include <string>
#include <iostream>
#include "Gestor_De_Planta.h"
#include <chrono>
#include <ctime>//para convertir a string

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
    int VecesUsadas=0;
    int VecesReparadas=0;
    std::chrono::system_clock::time_point ultimaFechaUso;

public:
    Maquina(std::string nombre) : nombre(nombre), EstadoMaquina(true){}

    int getId() const { return id; }
    String getNombre() const { return nombre; }
    String getTipo() const { return tipo; }
    bool getEstado() const { return EstadoMaquina; }

    int getVecesUsadas()const{return VecesUsadas;}
    int getVecesReparada()const{return VecesReparadas;}

    void IncrementarUso(){

        VecesUsadas++;
        ActualizarFechaUso();
    
    }
    void IncrementarReparacion(){VecesReparadas++;}

    void ActualizarFechaUso(){

        ultimaFechaUso=std::chrono::system_clock::now();

    }

    std::string getUltimaFechaUso()const{

        if(ultimaFechaUso.time_since_epoch().count()==0)
        return "Nunca usada";

        std::time_t Tiempo=std::chrono::system_clock::to_time_t(ultimaFechaUso);
        return std::ctime(&Tiempo);//esto incluye salto de linea

    }

    std::chrono::system_clock::time_point getUltimaFechaUsoTP()const{

        return ultimaFechaUso;

    }

    void setUltimaFechaUsoTP(std::chrono::system_clock::time_point fecha){

        ultimaFechaUso=fecha;

    }

    void setNombre(const String &Nuevonombre) { this->nombre = Nuevonombre; }
    void setTipo(const String &NuevoTipo) {  this->tipo = NuevoTipo; }
    void setEnUso(bool estado) {  this->EstadoMaquina = estado; }
    static void MenuMaquinas(Gestor_De_Planta& gestor);
    virtual void VerEstadoMaquina()const{

        cout<<"\nMaquina: "<<nombre<<endl;
        cout<<" Estado: "<<(EstadoMaquina ? "En buen estado":"En mal estado")<<endl;
        cout<<" Veces usada: "<<VecesUsadas<<endl;
        cout<<" Veces Reparada: "<<VecesReparadas<<endl;
        cout<<" Ultimo uso: "<<getUltimaFechaUso()<<endl;
        cout<<"=================================================================================\n";
    
    }

    virtual ~Maquina() {}
};


#endif // MAQUINA_H