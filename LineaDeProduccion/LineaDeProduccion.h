#ifndef LINEAPRODUCCION_H
#define LINEAPRODUCCION_H

#include <vector>

#include <Maquina.h>

class LineaDeProduccion
{
private:
    std::vector<Maquina *> maquinas;
    bool operando;

public:
    LineaDeProduccion() : operando(false) {}

    void agregarMaquina(Maquina *maquina)
    {
        maquinas.push_back(maquina);
    }

    void iniciarProduccion()
    {
        if (maquinas.empty())
        {
            std::cout << "No hay maquinas en la linea de produccion.\n";
            return;
        }
        operando = true;
        std::cout << "Produccion iniciada.\n";
    }

    void detenerProduccion()
    {
        operando = false;
        std::cout << "Produccion detenida.\n";
    }
};

#endif //LINEAPRODUCCION_H
