#ifndef EXTRACTOR_H
#define EXTRACTOR_H
#include "Maquina.h"
#include <vector>
#include "Producto.h"

using namespace std;


class Extractor : public Maquina
{

private: 

    std::vector<Maquina*> maquinas;
    std::vector<std::string> logProgreso;
    void extraerJugo();
    std::vector<Frutas> FRUTAS;
    std::vector<Producto> productos;



public:
    Extractor() : Maquina("Extractor de Jugo") {}

    //aqui aplicando polimorfismo
    void VerEstadoMaquina() const override{

        cout<<"Maquina Extractor: "<<(getEstado()?"En buena estado":"En mal estado")<<endl;

    }

    ~Extractor() override;  
    
};

#endif //EXTRACTOR_H