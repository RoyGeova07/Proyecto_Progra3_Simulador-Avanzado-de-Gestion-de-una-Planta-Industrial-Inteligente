#include <iostream>
#include <vector>
using namespace std;

class MateriaPrima
{
private:
    string nombre;
    double cantidad;
    string unidad;

public:
    // aqui sobrecarga de operadores
    MateriaPrima(const string& nombre, double cantidad, const string& unidad)
        : nombre(nombre), cantidad(cantidad), unidad(unidad) {}

    MateriaPrima(const string& nombre) : nombre(nombre), cantidad(0),unidad("kg"){}

    void agregarStock(double cantidadExtra)
    {
        cantidad += cantidadExtra;
    }

    void reducirStock(double cantidadUsada)
    {
        if (cantidadUsada <= cantidad)
        {
            cantidad -= cantidadUsada;
        }
        else
        {
            cout << "No hay suficiente stock de " << nombre << "\n";
        }
    }

    void mostrarInfo() const
    {
        cout << "Materia Prima: " << nombre << " - " << cantidad << " " << unidad << "\n";
    }
};
