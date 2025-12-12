#pragma once
#include "PolizaManager.h"
#include "ClienteManager.h"
#include "SiniestroManager.h"
#include "PagoManager.h"

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
        PagoManager _pagoManager;
        SiniestroManager _siniestroManager;

};