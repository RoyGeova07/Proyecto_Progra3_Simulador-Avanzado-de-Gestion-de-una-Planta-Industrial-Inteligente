#ifndef EMPLEADO_H
#define EMPLEADO_H

#include <iostream>
#include <string>

class Empleado
{
protected:
    std::string nombre;
    int id;
    int salario;
    std::string cargo;
    static int contadorID;
    int dineroGanado=0;

public:
    Empleado(const std::string &nombre, const std::string &cargo)
        : nombre(nombre), cargo(cargo), id(++contadorID),salario(0),dineroGanado(0) {} // Asigna un ID unico automaticamente

    virtual void MostrarInfo() const
    {

        std::cout << "ID: " << id << " - Nombre: " << nombre << " - Cargo: " << cargo <<" - Salario: "<<salario<<"- Pagado: $"<<dineroGanado<<std::endl;
            
    }

    

    virtual void RealizarTarea() = 0; // funciona pura (obligatorio en subclases)
    virtual ~Empleado() = default;    // Destructor virtual

    // Getters
    int getId() const { return id; }
    std::string getNombre() const { return nombre; }
    std::string getCargo() const { return cargo; }
    int getSalario() const {return salario;}
    void AgregarPago(int cantidad) {dineroGanado+=cantidad;}
    int getDineroGanado()const {return dineroGanado;}
    void setId(int NuevoId){ id=NuevoId;}

    void setSalario(int nuevoSalario){

        this->salario=nuevoSalario;  

    }
    void setDineroGanado(int NuevoDineroGanada){dineroGanado=NuevoDineroGanada;}
    void setCargo(std::string NuevoCargo){cargo=NuevoCargo;}

};



#endif // EMPLEADO_H