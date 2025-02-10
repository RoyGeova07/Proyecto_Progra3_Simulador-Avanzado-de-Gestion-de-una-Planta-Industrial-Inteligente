#ifndef PASTEURIZADOR_h
#define PASTEURIZADOR_h
#include <Maquina.h>

// consiste en el tratamiento del calor de un producto para matar todas las bacterias patógenas y reducir la actividad enzimática
class Pasteurizador : public Maquina
{
public:

    Pasteurizador() : Maquina("Pasteurizador") {}
    
};

#endif // PASTEURIZADOR_h