#ifndef PASTEURIZADOR_h
#define PASTEURIZADOR_h
#include "Maquina.h"
#include "Producto.h"
#include <vector>
#include "Frutas.h"

using namespace std;



// consiste en el tratamiento del calor de un producto para matar todas las bacterias patogenas y reducir la actividad enzimatica
class Pasteurizador : public Maquina
{

private:

    std::vector<Maquina*>maquinas;
    std::vector<Producto>productos;
    std::vector<Frutas> frutas;
    void pasteurizar();
    std::vector<std::string>logProgreso;


public:
    
    Pasteurizador() : Maquina("Pasteurizador") {}

    //aqui aplicando polimorfismos
    void VerEstadoMaquina() const override{

        cout<<"Maquina Pasterizador: "<<(getEstado()?"En buena estado":"En mal estado")<<endl;

    }
    ~Pasteurizador() override;
    
};

#endif // PASTEURIZADOR_h