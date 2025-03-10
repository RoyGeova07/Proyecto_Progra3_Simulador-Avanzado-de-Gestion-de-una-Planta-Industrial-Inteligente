#ifndef EXTRACTOR_H
#define EXTRACTOR_H

#include "Maquina.h"
<<<<<<< Updated upstream

class Extractor : public Maquina
{
public:

    Extractor() : Maquina("Extractor de Jugo") {}
=======
#include <mutex>
#include <thread>
#include <vector>
#include <string>
#include "Frutas.h"
#include "Producto.h"
#include "Empleado.h"


class Extractor : public Maquina
{
private:
    std::mutex mtx;  

    
    void MostrarCronometro(int segundos, const std::string &frutaNombre);
    bool VerificarFallo();
    void ExtraerFruta(const std::string &frutaNombre);

public:
    Extractor();
    ~Extractor() override;

    /*
>>>>>>> Stashed changes
    
    Recibe referencias a:

        inventarioFrutas (para consumirlas),
        empleados (para buscar técnicos),
        productos (para añadir el jugo creado).

     */

    void MenuExtractor(std::vector<Frutas> &inventarioFrutas, std::vector<Empleado*> &empleados, std::vector<Producto> &productos);
};

#endif // EXTRACTOR_H
