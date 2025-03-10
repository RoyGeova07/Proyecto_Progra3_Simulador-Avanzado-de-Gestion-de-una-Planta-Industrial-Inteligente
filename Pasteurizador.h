#ifndef PASTEURIZADOR_H
#define PASTEURIZADOR_H

#include "Maquina.h"
<<<<<<< Updated upstream

// consiste en el tratamiento del calor de un producto para matar todas las bacterias patógenas y reducir la actividad enzimatica
class Pasteurizador : public Maquina
{
public:

    Pasteurizador() : Maquina("Pasteurizador") {}
=======
#include <mutex>
#include <thread>
#include <vector>
#include <string>
#include "Producto.h"
#include "Frutas.h"
#include "Empleado.h"


class Pasteurizador : public Maquina
{
private:
    std::mutex mtx;  

    void MostrarCronometro(int segundos, const std::string &productoNombre);
    bool VerificarFallo();
    void PasteurizarProducto(const std::string &productoNombre);

public:
    Pasteurizador();
    ~Pasteurizador() override;

    // Recibe referencia a 'productos' (para pasteurizarlos) y 'empleados' (para técnicos)
>>>>>>> Stashed changes
    
    void MenuPasteurizador(std::vector<Producto> &productos,
                           std::vector<Empleado*> &empleados);
};

#endif // PASTEURIZADOR_H
