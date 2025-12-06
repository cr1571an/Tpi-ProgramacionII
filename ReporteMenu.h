#pragma once
#include "PolizaManager.h"
#include "ClienteManager.h"

class ReporteMenu{
    public:
        ReporteMenu();
        void mostrar();

    private:
        int _cantidadOpciones;
        void mostrarOpciones();
        int seleccionOpcion();
        void ejecutarOpcion(int opcion);

        PolizaManager _polizaManager;
        ClienteManager _clienteManager;
    
};