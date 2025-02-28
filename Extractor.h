#ifndef EXTRACTOR_H
#define EXTRACTOR_H
#include "Maquina.h"
#include <vector>
#include "Producto.h"

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
    ~Extractor() override;  
    
};

#endif //EXTRACTOR_H