#pragma once
#include "ClienteMenu.h"
#include "VehiculoMenu.h"
#include "ReporteMenu.h"
#include "PolizaMenu.h"
#include "SiniestroMenu.h"
#include "PagoMenu.h"
#include "ReporteMenu.h"




class App
{
public:
    App();
    void run();

protected:
    void mostrarOpciones();
    int seleccionOpcion();
    void ejecutarOpcion(int opcion);

    ClienteMenu _clienteMenu;
    VehiculoMenu _vehiculoMenu;
    ReporteMenu _reporteMenu;
    PolizaMenu _polizaMenu;
    SiniestroMenu _siniestroMenu;
    PagoMenu _pagoMenu;
    ReporteMenu _reporteMenu;
    

private:
    int _cantidadOpciones;
};
