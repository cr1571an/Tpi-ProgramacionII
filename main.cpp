#ifdef _WIN32
#include <windows.h>
#endif
#include <iostream>
#include "App.h"
#include "tools/imprimirArchivos.h"
#include "tools/generadorDeArchivosDeDatos.h"

using namespace std;

int main() {
    #ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
    #endif

    App app;
    app.run();

//  imprimirArchivos();
//  generarClientes();
//  generarPagos();
//  generarPolizas();
//  generarVehiculos();
//  generarSiniestros();
//  generarTiposSeguros();


    return 0;
}
