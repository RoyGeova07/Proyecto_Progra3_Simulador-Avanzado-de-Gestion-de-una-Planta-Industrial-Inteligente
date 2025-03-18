#include "Tienda.h"
#include <iostream>
#include "NumeroValido.h"     
#include "Frutas.h"
#include "Producto.h"
using namespace std;


// Menú principal de la Tienda

void Tienda::MenuTienda(Gestor_De_Planta &gestor, double &capital)
{
    int opcion = 0;

    while (opcion != 5) {

        cout << "\n--- Tienda de Insumos ---\n";
        cout << "Capital disponible: $" << capital << "\n";
        cout << "1. Comprar Frutas\n";
        cout << "2. Comprar Conservantes\n";
        cout << "3. Comprar Envases\n";
        cout << "4. Comprar Agua\n";
        cout << "5. Regresar\n";

        opcion = NumeroValido("Seleccione una opcion: ", 1, 5);

        switch(opcion) {
            case 1:
                ComprarFrutas(gestor, capital);
                break;

            case 2:
                ComprarConservantes(gestor, capital);
                break;

            case 3:
                ComprarEnvases(gestor, capital);
                break;

            case 4:
                ComprarAgua(gestor, capital);
                break;

            case 5:
                cout << "Saliendo de la Tienda...\n";
                break;

            default:
                cout << "Opcion invalida.\n";
                break;


        }
    }

}


// Comprar Frutas

void Tienda::ComprarFrutas(Gestor_De_Planta &gestor, double &capital)
{
    cout << "\n--- Comprar Frutas ---\n";
    cout << "Seleccione el tipo de fruta:\n";
    cout << "1. Limon\n2. Naranja\n3. Piña\n4. Sandia\n5. Fresa\n6. Tamarindo\n7. Coco\n";

    int tipoF = NumeroValido("Opcion: ", 1, 7);

    int cant   = NumeroValido("Cantidad a comprar: ", 1, 1000);
    double precioUnit = NumeroValido("Precio por unidad: ", 1, 500);

    double costoTotal = cant * precioUnit;
    if (costoTotal > capital) {

        cout << "No tienes suficiente capital para esta compra.\n";
        return;
    }

    // Descontar el capital
    capital -= costoTotal;

    gestor.AgregarFruta(Frutas((Frutas::Fruta)tipoF, precioUnit, cant));

    cout << "Compra exitosa. Nuevo capital: $" << capital << "\n";
}


void Tienda::ComprarConservantes(Gestor_De_Planta &gestor, double &capital)
{
    cout << "\n--- Comprar Conservantes ---\n";
    int cantidad = NumeroValido("Cantidad de conservantes a comprar: ", 1, 1000);
    double precioUnit = NumeroValido("Precio por unidad: ", 1, 500);

    double costo = cantidad * precioUnit;
    if (costo > capital) {
        cout << "No tienes suficiente capital para esta compra.\n";
        return;
    }

    capital -= costo;
    // Creamos un producto "Conservante"
    Producto conserv("Conservante", cantidad, precioUnit);
    gestor.agregarProducto(conserv);

    cout << "Conservantes comprados exitosamente. Capital restante: $" << capital << "\n";
}

// Comprar Envases

void Tienda::ComprarEnvases(Gestor_De_Planta &gestor, double &capital)
{
    cout << "\n--- Comprar Envases ---\n";
    int cantidad = NumeroValido("Cantidad de envases a comprar: ", 1, 1000);
    double precioUnit = NumeroValido("Precio por unidad: ", 1, 500);

    double costo = cantidad * precioUnit;
    if (costo > capital) {
        cout << "No tienes suficiente capital para esta compra.\n";
        return;
    }

    capital -= costo;

    Producto env("Envases", cantidad, precioUnit);
    gestor.agregarProducto(env);

    cout << "Envases comprados. Capital restante: $" << capital << "\n";
}


void Tienda::ComprarAgua(Gestor_De_Planta &gestor, double &capital)
{
    cout << "\n--- Comprar Agua ---\n";
    int cantidad = NumeroValido("Litros de agua a comprar: ", 1, 10000);
    double precioUnit = NumeroValido("Precio por litro: ", 1, 100);

    double costo = cantidad * precioUnit;
    if (costo > capital) {
        cout << "No hay suficiente capital.\n";
        return;
    }

    capital -= costo;

    gestor.AgregarFruta(Frutas(Frutas::Agua, precioUnit, cantidad));

    cout << "Agua comprada correctamente. Capital restante: $" << capital << "\n";
}
