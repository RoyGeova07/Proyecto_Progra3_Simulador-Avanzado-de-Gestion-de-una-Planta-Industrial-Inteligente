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
    
public:

    int id;
    String nombre;
    String tipo;
    bool EnUso;

    Maquina(String nombre, String tipo, bool EnUso){

        this->id= ++contadorID;// Asigna un ID unico automáticamente
        this->nombre=nombre;
        this->tipo=tipo;
        this->EnUso=false;

    }

    void Encender() {this->EnUso = true;}
    void Apagar() {this->EnUso=false;}

    void MostrarInfo(){

        std::cout<<"ID: "<<this->id<<" - Maquina: "<<this->nombre<<" - Tipo: "<<this->tipo<<" - Estado: "<<(this->EnUso ? "En uso" : "Apagada") <<std::endl;   

    }
    
};


int Maquina::contadorID=0;


#endif //MAQUINA_H