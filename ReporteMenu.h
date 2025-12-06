#pragma once
#include "Reportes.h"

class ReporteMenu {
    public:
        ReporteMenu();
        void mostrar();
        void mostrarOpciones();
        int seleccionOpcion();
        void ejecutarOpcion(int opcion);

    private:
        int _cantidadOpciones;
        Reportes _reportes;
};