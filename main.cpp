#ifdef _WIN32
#include <windows.h>
#endif
#include "App.h"
#include "tools/generadorDeArchivosDeDatos.h"
#include "tools/imprimirArchivos.h"
int main() {
    #ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
    #endif

    App app;
    app.run();
    
    /* generarClientes();
    generarVehiculos();
    generarPolizas();
    generarSiniestros();
    generarTiposSeguros();
    generarTiposSiniestros();
    generarVencimientos();
    imprimirClientes();
    imprimirVehiculos();
    imprimirPagos();
    imprimirSiniestros();
    imprimirPolizas();
    imprimirTiposSiniestros();
    imprimirTiposSeguros();
    imprimirVencimientos(); */

    return 0;
}