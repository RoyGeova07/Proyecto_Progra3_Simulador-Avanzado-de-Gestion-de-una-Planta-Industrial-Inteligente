#ifndef MAQUINA_H
#define MAQUINA_H


#include <string.h>
#include <string>
#include <iostream>

using String = std::string;

class Maquina
{
private:

    static int contadorID;//este es un contador estatico para generar IDs unicos
    int id;
    String nombre;
    String tipo;
    bool EnUso;
    
public:

    

    Maquina(const String &nombre, const String &tipo, bool EnUso = false)
    : id(++contadorID), nombre(nombre), tipo(tipo), EnUso(EnUso) {}

    void Encender() {this->EnUso = true;}
    void Apagar() {this->EnUso=false;}

    void MostrarInfo(){

        std::cout<<"ID: "<<this->id<<" - Maquina: "<<this->nombre<<" - Tipo: "<<this->tipo<<" - Estado: "<<(this->EnUso ? "En uso" : "Apagada") <<std::endl;   

    }

    int getId() const {return id;}
    String getNombre() const {return nombre;}
    String getTipo() const {return tipo;}
    bool isEnUso() const {return EnUso;}

    void setNombre(const String &Nuevonombre) {nombre=Nuevonombre;}
    void setTipo(const String &NuevoTipo) {tipo=NuevoTipo;}
    void setEnUso(bool estado) { EnUso = estado; } 
    
};


int Maquina::contadorID=0;


#endif //MAQUINA_H