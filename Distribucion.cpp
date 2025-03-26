#include "Distribucion.h"
#include "Gestor_De_Planta.h"

using namespace std;

Distribucion::Distribucion(){

    //esto guarda el tiempo actual como referencia 
    tiempoUltimoPedido=chrono::steady_clock::now();

    generarPedidosAleatorios();
    activo=true;
    hiloGeneradorPedidos=std::thread([this](){

        while (activo)
        {
            
            std::this_thread::sleep_for(std::chrono::seconds(1));//cada segundo lo verficaraaa
            verificarRegeneracionPedidos();

        }
        

    });

}

Distribucion::~Distribucion(){

    activo=false;
    if(hiloGeneradorPedidos.joinable())
    {
        
        hiloGeneradorPedidos.join();

    }
    

}

//esta funcion verifica si deben regeenerar los pedidos automaticamente despues de 15 segundos
void Distribucion::verificarRegeneracionPedidos(){

    auto ahora=chrono::steady_clock::now();
    auto TiempoPasado=chrono::duration_cast<chrono::seconds>(ahora-tiempoUltimoPedido);


    //aqui si no hay pedidos pendientes y han pasado al menos 15 segundos, se generan mas pedidos
    if (pedidosPendientes.size()<7&&TiempoPasado.count()>=15)
    {

        //cout<<"\n Generar mas pedidos\n";
        generarPedidosAleatorios();
        tiempoUltimoPedido=ahora;//aqui actualiza el tiempo del ultimpo pedidoooooo

    }

}

char obtenerRespuestaSINO(string mensaje){

    string temp;
    char respuesta;
    while(true){

        cout<<mensaje;
        getline(cin,temp);
        if(temp.empty())continue;
        respuesta = tolower(temp[0]);  
        if(respuesta=='s'||respuesta=='n')return respuesta;
        cout << "Entrada invalida. Ingrese 's' para si o 'n' para no.\n";   

    }

}

//mapa con los precios base por nombre de jugo como respaldo.
std::map<std::string, double> preciosBase = {

    {"Limon", 17.0}, {"Naranja", 15.0}, {"Piña", 12.0},
    {"Sandia", 11.0}, {"Fresa", 22.0}, {"Tamarindo", 24.0}, {"Coco", 30.0}

};

void Distribucion::generarPedidosAleatorios(){

    int MaximoPedidosAGenerar=3+rand()%3;//entre 3 0 5 pedidos
    int EspacioDisponible=7-pedidosPendientes.size();
    MaximoPedidosAGenerar=min(MaximoPedidosAGenerar,EspacioDisponible);

    vector<string> jugos= {

        "Limon","Naranja","Piña","Sandia","Fresa","Tamarindo","Coco"

    };

    srand(time(0));//para los numeros aletoariosss


    for(int i=0;i<MaximoPedidosAGenerar;i++)
    {

        map<string,int>pedido;
        int NumeroJugos=2+rand()%3;//entre 2 y 4 tipos de jugos por pedido
        for(int j=0;j<NumeroJugos;j++)
        {
           
            string Jugo=jugos[rand()%jugos.size()];//creacion del juguito aletorioooo]
            int cantidad=1+rand()%5;//entre 1 y 5 unidades
            pedido[Jugo]+=cantidad;//si ya existe el jugo se le suma

        }
        pedidosPendientes.push_back(pedido);//aqui se guarda el pedido
           
    }
    
}

//esta funcion servira para mostrar todos los pedidos pendientes
void Distribucion::mostrarPedidosDisponibles(){

    cout<<"\n Pedidos Pendientes:\n";

    if(pedidosPendientes.empty())
    {
        
        cout<<"\n No hay pedidos pendientes.\n";
        return;

    }

    const auto& jugosDisponiblesss=gestorReferencia->getInventarioJugos();

    for (size_t i=0;i<pedidosPendientes.size();i++)
    {
        const auto& pedido=pedidosPendientes[i];
        double total=calcularPrecioPedido(pedido,jugosDisponiblesss);
        int tiempoEntrega=calcularTiempoEntrega(pedido.size());//tiempo depende de tipos de jugos

        cout<<i+1<<". Pedido: ";
        for(const auto&[nombre,cantidad]:pedido){

            cout<<nombre<<" x"<<cantidad<<" | ";

        }
        cout<<" Total estimado: $"<<total<<" | Tiempo estimado: "<<tiempoEntrega<<" segundos\n";
        
    }

    /*
    
    Ejemplo de calcularTiempoEntrega
    Supon que hay 3 tipos de jugos en el pedido:


    int calcularTiempoEntrega(3) 
    → 6 + calcularTiempoEntrega(2)
    → 6 + 6 + calcularTiempoEntrega(1)
    → 6 + 6 + 6 + calcularTiempoEntrega(0)
    → 6 + 6 + 6 + 0 = 18 segundos
    
    */
    
}

//esta funcion verifica si hay suficientes jugos disponibles en invetario para completar el pedido
bool Distribucion::verificarDisponibilidad(const map<string,int>& pedido,const vector<Producto>& jugos){

    for(const auto&[nombre,cantidad]:pedido){

        //este for buscara si hay un jugo con nombre igual y cantidad suficiente
        auto Encuentra=find_if(jugos.begin(),jugos.end(),[&](const Producto& p){

            return p.getNombre()==nombre&&p.getCantidad()>=cantidad;

        });
        if(Encuentra==jugos.end())return false;//si no lo encuentra, no se puede complir 

    }
    return true;

}

//esta funcion procesa y entraga un pedido, actualizara el inventario y suma la ganarancia a la capitallll
void Distribucion::procesarPedido(Gestor_De_Planta& gestor,int indice){

    double total=0;//esta vriable acumulara la ganancia del pedido

    if(indice<1||indice>(int)pedidosPendientes.size())
    {
        
        cout<<"Pedido invalidoooo\n";
        return;

    }
    auto& jugos=gestor.getInventarioJugos();//este accede al inventario de jugos listos
    auto& pedido=pedidosPendientes[indice-1];//acceede al pedido selccionado

    if (!verificarDisponibilidad(pedido,jugos))
    {
        
        cout<<"\nNo hay suficientes jugos disponibles para este pedido\n";
        return;

    }

    cout<<"\nEstas a punto de entregar el siguiente pedido:\n";
    for(const auto&[nombre,cantidad]:pedido){

        cout<<nombre<<" x"<<cantidad<<" | ";

    }
    char confirmacion;
    confirmacion=obtenerRespuestaSINO("\nDeseas continuar? (s/n): ");
    if(confirmacion!='s'&&confirmacion!='S')return;

    //aqui simulara el tiempo de entrega con pausa y animacionnn
    int TiempoEntrega=calcularTiempoEntrega(pedido.size());
    cout<<"\nEntregando pedido, tiempo estimado: "<<TiempoEntrega<<" segundos..\n";
    cout<<"Enviando";
    for (int i=0;i<TiempoEntrega;i++)
    {
        
        cout<<".";
        cout.flush();
        std::this_thread::sleep_for(std::chrono::seconds(1));

    }
    cout<<"\n";
    
    for(auto&[nombre,cantidad]:pedido){
        for(auto& jugo:jugos){

            if(jugo.getNombre()==nombre){

                //aqui restara las unidades vendidas
                jugo.setCantidadProducida(jugo.getCantidadProducida()-cantidad);
                total+=cantidad*jugo.getPrecio();//sumara la gananciaaaaaaa
                ventasPorJugo[nombre]+=cantidad;//aqui se registra la venta
                break;

            }

        }

    }
    gestor.agregarCapital(total);//aqui se sumara la ganancia a la capital
    cout<<"\n Pedido entregado con exito. Ganancia: $"<<total<<"\n";

    //este eliminara el pedido del vector
    pedidosPendientes.erase(pedidosPendientes.begin()+(indice-1));
    

}

//EXPLICAR ESTA FUNCIONNN
//EXPLICAR ESTA FUNCIONNN
//EXPLICAR ESTA FUNCIONNN
//EXPLICAR ESTA FUNCIONNN
//EXPLICAR ESTA FUNCIONNN
void Distribucion::MostrarRanking(std::ostream& messi)const{

    if(ventasPorJugo.empty())
    {
        
        messi<<"\n >> No se han registrado ventas de jugos aun\n";
        return;

    }
    //aqui se convertira el mapa en vector para ordenar]
    std::vector<std::pair<std::string,int>> ranking(ventasPorJugo.begin(),ventasPorJugo.end());

    std::sort(ranking.begin(),ranking.end(),[](const auto& a, const auto& b){

        return a.second>b.second; // Orden descendente por cantidad

    });

    messi<<"\n>> Ranking de Jugos Mas Vendidos:\n";
    for(const auto& [nombre, cantidad] : ranking){

        messi << "- " << nombre << ": " << cantidad << " unidades vendidas\n";

    }

    // Mostrar jugo estrella (mas vendido) y menos vendido (con al menos 1 venta)
    const auto& estrella = ranking.front();
    messi<<"\n>> Jugo estrella: "<<estrella.first<<" ("<<estrella.second<<" unidades)\n";

    // Buscar el menos vendido que tenga al menos una venta
    for (auto menos=ranking.rbegin();menos!=ranking.rend();++menos) {

        if(menos->second>0){

            messi<< ">> Jugo menos vendido: "<<menos->first<<" ("<<menos->second<<" unidades)\n";
            break;

        }
    }

    //std::ostream& "messi" me permitira imprimir en pantalla o escribir en archivos (como los reportes) con la misma funcion.
 
    

}

//aqui funcion recursiva, calcula el tiempo total de entrega 
int Distribucion::calcularTiempoEntrega(int PedidosPendientes){

    if(PedidosPendientes<=0)return 0;
    return 6+calcularTiempoEntrega(PedidosPendientes-1);

}

double Distribucion::calcularPrecioPedido(const std::map<std::string, int>& pedido, const std::vector<Producto>& jugosDisponibles){

    double total=0;
    for(const auto&[nombre,cantidad]:pedido){

        auto cocacola=find_if(jugosDisponibles.begin(),jugosDisponibles.end(),[&](const Producto& jugo){

            return jugo.getNombre()==nombre;

        });
        if(cocacola!=jugosDisponibles.end()){

            total+=cocacola->getPrecio()*cantidad;

        }else{

            //aqui, usar precio base como referencia si el jugo no esta disponible
            if(preciosBase.count(nombre)){

                total+=preciosBase[nombre]*cantidad;

            }

        }


    }
    return total;

}

void Distribucion::mostrarMenuPedidos(Gestor_De_Planta& gestor){

    int opcion=0;

    while(opcion!=3)
    {
        verificarRegeneracionPedidos(); //la llamo al principio para verificar si hay que crear nuevos pedidos

        cout<<"=================================================================\n";
        cout<<"\n --- MENU DE DISTRIBUCION --- \n";
        cout<<"1. Ver pedidos pendientes\n";
        cout<<"2. Entregar pedido\n";
        cout<<"3. Volver\n";
        opcion=NumeroValido("Ingrese una opcion: ",1,3);

        if(opcion==1)
        {
            cout<<"=================================================================\n";
            mostrarPedidosDisponibles();

        }else if(opcion==2){

            cout<<"=================================================================\n";
            mostrarPedidosDisponibles();
            if(pedidosPendientes.empty())continue;
            int seleccion=NumeroValido("Seleccione el numero de pedido a entregar: ",1,pedidosPendientes.size());
            procesarPedido(gestor,seleccion);

        }else if(opcion==3){

            gestor.MiniMenuGestor(gestor);

        }else{

            cout<<"\nOpcion no valida\n";

        }
        
        
    }
    

}

