#include "Tienda.h"
#include <iostream>
#include <iomanip>  // Para formatear tablas
#include "NumeroValido.h"
#include "Frutas.h"
#include "Producto.h"
#include "Gestor_De_Planta.h"

using namespace std;

void Tienda::MenuTienda(Gestor_De_Planta& gestor) {
    int opcion = 0;

    while (opcion != 5) {
        cout << "\n==============================\n";
        cout << "           TIENDA DE INSUMOS        \n";
        cout << "==============================\n";
        cout << " Capital disponible: $" << gestor.getCapital() << "\n";
        cout << "1.  Comprar Frutas\n";
        cout << "2.  Comprar Conservantes\n";
        cout << "3.  Comprar Envases\n";
        cout << "4.  Comprar Agua\n";
        cout << "5.  Regresar\n";
        cout << "==============================\n";

        opcion = NumeroValido("Seleccione una opcion: ", 1, 5);

        switch (opcion) {
            case 1: ComprarFrutas(gestor); break;
            case 2: ComprarConservantes(gestor); break;
            case 3: ComprarEnvases(gestor); break;
            case 4: ComprarAgua(gestor); break;
            case 5: cout << "Saliendo de la Tienda...\n"; return;
            default: cout << "Opcion invalida.\n"; break;
        }
    }
}

void Tienda::ComprarFrutas(Gestor_De_Planta &gestor) {
    cout << "\n --- COMPRAR FRUTAS ---\n";
    cout << left << setw(4) << "ID" << setw(15) << "FRUTA" << right << setw(3) << "PRECIO\n";
    cout << "---------------------------------\n";
    cout << "1. " << setw(15) << left << "Limon" << setw(5) << right << "$2.4\n";
    cout << "2. " << setw(15) << left << "Naranja" << setw(5) << right << "$3.4\n";
    cout << "3. " << setw(15) << left << "Pina" << setw(5) << right << "$5.6\n";
    cout << "4. " << setw(15) << left << "Sandia" << setw(5) << right << "$7.8\n";
    cout << "5. " << setw(15) << left << "Fresa" << setw(5) << right << "$2.0\n";
    cout << "6. " << setw(15) << left << "Tamarindo" << setw(5) << right << "$4.0\n";
    cout << "7. " << setw(15) << left << "Coco" << setw(5) << right << "$2.1\n";
    cout << "---------------------------------\n";

    int tipoF = NumeroValido("Opcion: ", 1, 7);
    int cantidad = NumeroValido("Cantidad a comprar: ", 1, 1000);

    double precioUnit;
    switch (tipoF) {
        case 1: precioUnit = 2.4; break;
        case 2: precioUnit = 3.4; break;
        case 3: precioUnit = 5.6; break;
        case 4: precioUnit = 7.8; break;
        case 5: precioUnit = 2.0; break;
        case 6: precioUnit = 4.0; break;
        case 7: precioUnit = 2.1; break;
    }

    double costoTotal = cantidad * precioUnit;
    if (costoTotal > gestor.getCapital()) {
        cout << "No tienes suficiente capital para esta compra.\n";
        return;
    }

    gestor.AgregarFruta(Frutas((Frutas::Fruta)tipoF, precioUnit, cantidad));
    gestor.agregarCapital(-costoTotal);  // Restar capital

    cout << "Compra exitosa. Nuevo capital: $" << gestor.getCapital() << "\n";
}

void Tienda::ComprarConservantes(Gestor_De_Planta &gestor) {
    cout << "\n --- COMPRAR CONSERVANTES ---\n";
    cout << "Cada conservante cuesta **$3**\n";
    
    int cantidad = NumeroValido("Cantidad de conservantes a comprar: ", 1, 1000);
    double precioUnit = 3.0;  // Precio corregido a $3

    double costo = cantidad * precioUnit;
    if (costo > gestor.getCapital()) {
        cout << "No tienes suficiente capital para esta compra.\n";
        return;
    }

    gestor.AgregarMasConservantes(cantidad);
    gestor.agregarCapital(-costo);

    cout << "Conservantes comprados exitosamente. Capital restante: $" << gestor.getCapital() << "\n";
}

void Tienda::ComprarEnvases(Gestor_De_Planta &gestor) {
    cout << "\n --- COMPRAR ENVASES ---\n";
    cout << "Cada envase cuesta **$7**\n";

    int cantidad = NumeroValido("Cantidad de envases a comprar: ", 1, 1000);
    double precioUnit = 7.0;  // Precio corregido a $7

    double costo = cantidad * precioUnit;
    if (costo > gestor.getCapital()) {
        cout << "No tienes suficiente capital para esta compra.\n";
        return;
    }

    gestor.AgregarMasEnvases(cantidad);
    gestor.agregarCapital(-costo);

    cout << "Envases comprados exitosamente. Capital restante: $" << gestor.getCapital() << "\n";
}

void Tienda::ComprarAgua(Gestor_De_Planta &gestor) {
    cout << "\n --- COMPRAR AGUA ---\n";
    cout << "Cada litro de agua cuesta **$5**\n";

    int cantidad = NumeroValido("Litros de agua a comprar: ", 1, 10000);
    double precioUnit = 5.0;  // Precio corregido a $5

    double costo = cantidad * precioUnit;

    if (costo > gestor.getCapital()) {
        cout << "No hay suficiente capital.\n";
        return;
    }

    gestor.setAgua(gestor.getAgua() + cantidad);
    gestor.agregarCapital(-costo);

    cout << "Agua comprada correctamente. Capital restante: $" << gestor.getCapital() << "\n";
}
