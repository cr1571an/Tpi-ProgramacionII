#include <iostream>
#include "ClienteManager.h"
#include "VehiculoManager.h"

using namespace std;

int main() {

    ClienteManager c;
    //c.cargar();
    c.mostrar();
    //c.eliminar(4);
    //c.mostrar();
    //c.mostrarDatosDeClienteDNI("11111");

    VehiculoManager v;
    v.cargar(1);
    v.mostrar();
    //v.eliminar(1);
    //v.mostrar();
    ////v.mostrarVehiculosDeCliente(1);

    return 0;
}


