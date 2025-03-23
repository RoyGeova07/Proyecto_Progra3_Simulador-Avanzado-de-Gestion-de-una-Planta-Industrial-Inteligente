#ifndef ENVASADORA_H
#define ENVASADORA_H
#include "Maquina.h"
#include "Producto.h"
#include <vector>
#include "Frutas.h"
#include <mutex>

using namespace std;



// consiste en el tratamiento del calor de un producto para matar todas las bacterias patogenas y reducir la actividad enzimatica
class Envasadora:public Maquina
{

private:

  

    std::vector<Maquina*>maquinas;
    std::vector<Producto>productos;
    std::vector<Frutas> frutas;
    void pasteurizar();
    std::vector<std::string>logProgreso;
    mutable mutex mtx;

    void MostrarCronometro(int segundos,const std::string& JugoNombre)const;

    void AgregarIngredientes(const std::string& JugoNombre,Gestor_De_Planta& gestor,int cantidad)const;

    void EnvasarJugos(const std::string& JugoNombre,Gestor_De_Planta& gestor,int cantidad)const;

    bool VerificarFallo();



public:
    
    Envasadora():Maquina("Pasteurizador") {}

    void MenuMaquinaEnvasadora(std::vector<Producto>& InventarioJugos,std::vector<Empleado*>& Empleados,Gestor_De_Planta& gestor);

    
    ~Envasadora() override;
    
};

#endif // ENVASADORA_H