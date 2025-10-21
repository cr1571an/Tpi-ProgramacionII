#include <iostream>
#include "ClienteManager.h"
using namespace std;

int main() {
    /// Funciona
    ClienteManager cm;
    cm.cargar();
    cm.mostrar();

    /// No funciona
    /*VehiculoManager vm;
    vm.cargar(cm);
    vm.mostrar();
    */

    return 0;
}


