#include <iostream>
#include "Gestor_De_Planta.h"
#include "Producto.h"
#include <vector>
#include <algorithm>
#include "Empleado.h"
#include "EmpleadoOperario.h"
#include "EmpleadoTecnico.h"
#include "NumeroValido.h"
#include "Maquina.h"
#include "Distribucion.h"
#include "Tienda.h"//siempre incluir el header en el cpp para evitar errores de dependencia circular
#include <iosfwd>
#include <filesystem>

using namespace std;

namespace fs=std::filesystem;


//aqui se usa un destructor para liberar la memmoria de los vectores de puntero
Gestor_De_Planta::Gestor_De_Planta(){

    distribucion=new Distribucion();
    distribucion->setGestor(this);

    tiendita=new Tienda();

}

//destructor para liberar memoria
Gestor_De_Planta::~Gestor_De_Planta() {
    delete distribucion;
    delete tiendita;
    for (auto emp : empleado) delete emp;
    empleado.clear();
}

void Gestor_De_Planta::ReducirAgua(double litros){

    if (AguaLitros>=litros)
    {
        
        AguaLitros-=litros;

    }else{

        AguaLitros=0;//aqui evita que el agua sea negativa
        
    }
    

}

void Gestor_De_Planta::AgregarEmpleado(Empleado* emp) {

    empleado.push_back(emp);

}


void Gestor_De_Planta::listarEmpleados()const {

    if (empleado.empty())
    {
        
        cout<<"NO HAY EMPLEADOS EN LA PLANTA\n";
        return;

    }


    cout<<"\n--- Lista de Empleados ---\n" ;   
    for(const auto &emp : empleado)
    {

        emp->MostrarInfo();

    }

}

void Gestor_De_Planta::listarProductos() const{

    if (productos.empty()) {
        cout << "No hay productos en el inventario." << endl;
        return;
    }

    cout << "\n--- Lista de Productos ---\n";
    for (const auto &producto : productos) {
       
        producto.mostrarInfo();

    }

}

void Gestor_De_Planta::ListarFrutas()const {

    if (FRUTAS.empty()) {
        cout << "No hay frutas en el inventario." << endl;
        return;
    }

    cout << "\n--- Lista de Frutas ---\n";
    for (const auto &fruta : FRUTAS) {
        cout << "Nombre: " << fruta.getNombre()
             << " | Cantidad: " << fruta.getCantidad()
             << " | Precio: $" << fruta.getCosto() << endl;
    }

}

void Gestor_De_Planta::VerEstadoMaquina() const {
    if (maquinas.empty()) {
        cout << "No hay maquinas en la planta." << endl;
        return;
    }

    cout << "\n--- Estado de las Maquinas ---\n";
    for (const auto &maquina : maquinas) {

        maquina->VerEstadoMaquina();//aqui se llama la funcion polimorfica.

    }
}

void Gestor_De_Planta::TransferirFrutaLavada(const Frutas& frutaLavada){

    for(auto& fruta:FRUTAS_LAVADAS){

        if (fruta.getNombre()==frutaLavada.getNombre())
        {
            
            fruta.setCantidad(fruta.getCantidad()+frutaLavada.getCantidad());

            //aqui si el costo cambio, puedes decidir si actualizarlo o mantener el anterior:
            fruta.setCosto(frutaLavada.getCosto());  // Opcional


            return;

        }
        
    }
    //aqui si la fruta no esta en la lista de lavadas, se agrega
    FRUTAS_LAVADAS.push_back(frutaLavada);

}

void Gestor_De_Planta::ListarFrutasLavadas()const{

    if (FRUTAS_LAVADAS.empty())
    {

        cout<<"No hay frutas lavadaaaas\n";
        return;
        
    }
    

    cout<<"\n--- Lista de Frutas Lavadas ---\n";
    for(const auto& fruta : FRUTAS_LAVADAS){
        cout << "Nombre: " << fruta.getNombre()
             << " | Cantidad Lavada: " << fruta.getCantidad()
             << " | Precio: $" << fruta.getCosto() << endl;
    }

}

//aqui funcion para eliminar un empleado por el id
//el find_id me ayuda a recorrer el vector empleado, buscando el primer elemento que cumpla con una condiciion
//begin apunta al primer elemento del vector y end al final

// el [id](Empleado* emp) es una funcion lambda que recibe un puntero a empleado y compara el id
// de ese empleado con el id que se esta buscando

//Que devuelve?
//find_if devuelve un iterador que apunta al primer Empleado* que tiene ese id.
//Si no lo encuentra, devuelve empleado.end(), lo que significa "no encontrado".

//Validacion (empleado encontrado o no)
//if (es != empleado.end()) {
//Si es no es end(), significa que find_if encontro un empleado con el ID buscado.
//Si es == end(), significa que el empleado no existe.

//"*es" es el puntero del empleado no encontrado
//(*es)->getNombre() accede al nombre del empleado

//Eliminar el puntero del vector
//Una vez eliminado el empleado, se debe quitar el puntero del vector para que el vector este limpio.
//empleado.erase(es);
//erase elimina el elemento en la posicion del iterador "*es".
//Es como ArrayList.remove(index) en Java, pero aqui se trabaja con punteros e iteradores.


void Gestor_De_Planta::eliminarEmpleado(int id) {

   auto es=find_if(empleado.begin(),empleado.end(),[id](Empleado* emp){

     return emp->getId()==id;

   });

   if(es!=empleado.end()){

        cout<<"\n**Empleado "<<(*es)->getNombre()<<" ha sido despedido.**\n";
        EMPLEADOS_DESPEDIDOS.push_back((*es)->getNombre());//aqui se guarda el nombre del empleado despedido
        delete *es;
        empleado.erase(es);

    }else{

        cout<<"No se encontro ningun empleado con el ID "<<id<<".\n";

    }

}

Empleado* Gestor_De_Planta::BuscarEmpleadoPorId(int id){

    for(Empleado* emp:empleado){

        if(emp->getId()==id){

            return emp;

        }

    }
    return nullptr;

}


int Gestor_De_Planta::CantidadEmpleados() const{

    return empleado.size();

}



void Gestor_De_Planta::AgregarFruta(const Frutas& fruta) {

    for(auto& EstaDuplicadoEl:FRUTAS){

        if(EstaDuplicadoEl.getNombre()==fruta.getNombre())
        {
           
            //aqui si la fruta ya existe, sumamos la cantidad y actulizamos el precio al ultimo valorEquis
            EstaDuplicadoEl.setCantidad(EstaDuplicadoEl.getCantidad()+fruta.getCantidad());
            EstaDuplicadoEl.setCosto(fruta.getCosto());//aqui se actualiza el precio al nuevo ingresado
            return;
           
        } 

    }
    //aqui si no se encontro una fruta con el mismo nombre lo agrega
    FRUTAS.push_back(fruta);

}


void Gestor_De_Planta::AgregarMaquina(Maquina* maq){

    maquinas.push_back(maq);

}

void Gestor_De_Planta::AgregarJugosSinIngredientesYEnvases(const Producto& jugo){

    for(auto&JugoCreado:JUGOS_SIN_INGREDIENTES){

        if (JugoCreado.getNombre()==jugo.getNombre())
        {
            
            JugoCreado.setCantidadSinIngredientes(JugoCreado.getCantidadSinIngredientes()+jugo.getCantidadSinIngredientes());
            //JugoCreado.setNombre(jugo.getNombre());
            return;//aqui evita los duplicados  

        }
        

    }
    Producto NuevoJugo(jugo.getNombre(),jugo.getCantidadProducida(),jugo.getPrecio());
    NuevoJugo.setCantidadSinIngredientes(jugo.getCantidadProducida());//aqui se asegura que la cantidad sin ingredientes se refleje
    JUGOS_SIN_INGREDIENTES.push_back(NuevoJugo);//aqui si no existe lo agrega

}

// estos son los que  ya se pueden vender 
void Gestor_De_Planta::AgregarJugosDisponibles(const Producto& jugo,int cantidad){

    for(auto& JugoFinal:JUGOS_DISPONIBLES){

        if (JugoFinal.getNombre()==jugo.getNombre())
        {
            
            JugoFinal.setCantidadProducida(JugoFinal.getCantidadProducida()+cantidad);
            return;

        }
        
    }
    Producto NuevoJugo(jugo.getNombre(),cantidad,jugo.getPrecio());
    JUGOS_DISPONIBLES.push_back(NuevoJugo);

}

void Gestor_De_Planta::ListaJugosDisponibles()const{

    if(JUGOS_DISPONIBLES.empty())
    {
        
        cout<<"\nNo hay jugos disponibles para la venta.\n";
        return;

    }

    cout<<"\n -- Jugos Disponibles para la venta -- \n";
    for(const auto& jugo:JUGOS_DISPONIBLES){

        cout<<"Jugo: "<<jugo.getNombre()<<" - Cantidad Disponible: "<<jugo.getCantidad()<<" - Precio: $"<<jugo.getPrecio()<<"\n.";

    }
    
}

void Gestor_De_Planta::ListaJugosFaltanIngredientesYEnvases()const{

    if(JUGOS_SIN_INGREDIENTES.empty())
    {

       cout<<"No hay jugos sin ingredientes aun\n";
       return;
        
    }
    cout<<"\n -- Jugos sin Ingredientes -- \n";
    for(const auto& JugosSinSabor: JUGOS_SIN_INGREDIENTES){

        std::cout<<"Jugo: "<<JugosSinSabor.getNombre()<<" Cantidad: "<<JugosSinSabor.getCantidadProducida()<<" - Sin Ingredientes\n";

    }

}

//ESTA FUNCION POR SI ACASO LO NECESITE A FUTURO
//EXPLICARE LA FUNCIONALIDAD DE ESTA FUNCION DESPUESSSSSS
//EXPLICARE LA FUNCIONALIDAD DE ESTA FUNCION DESPUESSSSSS
//EXPLICARE LA FUNCIONALIDAD DE ESTA FUNCION DESPUESSSSSS
//EXPLICARE LA FUNCIONALIDAD DE ESTA FUNCION DESPUESSSSSS
//EXPLICARE LA FUNCIONALIDAD DE ESTA FUNCION DESPUESSSSSS
void Gestor_De_Planta::EliminarJugoSinIngredientes(const string& NombreJugo){

    auto messi=remove_if(JUGOS_SIN_INGREDIENTES.begin(),JUGOS_SIN_INGREDIENTES.end(),[&NombreJugo](const Producto& jugo){return jugo.getNombre()==NombreJugo;});

    if(messi!=JUGOS_SIN_INGREDIENTES.end()){

        JUGOS_SIN_INGREDIENTES.erase(messi,JUGOS_SIN_INGREDIENTES.end());

    }

}

char ObtenerCocaCola(string mensaje){

    string cocacola;
    char respuestagod;
    while(true){

        cout<<mensaje;
        getline(cin,cocacola);
        if(cocacola.empty())continue;
        respuestagod = tolower(cocacola[0]);  
        if(respuestagod=='s'||respuestagod=='n')return respuestagod;
        cout << "Entrada invalida. Ingrese 's' para si o 'n' para no.\n";   

    }

}

template <typename T>
T NumeroTypename(string mensaje, T minimoComumMultiplo, T MaximoComunMultiplo){

    T valorEquis;
    string hitler;
    char variableExtra;
    while (true){

        cout << mensaje;
        getline(cin, hitler);
        istringstream iss(hitler);

        //aqui se  extrae el valorEquis del tipo T
        if(!(iss>>valorEquis)){

            cout << "Error: Entrada no valida. Intente de nuevo.\n";
            continue;

        }
        // Verificamos si quedaron caracteres adicionales usando 'iss' y no 'cin'
        if(iss>>variableExtra){

            cout<<"Error: Entrada no valida. Intente de nuevo.\n";
            continue;

        }
        if(valorEquis<minimoComumMultiplo||valorEquis>MaximoComunMultiplo){

            cout << "Error: Entrada fuera de rango. Intente de nuevo.\n";
            continue;

        }
        return valorEquis;
    }
}


void Gestor_De_Planta::MiniMenuGestor(Gestor_De_Planta& gestor){

    int opcionmini=0;
  
    while (opcionmini!=5)
    {
        cout<<"\n====================Menu de la planta====================\n";
        cout<<"1. Listar Planta\n";
        cout<<"2. Despedir Empleados\n";
        cout<<"3. Espacio de Maquinas\n";
        cout<<"4. Comprar Frutas\n";
        cout<<"5. Ver pedidos\n";
        cout<<"6. Generar reporte de la planta de "<<gestor.getNombrePLanta()<<"\n";
        cout<<"7. Ver reporte de la planta de "<<gestor.getNombrePLanta()<<"\n";
        cout<<"8. Ingresar mas capital\n";
        cout<<"9. Guardar Simulacion\n";
        cout<<"10. Salir de mi planta\n";
        opcionmini=NumeroValido("Ingrese una opcion: ",1,10);
        
    
        if(opcionmini==1)
        {
            cout<<"===============================================================\n";
            //listar empleados contratados
            cout<<"\nEmpleados activos:\n ";
            listarEmpleados();

            cout<<"----------------------------------------------------------------\n";

            cout<<"\nNombre de la planta: "<<getNombrePLanta()<<"\n";

            cout<<"----------------------------------------------------------------\n";
            //aqui se listas las frutas
            cout<<"\nFrutas en inventario:\n";
            ListarFrutas();

            cout<<"----------------------------------------------------------------\n";

            cout<<"\nCapital: $"<<getCapital()<<"\n";

            cout<<"----------------------------------------------------------------\n";

            cout<<"\nFrutas lavadas en general:\n";
            ListarFrutasLavadas();

            cout<<"----------------------------------------------------------------\n";

            cout<<"\nJugos sin Ingredientes y envases por Agregar:\n";
            ListaJugosFaltanIngredientesYEnvases();

            cout<<"----------------------------------------------------------------\n";

            cout<<"\nJugos Disponibles:\n";
            ListaJugosDisponibles();

            cout<<"----------------------------------------------------------------\n";

            cout<<"\nAgua disponible: "<<getAgua()<<" litros\n";

            cout<<"----------------------------------------------------------------\n";

            cout<<"\nConservantes disponibles: "<<getConservantes()<<" unidades\n";

            cout<<"----------------------------------------------------------------\n";

            cout<<"\n Envases disponibles: "<<getEnvases()<<" unidades\n";

            cout<<"----------------------------------------------------------------\n";
            
            cout<<"\nEstado de las maquinas actualmente:\n";
            VerEstadoMaquina();

            cout<<"====================================================================\n";
    
        }else if (opcionmini==2){
            int id;
    
            cout<<"======================================================================\n";
            cout<<"***seleccione 51 para salir****\n";
           //listar empleados contratados
           cout<<"\nEmpleados activos:\n ";
            listarEmpleados();
           cout<<"---Nota-- Presione 51 para volver al menu\n";
           id=NumeroValido("Ingrese el ID del empleado a despedir: ",1,51);

           if(id==51){

            return;

           }
           
           eliminarEmpleado(id);

           listarEmpleados();

            
        }else if(opcionmini==3){
        
            Maquina::MenuMaquinas(*this);
            
        }else if(opcionmini==4){
    
            /*
            
            ejemplo de una instancia nueva
            Tienda tienda;  esto borra todos los datos anteriores
            tienda.MenuTienda(*this);
            
            */
           getTienda().MenuTienda(*this);//una sola instancia, para no perder los datos
            
            
    
        }else if(opcionmini==5){
    
            if(!distribucion){

                distribucion=new Distribucion();
                distribucion->setGestor(this);


            }
            distribucion->mostrarMenuPedidos(*this);

        }else if(opcionmini==6){
    
            EmpleadoOperario dummy(""); // No se usa directamente, pero sirve para invocar el metodo estatico
            dummy.GenerarReportePlantaConHilos(*this, this->getEmpleados());        
    
        }else if(opcionmini==7){

            string carpeta="Reportes de Plantas Industriales";
            string archivo=carpeta+"/"+gestor.getNombrePLanta()+".txt";
            ifstream reporte(archivo);

            if(!reporte.is_open())
            {
                
                cout<<"\n No se encontrado un reporte de esta planta.\n";

            }else{

                cout<<"\n==========  CONTENIDO DEL REPORTE ==========\n";
                string linea;
                while(getline(reporte,linea))
                {

                    cout<<linea<<"\n";
                    
                }
                cout << "\n==========  FIN DEL REPORTE ==========\n";
                reporte.close();
                
            }
            
            


        }else if(opcionmini==8){

            char respuestagod;
            double CapitalAdicional;
            respuestagod=ObtenerCocaCola("\nDesea agregar mas dinero? (s/n): ");
            if(respuestagod=='s'||respuestagod=='S')
            {
        
                CapitalAdicional=NumeroTypename("Ingrese la cantidad a adicionar: ",1.0,50000.0);
                
            }
            gestor.agregarCapital(CapitalAdicional);

        }else if(opcionmini==9){

            string nombre;
            cout<<"\nIngrese el nombre del archivo para guardar (ej:  miplanta.bin): ";
            getline(cin,nombre);
            if(nombre.empty())nombre="SimulacionPlanta.bin";

            string ruta="Planta Industriales guardadas/"+nombre;
            if(fs::exists(ruta)){

                char respuesta;
                ObtenerCocaCola("\nEl archivo ya existe. Deseas sobreescribirlo? (s/n): ");
                if (respuesta!='s'||respuesta=='S');
                {
                    
                    cout<<"Operacion cancelada. No se guardo la simulacion\n";
                    return;

                }
                
            }

            GuardarSimulacionBinario(nombre);

        }else if (opcionmini==10){

            cout<<" --- Saliendo de mi planta --- \n";
            //VOLVER AL MENU INICIO DEL MAIN
            MenuPrincipal();

        }else{

            cout<<"opcion no valida\n";

        }

    }
        

}

void Gestor_De_Planta::GuardarSimulacionBinario(const std::string &nombreArchivo)
{
    // 1) Crear/verificar la carpeta
    std::string carpeta = "Plantas Industriales guardadas";
    if(!fs::exists(carpeta)) {
        fs::create_directory(carpeta);
    }

    // 2) Construir la ruta completa (carpeta + archivo)
    std::string ruta = carpeta + "/" + nombreArchivo;

    // 3) Abrir archivo binario
    std::ofstream archivo(ruta, std::ios::binary);
    if(!archivo.is_open()) {
        std::cerr << "Error al abrir el archivo binario para guardar la simulacion.\n";
        return;
    }

    // a) Guardar nombre de la planta
    {
        size_t len = NombreDelaPlanta.size();
        archivo.write(reinterpret_cast<const char*>(&len), sizeof(len));
        archivo.write(NombreDelaPlanta.c_str(), len);
    }

    // b) Guardar capital, agua, conservantes, envases
    archivo.write(reinterpret_cast<const char*>(&CapitalInicial), sizeof(CapitalInicial));
    archivo.write(reinterpret_cast<const char*>(&AguaLitros),     sizeof(AguaLitros));
    archivo.write(reinterpret_cast<const char*>(&Conservantes),   sizeof(Conservantes));
    archivo.write(reinterpret_cast<const char*>(&Envases),        sizeof(Envases));

    // c) Guardar FRUTAS
    {
        size_t totalFrutas = FRUTAS.size();
        archivo.write(reinterpret_cast<const char*>(&totalFrutas), sizeof(totalFrutas));
        for(const auto &f : FRUTAS)
        {
            // Necesitamos mapear getNombre() a un int enum
            int tipoInt = -1;
            // Ejemplo de mapeo básico:
            if(f.getNombre() == "Agua")       tipoInt = 0;
            else if(f.getNombre() == "Limon") tipoInt = 1;
            else if(f.getNombre() == "Naranja") tipoInt = 2;
            else if(f.getNombre() == "Piña")  tipoInt = 3;
            else if(f.getNombre() == "Sandia") tipoInt = 4;
            else if(f.getNombre() == "Fresa")  tipoInt = 5;
            else if(f.getNombre() == "Tamarindo") tipoInt = 6;
            else if(f.getNombre() == "Coco")  tipoInt = 7;

            archivo.write(reinterpret_cast<const char*>(&tipoInt), sizeof(tipoInt));
            double costo = f.getCosto();
            archivo.write(reinterpret_cast<const char*>(&costo), sizeof(costo));
            int cantidad = f.getCantidad();
            archivo.write(reinterpret_cast<const char*>(&cantidad), sizeof(cantidad));
            int cLavada = f.getCantidadLavada();
            archivo.write(reinterpret_cast<const char*>(&cLavada), sizeof(cLavada));
        }
    }

    // d) Guardar Empleados
    {
        size_t totalEmp = empleado.size();
        archivo.write(reinterpret_cast<const char*>(&totalEmp), sizeof(totalEmp));
        for(auto *emp : empleado)
        {
            if(dynamic_cast<EmpleadoOperario*>(emp)) {
                int tipoEmp = 0; // operario
                archivo.write(reinterpret_cast<const char*>(&tipoEmp), sizeof(tipoEmp));
            }
            else if(dynamic_cast<EmpleadoTecnico*>(emp)) {
                int tipoEmp = 1; // tecnico
                archivo.write(reinterpret_cast<const char*>(&tipoEmp), sizeof(tipoEmp));
            }
            else {
                int tipoEmp = 9; // desconocido
                archivo.write(reinterpret_cast<const char*>(&tipoEmp), sizeof(tipoEmp));
            }

            // Guardar nombre
            std::string nom = emp->getNombre();
            size_t lenNom = nom.size();
            archivo.write(reinterpret_cast<const char*>(&lenNom), sizeof(lenNom));
            archivo.write(nom.c_str(), lenNom);

            // Guardar cargo
            std::string cargo = emp->getCargo();
            size_t lenCargo = cargo.size();
            archivo.write(reinterpret_cast<const char*>(&lenCargo), sizeof(lenCargo));
            archivo.write(cargo.c_str(), lenCargo);

            // Guardar id, salario, dineroGanado
            int id = emp->getId();
            archivo.write(reinterpret_cast<const char*>(&id), sizeof(id));

            int salario = emp->getSalario();
            archivo.write(reinterpret_cast<const char*>(&salario), sizeof(salario));

            int dineroGanado = emp->getDineroGanado();
            archivo.write(reinterpret_cast<const char*>(&dineroGanado), sizeof(dineroGanado));
        }
    }

    // e) Guardar FRUTAS_LAVADAS
    {
        size_t totalLavadas = FRUTAS_LAVADAS.size();
        archivo.write(reinterpret_cast<const char*>(&totalLavadas), sizeof(totalLavadas));
        for(const auto& fruta : FRUTAS_LAVADAS) {
            int tipoInt = -1;
            if(fruta.getNombre() == "Limon") tipoInt = 1;
            else if(fruta.getNombre() == "Naranja") tipoInt = 2;
            else if(fruta.getNombre() == "Piña") tipoInt = 3;
            else if(fruta.getNombre() == "Sandia") tipoInt = 4;
            else if(fruta.getNombre() == "Fresa") tipoInt = 5;
            else if(fruta.getNombre() == "Tamarindo") tipoInt = 6;
            else if(fruta.getNombre() == "Coco") tipoInt = 7;

            archivo.write(reinterpret_cast<const char*>(&tipoInt), sizeof(tipoInt));
            double costo = fruta.getCosto();
            archivo.write(reinterpret_cast<const char*>(&costo), sizeof(costo));
            int cantidad = fruta.getCantidad();
            archivo.write(reinterpret_cast<const char*>(&cantidad), sizeof(cantidad));
        }
    }

    // f) Guardar JUGOS_SIN_INGREDIENTES
    {
        size_t totalJugosSin = JUGOS_SIN_INGREDIENTES.size();
        archivo.write(reinterpret_cast<const char*>(&totalJugosSin), sizeof(totalJugosSin));
        for(const auto& jugo : JUGOS_SIN_INGREDIENTES) {
            size_t len = jugo.getNombre().size();
            archivo.write(reinterpret_cast<const char*>(&len), sizeof(len));
            archivo.write(jugo.getNombre().c_str(), len);

            int cantidad = jugo.getCantidadSinIngredientes();
            double precio = jugo.getPrecio();
            archivo.write(reinterpret_cast<const char*>(&cantidad), sizeof(cantidad));
            archivo.write(reinterpret_cast<const char*>(&precio), sizeof(precio));
        }
    }

    // g) Guardar JUGOS_DISPONIBLES
    {
        size_t totalJugos = JUGOS_DISPONIBLES.size();
        archivo.write(reinterpret_cast<const char*>(&totalJugos), sizeof(totalJugos));
        for(const auto& jugo : JUGOS_DISPONIBLES) {
            size_t len = jugo.getNombre().size();
            archivo.write(reinterpret_cast<const char*>(&len), sizeof(len));
            archivo.write(jugo.getNombre().c_str(), len);

            int cantidad = jugo.getCantidad();
            double precio = jugo.getPrecio();
            archivo.write(reinterpret_cast<const char*>(&cantidad), sizeof(cantidad));
            archivo.write(reinterpret_cast<const char*>(&precio), sizeof(precio));
        }
    }

    // h) Guardar empleados despedidos
    {
        size_t totalDespedidos = EMPLEADOS_DESPEDIDOS.size();
        archivo.write(reinterpret_cast<const char*>(&totalDespedidos), sizeof(totalDespedidos));
        for(const auto& nombre : EMPLEADOS_DESPEDIDOS) {
            size_t len = nombre.size();
            archivo.write(reinterpret_cast<const char*>(&len), sizeof(len));
            archivo.write(nombre.c_str(), len);
        }
    }

    // i) Guardar tienda
    {
        Tienda& t = *tiendita;
        int limon = t.getLimon(), naranja = t.getNaranja(), pina = t.getPilla();
        int sandia = t.getSandia(), fresa = t.getFresa(), tamarindo = t.getTamarindo(), coco = t.getCoco();
        int conservantes = t.getConservantesComprados(), envases = t.getEnvasesComprados();
        double aguaComprada = t.getAguaComprada();
        double totalGastado = t.getDineroGastadoEnTodaLatienda();
        int totalFrutas = t.getFrutasCompradas();

        archivo.write(reinterpret_cast<const char*>(&limon), sizeof(limon));
        archivo.write(reinterpret_cast<const char*>(&naranja), sizeof(naranja));
        archivo.write(reinterpret_cast<const char*>(&pina), sizeof(pina));
        archivo.write(reinterpret_cast<const char*>(&sandia), sizeof(sandia));
        archivo.write(reinterpret_cast<const char*>(&fresa), sizeof(fresa));
        archivo.write(reinterpret_cast<const char*>(&tamarindo), sizeof(tamarindo));
        archivo.write(reinterpret_cast<const char*>(&coco), sizeof(coco));

        archivo.write(reinterpret_cast<const char*>(&conservantes), sizeof(conservantes));
        archivo.write(reinterpret_cast<const char*>(&envases), sizeof(envases));
        archivo.write(reinterpret_cast<const char*>(&aguaComprada), sizeof(aguaComprada));
        archivo.write(reinterpret_cast<const char*>(&totalGastado), sizeof(totalGastado));
        archivo.write(reinterpret_cast<const char*>(&totalFrutas), sizeof(totalFrutas));
    }

    // j) guardar estado de la maquina
    
    for(Maquina* m:maquinas){

        int vecesUsadas=m->getVecesUsadas();
        int vecesReparadas=m->getVecesReparada();
        bool Estado=m->getEstado();

        archivo.write(reinterpret_cast<const char*>(&vecesUsadas),sizeof(vecesUsadas));
        archivo.write(reinterpret_cast<const char*>(&vecesReparadas),sizeof(vecesReparadas));
        archivo.write(reinterpret_cast<const char*>(&Estado),sizeof(Estado));

        //aqui guarda el tiempo como tipo time_t
        std::chrono::system_clock::time_point FechaUso=m->getUltimaFechaUsoTP();
        std::time_t tiempo=std::chrono::system_clock::to_time_t(FechaUso);
        archivo.write(reinterpret_cast<const char*>(&tiempo),sizeof(tiempo));
        

    }
    
    archivo.close();
    cout << "\nSimulacion guardada exitosamente en: " << ruta << "\n";
}

void Gestor_De_Planta::CargarSimulacionBinario(const std::string &nombreArchivo) {
    std::string carpeta = "Plantas Industriales guardadas";
    std::string ruta = carpeta + "/" + nombreArchivo;

    std::ifstream archivo(ruta, std::ios::binary);
    if (!archivo.is_open()) {
        std::cerr << "No se pudo abrir el archivo para cargar la simulacion.\n";
        return;
    }

    // a) Nombre planta
    size_t len;
    archivo.read(reinterpret_cast<char*>(&len), sizeof(len));
    NombreDelaPlanta.resize(len);
    archivo.read(&NombreDelaPlanta[0], len);

    // b) Capital, agua, conservantes, envases
    archivo.read(reinterpret_cast<char*>(&CapitalInicial), sizeof(CapitalInicial));
    archivo.read(reinterpret_cast<char*>(&AguaLitros), sizeof(AguaLitros));
    archivo.read(reinterpret_cast<char*>(&Conservantes), sizeof(Conservantes));
    archivo.read(reinterpret_cast<char*>(&Envases), sizeof(Envases));

    // c) Frutas
    FRUTAS.clear();
    size_t TotalFrutass;
    archivo.read(reinterpret_cast<char*>(&TotalFrutass), sizeof(TotalFrutass));
    for (size_t i = 0; i < TotalFrutass; ++i) {
        int tipoInt, cantidad, cLavada;
        double costo;
        archivo.read(reinterpret_cast<char*>(&tipoInt), sizeof(tipoInt));
        archivo.read(reinterpret_cast<char*>(&costo), sizeof(costo));
        archivo.read(reinterpret_cast<char*>(&cantidad), sizeof(cantidad));
        archivo.read(reinterpret_cast<char*>(&cLavada), sizeof(cLavada));

        std::string nombre;
        switch(tipoInt) {
            case 0: nombre = "Agua"; break;
            case 1: nombre = "Limon"; break;
            case 2: nombre = "Naranja"; break;
            case 3: nombre = "Piña"; break;
            case 4: nombre = "Sandia"; break;
            case 5: nombre = "Fresa"; break;
            case 6: nombre = "Tamarindo"; break;
            case 7: nombre = "Coco"; break;
            default: nombre = "Desconocida"; break;
        }
        Frutas::Fruta tipo = Frutas::ObtenerFrutaDesdeNombre(nombre);
        Frutas fruta(tipo, costo, cantidad);
        fruta.setCantidadLavada(cLavada);
        FRUTAS.push_back(fruta);
    }

    // d) Empleados
    empleado.clear();
    size_t totalEmp;
    archivo.read(reinterpret_cast<char*>(&totalEmp), sizeof(totalEmp));
    for (size_t i = 0; i < totalEmp; ++i) {
        int tipoEmp;
        archivo.read(reinterpret_cast<char*>(&tipoEmp), sizeof(tipoEmp));

        size_t lenNom, lenCargo;
        std::string nombre, cargo;
        archivo.read(reinterpret_cast<char*>(&lenNom), sizeof(lenNom));
        nombre.resize(lenNom);
        archivo.read(&nombre[0], lenNom);

        archivo.read(reinterpret_cast<char*>(&lenCargo), sizeof(lenCargo));
        cargo.resize(lenCargo);
        archivo.read(&cargo[0], lenCargo);

        int id, salario, dineroGanado;
        archivo.read(reinterpret_cast<char*>(&id), sizeof(id));
        archivo.read(reinterpret_cast<char*>(&salario), sizeof(salario));
        archivo.read(reinterpret_cast<char*>(&dineroGanado), sizeof(dineroGanado));

        Empleado* nuevo = nullptr;
        if (tipoEmp == 0) nuevo = new EmpleadoOperario(nombre);
        else if (tipoEmp == 1) nuevo = new EmpleadoTecnico(nombre);

        if (nuevo) {
            nuevo->setId(id);
            nuevo->setSalario(salario);
            nuevo->setDineroGanado(dineroGanado);
            nuevo->setCargo(cargo);
            empleado.push_back(nuevo);
        }
    }

    // e) Frutas lavadas
    FRUTAS_LAVADAS.clear();
    size_t totalLavadas;
    archivo.read(reinterpret_cast<char*>(&totalLavadas), sizeof(totalLavadas));
    for (size_t i = 0; i < totalLavadas; ++i) {
        int tipoInt, cantidad;
        double costo;
        archivo.read(reinterpret_cast<char*>(&tipoInt), sizeof(tipoInt));
        archivo.read(reinterpret_cast<char*>(&costo), sizeof(costo));
        archivo.read(reinterpret_cast<char*>(&cantidad), sizeof(cantidad));

        std::string nombre;
        switch(tipoInt) {
            case 1: nombre = "Limon"; break;
            case 2: nombre = "Naranja"; break;
            case 3: nombre = "Piña"; break;
            case 4: nombre = "Sandia"; break;
            case 5: nombre = "Fresa"; break;
            case 6: nombre = "Tamarindo"; break;
            case 7: nombre = "Coco"; break;
            default: nombre = "Desconocida"; break;
        }

        Frutas::Fruta tipo = Frutas::ObtenerFrutaDesdeNombre(nombre);
        Frutas fruta(tipo, costo, cantidad);
        FRUTAS_LAVADAS.push_back(fruta);
    }

    // f) Jugos sin ingredientes
    JUGOS_SIN_INGREDIENTES.clear();
    size_t totalJugosSin;
    archivo.read(reinterpret_cast<char*>(&totalJugosSin), sizeof(totalJugosSin));
    for (size_t i = 0; i < totalJugosSin; ++i) {
        size_t len;
        archivo.read(reinterpret_cast<char*>(&len), sizeof(len));
        std::string nombre(len, ' ');
        archivo.read(&nombre[0], len);

        int cantidad;
        double precio;
        archivo.read(reinterpret_cast<char*>(&cantidad), sizeof(cantidad));
        archivo.read(reinterpret_cast<char*>(&precio), sizeof(precio));

        Producto jugo(nombre, cantidad, precio);
        jugo.setCantidadSinIngredientes(cantidad);
        JUGOS_SIN_INGREDIENTES.push_back(jugo);
    }

    // g) Jugos disponibles
    JUGOS_DISPONIBLES.clear();
    size_t totalJugos;
    archivo.read(reinterpret_cast<char*>(&totalJugos), sizeof(totalJugos));
    for (size_t i = 0; i < totalJugos; ++i) {
        size_t len;
        archivo.read(reinterpret_cast<char*>(&len), sizeof(len));
        std::string nombre(len, ' ');
        archivo.read(&nombre[0], len);

        int cantidad;
        double precio;
        archivo.read(reinterpret_cast<char*>(&cantidad), sizeof(cantidad));
        archivo.read(reinterpret_cast<char*>(&precio), sizeof(precio));

        Producto jugo(nombre, cantidad, precio);
        JUGOS_DISPONIBLES.push_back(jugo);
    }

    // h) Empleados despedidos
    EMPLEADOS_DESPEDIDOS.clear();
    size_t totalDespedidos;
    archivo.read(reinterpret_cast<char*>(&totalDespedidos), sizeof(totalDespedidos));
    for (size_t i = 0; i < totalDespedidos; ++i) {
        size_t len;
        archivo.read(reinterpret_cast<char*>(&len), sizeof(len));
        std::string nombre(len, ' ');
        archivo.read(&nombre[0], len);
        EMPLEADOS_DESPEDIDOS.push_back(nombre);
    }

    // i) Tienda
    int limon, naranja, pina, sandia, fresa, tamarindo, coco, conservantes, envases, totalFrutas;
    double agua, totalGastado;
    archivo.read(reinterpret_cast<char*>(&limon), sizeof(limon));
    archivo.read(reinterpret_cast<char*>(&naranja), sizeof(naranja));
    archivo.read(reinterpret_cast<char*>(&pina), sizeof(pina));
    archivo.read(reinterpret_cast<char*>(&sandia), sizeof(sandia));
    archivo.read(reinterpret_cast<char*>(&fresa), sizeof(fresa));
    archivo.read(reinterpret_cast<char*>(&tamarindo), sizeof(tamarindo));
    archivo.read(reinterpret_cast<char*>(&coco), sizeof(coco));
    archivo.read(reinterpret_cast<char*>(&conservantes), sizeof(conservantes));
    archivo.read(reinterpret_cast<char*>(&envases), sizeof(envases));
    archivo.read(reinterpret_cast<char*>(&agua), sizeof(agua));
    archivo.read(reinterpret_cast<char*>(&totalGastado), sizeof(totalGastado));
    archivo.read(reinterpret_cast<char*>(&totalFrutas), sizeof(totalFrutas));

    tiendita->setDatosCompras(limon, naranja, pina, sandia, fresa, tamarindo, coco,conservantes, envases, agua, totalGastado, totalFrutas);

    //j) aqui cargar el estado de las 3 maquinas
    for(Maquina* m:maquinas){

        int VecesUsadas,VecesReperadas;
        bool Estado;
        std::time_t tiempo;

        archivo.read(reinterpret_cast<char*>(&VecesUsadas),sizeof(VecesUsadas));
        archivo.read(reinterpret_cast<char*>(&VecesReperadas),sizeof(VecesReperadas));
        archivo.read(reinterpret_cast<char*>(&Estado),sizeof(Estado));
        archivo.read(reinterpret_cast<char*>(&tiempo),sizeof(tiempo));

        m->setEnUso(Estado);

        //aqui con ciclo for asignas los datos
        for (int i=0;i<VecesReperadas;++i)m->IncrementarReparacion();
        for (int i=0;i<VecesUsadas;++i)m->IncrementarUso();
        m->setUltimaFechaUsoTP(std::chrono::system_clock::from_time_t(tiempo));

    }

    archivo.close();
    std::cout << "\nSimulacion cargada exitosamente desde: " << ruta << "\n";
}


