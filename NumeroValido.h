#ifndef NUMEROVALIDO_H
#define NUMEROVALIDO_H

#include <iostream>
#include <sstream>
#include <string>

using namespace std;

//que colera, tengo que crear un pt archivo aparte para llamar esta funcion clera para que el 
// pto linker no se que queje JAJAJAJ
//EN JAVA NO PASABA EST0OOOO

//Las funciones inline pueden aparecer en varios archivos sin causar errores de linking
inline int NumeroValido(string mensaje, int minimo, int maximo) {

    int valor;
    string entrada;
    char extra;
    while (true) {

        cout << mensaje;
        getline(cin, entrada);
        istringstream iss(entrada);

        //aqui se extraer el entero
        if (!(iss>>valor)) {

            cout << "Error: Entrada no valida. Intente de nuevo.\n";
            continue;

        }
        //aqui verificamos que no haya caracteres adicionales (por ejemplo, el ".4" de "3.4")

        if (iss>>extra) {

            cout<<"Error: Entrada no valida. Intente de nuevo.\n";
            continue;

        }
        if (valor<minimo||valor>maximo) {

            cout<<"Error: Entrada fuera de rango. Intente de nuevo.\n";
            continue;

        }
        return valor;

    }
}












#endif // NUMEROVALIDO_H