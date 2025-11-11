#pragma once
#include "PolizaArchivo.h"
#include "Poliza.h"
#include "VehiculoManager.h"

class PolizaManager {
    public:
        PolizaManager();
        void mostrar();
        void cargar();
        void eliminar(int id);
    private:
        PolizaArchivo _archivo;
        VehiculoManager _vehiculoManager;

};
