#ifndef LINEAPRODUCCION_H
#define LINEAPRODUCCION_H

#include <Maquina.h>


class LineaDeProduccion {
    private:
        vector<Maquina*> maquinas;
        bool operando;
    
    public:
        LineaDeProduccion() : operando(false) {}
    
        void agregarMaquina(Maquina* maquina) {
            maquinas.push_back(maquina);
        }
    
        void iniciarProduccion() {
            if (maquinas.empty()) {
                cout << "No hay máquinas en la línea de producción.\n";
                return;
            }
            operando = true;
            cout << "Producción iniciada.\n";
        }
    
        void detenerProduccion() {
            operando = false;
            cout << "Producción detenida.\n";
        }
    };






#endif LINEAPRODUCCION_H
