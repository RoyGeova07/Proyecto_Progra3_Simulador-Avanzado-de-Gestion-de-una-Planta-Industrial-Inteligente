// Simulador.h
//#ifndef SIMULADOR_H
//#define SIMULADOR_H

#include "PlantaIndustrial.h"

#include <thread>
#include <mutex>




class Simulador {
    private:
    
    PlantaIndustrial planta;
    
    bool enEjecucion;               
    bool enPausa;                   
    std::thread hiloSimulacion;     
    std::mutex mtx;                 
    double tiempoSimulacion;        // Tiempo simulado (por ejemplo en “días” o “horas”)
    double escalaTiempo;            // Relación tiempo real-tiempo simulado (ej. 1 seg real = 1 día simulado)

    void loopSimulacion();

    public:
    
    /*
    void iniciarSimulacion();
    void pausarSimulacion();
    void reaunudarSimulacion();
    void detenerSimulacion();
    */

};

/*

iniciar simulacion ---> 
    enEjecucion = true;
    enPausa = false;
    hiloSimulacion = std::thread(&Simulador::loopSimulacion, this);


pausar ---> enPausa = true;
reaunudar ---> enPausa = false;


detener simulacion ---> enEjecucion = false;

loop Simualacion ---> std::this_thread::sleep_for(std::chrono::milliseconds(100));


*/