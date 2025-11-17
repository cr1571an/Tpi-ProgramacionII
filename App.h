#pragma once
#include "ClienteMenu.h"
#include "VehiculoMenu.h"

#include "PolizaMenu.h"
/*#include "SiniestroMenu.h"*/
//#include "PagoMenu.h"




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

    PolizaMenu _polizaMenu;
    /*SiniestroMenu _siniestroMenu;*/
    //PagoMenu _pagoMenu;


private:
    int _cantidadOpciones;
};
