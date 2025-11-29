#pragma once
#include "PolizaManager.h"
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
    
};