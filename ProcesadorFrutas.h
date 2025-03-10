#ifndef ProcesadorFrutas_H
#define ProcesadorFrutas_H
#include "Maquina.h"
#include <vector>
#include "Producto.h"
#include <mutex>

using namespace std;


class ProcesadorFrutas : public Maquina
{

private: 

    

    std::vector<Maquina*> maquinas;
    std::vector<std::string> logProgreso;
    void extraerJugo();
    std::vector<Frutas> FRUTAS;
    std::vector<Producto> productos;
    mutable mutex mtx;

    void MostrarCronometro(int segundos,const std::string& frutanombre)const;

    void TriturarFruta(int segundos, const std::string &FrutaNombre)const;

    void ExtraerJugo(int segundos, const std::string &FrutaNombre)const;


    bool VerificarFallo();



public:
    ProcesadorFrutas() : Maquina("ProcesadorFrutas de Jugo") {}

    //aqui aplicando polimorfismo
    void VerEstadoMaquina() const override{

        cout<<"Maquina ProcesadorFrutas: "<<(getEstado()?"En buena estado":"En mal estado")<<endl;

    }

    void MenuProcesadorFrutas(std::vector<Frutas>& inventarioFrutas,std::vector<Empleado*>& empleados,Gestor_De_Planta& gestor);

    ~ProcesadorFrutas() override;  
    
};

#endif //ProcesadorFrutas_H