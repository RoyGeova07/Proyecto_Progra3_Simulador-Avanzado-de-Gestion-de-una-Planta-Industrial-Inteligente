#ifndef MAQUINA_H
#define MAQUINA_H

#include <string.h>
#include <string>
#include <iostream>

using String = std::string;

class Maquina
{
private:
    static int contadorID; // este es un contador estatico para generar IDs unicos
    int id;
    String nombre;
    String tipo;
    bool operativa;

public:
    Maquina(std::string nombre) : nombre(nombre), operativa(true)
    {
        id = ++contadorID;
    }

    void Encender() { this->operativa = true; }
    void Apagar() { this->operativa = false; }

    void MostrarInfo()
    {

        std::cout << "ID: " << this->id << " - Maquina: " << this->nombre << " - Tipo: " << this->tipo << " - Estado: " << (this->operativa ? "En uso" : "Apagada") << std::endl;
    }

    int getId() const { return id; }
    String getNombre() const { return nombre; }
    String getTipo() const { return tipo; }
    bool isEnUso() const { return operativa; }

    void setNombre(const String &Nuevonombre) { nombre = Nuevonombre; }
    void setTipo(const String &NuevoTipo) { tipo = NuevoTipo; }
    void setEnUso(bool estado) { operativa = estado; }

    virtual ~Maquina() {}
};

int Maquina::contadorID = 0;

#endif // MAQUINA_H